import sys
import xml.etree.ElementTree as ET
import re
from parse_code_file import *

#TODO: THIS/FUNCTION FOR TURNING FIELD NAMES INTO THEIR ASSOCIATED XML PROPS
attribute_code_map = {
    'tugs': ['numberOfTugs'],
    'position': ['startPosition'],
    'amount': ['amountDumped']
}

def stripAndSplitEventTagName(name):
    prefix = re.search('^[A-Z][a-z]+', name)
    if prefix:
        #the prefix identifying the entity type
        entity_prefix = prefix.group(0)
        #the code for the specific event amongst those for this entity
        event_code = name[len(entity_prefix):]
        return (entity_prefix, event_code)
    else:
        return None

def guess_type(name, value):
    if name == 'signalState':
        return 'SignalStateType'
    if value in ['true', 'false']:
        return 'bool'
    else:
        try:
            int(value)
            return 'int'
        except ValueError:
            pass

        try:
            float(value)
            return 'double'
        except ValueError:
            pass

        return 'std::string'

"""
this enforces an override pattern that ensures the chosen type can handle all values seen
e.g. if both int and double are seen, double can be used, but if bool and int were seen, it'd need to be treated as a string
"""
def pick_between_two_types(a, b):
    if a is None:
        return b
    elif b is None:
        return a
    elif a == b:
        return a
    elif (a == 'int' and b == 'double') or (b == 'int' and a == 'double'):
        return 'double'
    else:
        return 'std::string'

"""
Adds type info to entities, determining it from xml files
"""
def resolve_types(entities, filenames):
    for each_file in filenames:
        tree = ET.parse(each_file)

        all_valid = True
        num_passes = 0
        #treat every element in the tree as potentially useful
        while not num_passes or (not all_valid and num_passes < 2):
            all_valid = True
            for elm in tree.iter():
                parts = stripAndSplitEventTagName(elm.tag)
                if not parts:
                    # skip because this is an empty line unless the file is invalid or the format has changed
                    continue
                # split and clean up the entity type and
                each_entity_code, each_event_code = parts
                each_entity_name = cleanUpEntityName(each_entity_code)
                each_event_name = cleanUpEventCode(each_event_code)

                #some entities like track may not be initially known about; but we'll need to correct this to deal with the state list anyway
                if each_entity_name is None:
                    each_entity_name = each_entity_code


                if not each_entity_name in entities:
                    print("UNRECOGNISED ENTITY '{}' WITH CODE '{}'!".format(each_entity_name, each_entity_code), file=sys.stderr)
                    newEntity = Entity(each_entity_name, each_entity_code)
                    newEntity.IS_TENTATIVE = True
                    entities[each_entity_name] = newEntity
                    all_valid = False
                    # if each_entity_name == 'Train':
                    #     newEntity.activities = []

                target_entity = entities[each_entity_name]

                if each_event_name not in target_entity.events:
                    print("ENTITY {}: UNKNOWN EVENT '{}'!".format(target_entity.name, each_event_name),file=sys.stderr)

                    new_event = Event(target_entity, each_event_name, each_event_code)
                    target_entity.events[each_event_name] = new_event

                    #this is a special event that seems to only appear for some entity types and is always missing from the codes.xml
                    if each_event_name == 'WrapUp':
                        
                        # now we can say that all other states go to the 'WrappedUp' states with the wrapup event
                        for each_state in target_entity.states:
                            new_event.state_map[each_state] = 'WrappedUp'
                    # continue

                # the codes file was missing stuff so lets try to retro fit it and try again on another pass oof the xml tree
                target_event = target_entity.events[each_event_name]

                for each_name, each_value in elm.attrib.items():
                    each_clean_name = each_name
                    #we can only really work with the cleaned up names
                    valid = False
                    if each_clean_name in target_entity.attributes:
                        valid = True
                    else:
                        each_clean_name = cleanUpAttributeName(each_clean_name)
                        if each_clean_name in target_entity.attributes:
                            valid = True
                        elif each_clean_name in attribute_code_map:
                            for each_mapped_name in attribute_code_map[each_clean_name]:
                                for each_cpp_attr in target_entity.attributes:
                                    if each_mapped_name == each_cpp_attr:
                                        each_clean_name = each_mapped_name
                                        valid = True
                                        break
                                if valid:
                                    break

                    if each_clean_name not in target_event.attributes:
                        print("ENTITY {}: EVENT: {}: ATTRIBUTE '{}' WAS NOT PREVIOUSLY KNOWN TO BE IN THE EVENT!".format(target_entity.name, target_event.name, each_clean_name),
                              file=sys.stderr)
                        target_event.attributes.append(each_clean_name)

                    if not valid:
                        print("ENTITY {}: UNKNOWN ATTRIBUTE '{}'!".format(target_entity.name, each_clean_name), file=sys.stderr)
                        target_entity.attribute_types[each_clean_name] = None
                        all_valid = False

                    each_type = guess_type(each_clean_name, each_value)
                    each_type = pick_between_two_types(target_entity.attribute_types[each_clean_name], each_type)
                    target_entity.attribute_types[each_clean_name] = each_type

                    if each_entity_name == 'Signal' and each_clean_name == 'signalState':
                        each_value = each_value.capitalize()
                        target_event.state_map[each_value] = each_value
                    # elif each_clean_name == 'maintactivity':
                    #     target_entity.activities.append(each_value)

                    #note the name as it appeared in the tag for generating the xml parsing code
                    target_entity.attribute_codes[each_clean_name] = each_name
            num_passes += 1


