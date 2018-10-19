import sys
import xml.etree.ElementTree as ET
import re
from data_structures import *

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

def guess_type(entities, name, value):
    #allow the statetype of some entities (e.g. track signals) to be used as attributes for some events (e.g. track signals or trains)
    for each_entity in entities.values():
        if name == cleanUpAttributeName(each_entity.identifier):
            return ('''{0}::Id'''.format(each_entity.name), '''#include "../{0}/{0}.h"'''.format(each_entity.name))
        if each_entity.has_encodable_state and name == '''{0}State'''.format(each_entity.name[0].lower() + each_entity.name[1:]):
            return ('''{0}StateType'''.format(each_entity.name), '''#include "../{0}/{0}StateType.h"'''.format(each_entity.name))
    if value in ['true', 'false']:
        return ('bool', None)
    else:
        try:
            int(value)
            return ('int', None)
        except ValueError:
            pass

        try:
            float(value)
            return ('double', None)
        except ValueError:
            pass

        return ('std::string', None)

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
def resolve_attributes(entities, encodable_entities, filenames, should_only_print_warnings):

    entity_code_map = {each.prefix.capitalize() : each for each in entities.values()}

    #this will be used to only output one warning per unrecognised tag
    unsplittable_tags = set()
    unrecognised_entities = set()
    unrecognised_events_map = {}
    for each_file in filenames:
        tree = ET.parse(each_file)

        all_valid = True
        num_passes = 0
        #treat every element in the tree as potentially useful
        while not num_passes or (not all_valid and num_passes < 2):
            all_valid = True
            for elm in tree.iter():
                #only leaf elms are considered events, elms with children are "skipped" (though their children are still considered)
                if list(elm):
                    continue #skip

                parts = stripAndSplitEventTagName(elm.tag)
                if not parts:
                    if elm.tag not in unsplittable_tags:
                        print("[Warning]: The tag-name '{}' does not match the expected format. All elements with this name will be skipped.".format(elm.tag),
                        file=sys.stderr)
                        unsplittable_tags.add(elm.tag)
                    continue #skip tag

                # split and clean up the entity prefix and event code
                each_entity_code, each_event_code = parts
                each_event_name = cleanUpEventCode(each_event_code)
                if each_entity_code not in entity_code_map.keys():
                    if each_entity_code not in unrecognised_entities:
                        print("[Warning]: The entity prefix '{}' is not recognised. All elements with this prefix will be skipped.".format(each_entity_code), file=sys.stderr)
                        unrecognised_entities.add(each_entity_code)
                    continue #skip tag

                target_entity = entity_code_map[each_entity_code]

                if each_event_name not in target_entity.events.keys():
                    each_sub_set = None
                    if each_entity_code not in unrecognised_events_map:
                        each_sub_set = set()
                        unrecognised_events_map[each_entity_code] = each_sub_set
                    else:
                        each_sub_set = unrecognised_events_map[each_entity_code]

                    if each_event_name not in each_sub_set:
                        print("[Warning]: For entity {1} - The event code '{0}' is not recognised. All elements with this code will be skipped for this entity.".format(each_event_code, target_entity.name),
                            file=sys.stderr)
                        each_sub_set.add(each_event_name)
                    continue

                # the codes file was missing stuff so lets try to retro fit it and try again on another pass oof the xml tree
                target_event = target_entity.events[each_event_name]

                for each_name, each_value in sorted(elm.attrib.items()):
                    each_clean_name = each_name

                    #we can only really work with the cleaned up names
                    attribute_recognised = False
                    if each_clean_name in target_event.attributes:
                        attribute_recognised = True
                    else:
                        each_clean_name = cleanUpAttributeName(each_clean_name)
                        if each_clean_name in target_event.attributes:
                            attribute_recognised = True
                        elif each_clean_name in attribute_code_map:
                            for each_mapped_name in attribute_code_map[each_clean_name]:
                                for each_cpp_attr in target_event.attributes:
                                    if each_mapped_name == each_cpp_attr:
                                        each_clean_name = each_mapped_name
                                        attribute_recognised = True
                                        break
                                if attribute_recognised:
                                    break

                    if not attribute_recognised:
                        if each_clean_name not in target_entity.attributes:
                            if not should_only_print_warnings:
                                print("[Info]: For entity {2} - for event {1} - found new attribute ({0}).".format(each_clean_name, each_event_code, target_entity.name),
                            file=sys.stderr)
                            target_entity.attribute_types[each_clean_name] = None
                            target_entity.attribute_codes[each_clean_name] = each_name
                        else:
                            if not should_only_print_warnings:
                                print(
                                    "[Info]: For entity {2} - for event {1} - found recognised attribute ({0}).".format(each_clean_name,
                                                                                                            each_event_code,
                                                                                                            target_entity.name),
                                    file=sys.stderr)
                        target_event.attributes.append(each_clean_name)

                    each_type, each_header = guess_type(entities, each_clean_name, each_value)
                    each_final_type = pick_between_two_types(target_entity.attribute_types[each_clean_name], each_type)
                    target_entity.attribute_types[each_clean_name] = each_final_type
                    if each_header is not None:
                        target_entity.attribute_headers.add(each_header)
            num_passes += 1


