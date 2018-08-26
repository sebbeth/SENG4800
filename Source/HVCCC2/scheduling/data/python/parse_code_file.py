import csv
import re
from functools import total_ordering
import itertools

#some dicts to map abbreviated event code components to their full words
entity_name_map = {
    'Lp': 'LoadPoint',
    'Stk': 'Stacker',
    'Vessel': 'Vessel',
    'Sl': 'ShipLoader',
    'Sp': 'Stockpile',
    'Rec': 'Reclaimer',
    'Ds': 'DumpStation'
}
#note: this map can be applied to both event codes and state names; but only since both are PascalCase
misc_abbreviation_map = {
    'Op': 'Operation',
    'Comp': 'Complete',
    'Trans': 'Transfer',
    'Maint': 'Maintenance',
    'Dep': 'Depart',
    'EA': 'Anchorage'
}

train_state_abbreviation_map = {
    'Depart': 'Departed',
    'Wait': 'Waiting',
    'Enter': 'Entered',
    'Leave': 'Left',
    'Start': 'Started',
    'Complete': 'Completed',
}

#only applicable to attribute names currently due to the logic for camelCase
attribute_abbreviation_map = {
    'pos': 'position',
    '#': 'number of',
    'Name': ' name',
    'stackerID': 'machineID',
    'reclaimerID': 'machineID',
    'StackerID': 'machineID',
    'ReclaimerID': 'machineID',
    'isTidal': 'is tidal',
    'maintActivity': 'maintenance activity',
    'plannedTime': 'planned time',
    'signalState': 'signal state',
    'trainType': 'train type'
}

@total_ordering
class Event:
    def __init__(self, entity, name, code):
        self.entity = entity
        self.name = name
        self.code = code
        self.attributes = []
        self.state_map = {}
    def __hash__(self):
        #uniquely id each event by the combination of it's name and it's parent'a name
        return (self.entity.name + self.name).__hash__()
    def __lt__(self, other):
        return self.name < other.name
    def __eq__(self, other):
        return self.entity == other.entity and self.name == other.name

@total_ordering
class Entity:
    def __init__(self, name, code):
        self.name = name
        self.code = code

        #{name: code}
        self.attribute_codes = {}
        self.attribute_types = {}

        self.events = {}

    #lists all the attributes available across any event for this entity
    @property
    def attributes(self):
        return self.attribute_types.keys()

    @property
    def states(self):
        result = set()
        for each_event in self.events.values():
            for each in itertools.chain(each_event.state_map.keys(), each_event.state_map.values()):
                result.add(each)
        return result
    def __hash__(self):
        #uniquely id each event by the combination of it's name and it's parent'a name
        return self.name.__hash__()
    def __lt__(self, other):
        return self.name < other.name
    def __eq__(self, other):
        return self.name == other.name

def stripAndSplitEventCode(code):
    code = code.strip()
    #note that the description is only useful to human readers and essentially garbage for the codegen
    code, description = code.split(' ', 1)
    prefix = re.search('^[A-Z][a-z]+', code)
    if prefix:
        #the prefix identifying the entity type
        entity_prefix = prefix.group(0)
        #the code for the specific event amongst those for this entity
        event_code = code[len(entity_prefix):]
        return (entity_prefix, event_code)
    else:
        return None

def cleanUpEntityName(name):
    return entity_name_map[name] if name in entity_name_map else None

def cleanUpEventCode(code):
    # replace some shorthand with longhand
    for pattern, replacement in misc_abbreviation_map.items():
        index = code.find(pattern)
        if index >= 0 and code[index:index + len(replacement)] != replacement:
            code = code.replace(pattern, replacement)
    return code

def cleanUpAttributeName(name):
    name = name.strip()

    #replace some shorthand with longhand
    for pattern, replacement in attribute_abbreviation_map.items():
        index = name.find(pattern)
        if index >= 0 and name[index:index+len(replacement)] != replacement:
            name = name.replace(pattern, replacement)

    #this is so that re-instate ID as Id at the end of this
    name = name.replace('ID', ' id ')

    #make the PascalCase (later will be camelCase, but whatever)
    name = ''.join(each.capitalize() for each in name.split())

    #restore any weirdly cased instances of the entity type names
    for each_type in entity_name_map.values():
        case_insensitive_regex = re.compile(each_type, re.IGNORECASE)
        name = case_insensitive_regex.sub(each_type, name)

    #make ids full upper
    name = name.replace('Id', 'ID')

    #make the whole thing camelCase
    name = name[:1].lower() + name[1:]


    return name

def cleanUpStateName(name):
    #similar to cleanUpAttributeName except that we want PascalCase for enums (which states will become)
    #also some (but not all) states are already in camelCase, whilst others require capwords
    name = name.strip()

    if re.search('\s', name):
        #there's a space after stripping so it will require capswords
        # make the PascalCase (later will be camelCase, but whatever)
        name = ''.join(each.capitalize() for each in name.split())
    else:
        #else assume it's in camelCase and up the first letter to get PascalCase
        name = name[:1].upper() + name[1:]

    #replace some shorthand with longhand
    for pattern, replacement in misc_abbreviation_map.items():
        name = name.replace(pattern, replacement)

    return name

def cleanUpTrainStateName(name):
    # replace some shorthand with longhand
    for pattern, replacement in train_state_abbreviation_map.items():
        index = name.find(pattern)
        if index >= 0 and name[index:index + len(replacement)] != replacement:
            name = name.replace(pattern, replacement)
    return name

def parseFile(filename):
    # empty stuff to be filled by parsing
    entities = {entity_name_map[each]: Entity(entity_name_map[each], each) for each in entity_name_map.keys()}
    contents = {}

    # first, fully process the file into memory to play with in several passes
    with open(filename, 'r') as file:
        reader = csv.DictReader(file)
        for each_attribute in reader.fieldnames:
            contents[each_attribute] = []
        for row in reader:
            if row['CODES']:
                for each_attribute in reader.fieldnames:
                    contents[each_attribute].append(row[each_attribute])

    #delay processing for many-to-one codes until all others are done (so we know that all the one-to-manys have been identified), so that if it's actually a many-to-many we will have the many mapping available (note: if it is a many-to-many, the true mapping can be inferred from the contents of the delayed tuple
    #store the event (object reference) to add it to, plus contents, since some are many-to-one and some look like many-to-one but are actually many-to-many since they need to return to their old state.
    #[(event_to_add_to, from_names, pseudo_to_name)]
    state_transitions_to_delay_processing = []

    #set(entity_name+from_name}
    one_to_many_states = set()

    for i in range(len(list(contents.values())[0])):
        each_full_event_code = contents['CODES'][i]
        parts = stripAndSplitEventCode(each_full_event_code)

        if not parts:
            # skip because this is an empty line unless the file is invalid or the format has changed
            continue

        #split and clean up the entity type and
        each_entity_code, each_event_code = parts
        each_entity_name = cleanUpEntityName(each_entity_code)
        each_event_name = cleanUpEventCode(each_event_code)

        #parse the other fields
        attributes_info = contents['INFO'][i]
        attributes = [cleanUpAttributeName(each) for each in attributes_info.split(',')] if attributes_info else []

        from_state_info = contents['FROM STATE'][i]
        from_states = [cleanUpStateName(each) for each in from_state_info.split(',')]

        to_state_info = contents['TO STATE'][i]
        to_states = [cleanUpStateName(each) for each in to_state_info.split(',')]

        #if there's only one empty string, make it an empty list and recognise that as invalid in generate_code
        if to_states[0] == '':
            to_states = []

        #check if the event exists, else create it.
        target_entity = entities[each_entity_name]
        target_event = Event(target_entity, each_event_name, each_event_code)
        target_entity.events[each_event_name] = target_event

        #add the attributes info to the event
        target_event.attributes = attributes

        for each in attributes:
            target_entity.attribute_types[each] = None

        #check the length of from_states to decide whether to delay processing it or not
        if len(from_states) == 1:
            #we can process it immediately
            state_map = None
            if len(to_states) == 1:
                state_map = {from_states[0]: to_states[0]}
            elif not to_states:
                state_map = {from_states[0]: None}
            else:
                state_map = {from_states[0]+each_to: each_to for each_to in to_states}
                #add this one-to-many/many-to-many state to the list of one-to-many states seen (to help resolve many-to-one processing later)
                one_to_many_states.add(each_entity_name+from_states[0])
            target_event.state_map = state_map
        else:
            #we have to delay it because we can't tell if it's many-to-one to actually many-to-many yet
            state_transitions_to_delay_processing.append((target_event, from_states, to_states[0]))

    #now we can process the many-to-one state transitions
    for event_to_add_to, from_names, pseudo_to_name in state_transitions_to_delay_processing:
        state_map = None
        if event_to_add_to.entity.name+pseudo_to_name in one_to_many_states:
            state_map = {each_from: pseudo_to_name+each_from for each_from in from_names}
        else:
            state_map = {each_from: pseudo_to_name for each_from in from_names}
        event_to_add_to.state_map = state_map


    return entities
    #from this point onwards, the information from CODES.xslx is fully encoded into the python objects and the code gen can begin (note: still need a map from the attribute names in CODES.xslx to XML attributes though)