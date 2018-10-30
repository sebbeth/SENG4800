import re
from functools import total_ordering
import itertools

#this should not be needed with the json files
# #some dicts to map abbreviated event code components to their full words
# entity_name_map = {
#     'Lp': 'LoadPoint',
#     'Stk': 'Stacker',
#     'Vessel': 'Vessel',
#     'Sl': 'ShipLoader',
#     'Sp': 'Stockpile',
#     'Rec': 'Reclaimer',
#     'Ds': 'DumpStation'
# }
# train_state_abbreviation_map = {
#     'Depart': 'Departed',
#     'Wait': 'Waiting',
#     'Enter': 'Entered',
#     'Leave': 'Left',
#     'Start': 'Started',
#     'Complete': 'Completed',
# }


#note: this map can be applied to both event codes and state names; but only since both are PascalCase
misc_abbreviation_map = {
    'Op': 'Operation',
    'Comp': 'Complete',
    'Trans': 'Transfer',
    'Maint': 'Maintenance',
    'Dep': 'Depart',
    'EA': 'Anchorage'
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

    # #restore any weirdly cased instances of the entity type names
    # for each_entity_name in entities.keys():
    #     case_insensitive_regex = re.compile(each_entity_name, re.IGNORECASE)
    #     name = case_insensitive_regex.sub(each_entity_name, name)

    #make ids full upper
    name = name.replace('Id', 'ID')

    #make the whole thing camelCase
    name = name[:1].lower() + name[1:]


    return name

@total_ordering
class Event:
    def __init__(self, entity, name, code):
        self.entity = entity
        self.name = name
        self.code = code
        self.attributes = []
    def __hash__(self):
        #uniquely id each event by the combination of it's name and it's parent'a name
        return (self.entity.name + self.name).__hash__()

    def __lt__(self, other):
        return self.name < other.name

    def __eq__(self, other):
        return self.entity == other.entity and self.name == other.name

@total_ordering
class State:
    def __init__(self, entity, name, code=None):
        self.entity = entity
        self.name = name
        self.code = code or name
        self.transitions = {}
    def __hash__(self):
        #uniquely id each event by the combination of it's name and it's parent'a name
        return (self.entity.name + self.name).__hash__()
    def __lt__(self, other):
        return self.name < other.name
    def __eq__(self, other):
        return self.entity == other.entity and self.name == other.name


@total_ordering
class Entity:
    def __init__(self, name, data=None):
        self.name = name
        if data:
            self.has_terminal = data['hasTerminal']
            #we currently assume that prefixes are always at most capitalized exactly onces at the beginning, and the next capital starts the event code
            self.prefix = data['tagPrefix'].capitalize()
            self.events = {}
            self.states = {}
            #{name: code}
            self.attribute_codes = {}
            self.attribute_types = {}
            self.attribute_headers = set()
            self.initial_state = None


            self.identifier = data['identifier']
            self.cleaned_identifier = cleanUpAttributeName(self.identifier)

            #if the data has information for decoding states, loop through that first
            if 'stateCodes' in data:
                for each_state_code, each_state_name in data['stateCodes'].items():
                    self.states[each_state_name] = State(self, each_state_name, each_state_code)
                self.has_encodable_state = True

                for each_event_code in data['events']:
                    each_event = None
                    each_event_name = cleanUpEventCode(each_event_code)
                    if each_event_name in self.events:
                        each_event = self.events[each_event_name]
                    else:
                        each_event = Event(self, each_event_name, each_event_code)
                        self.events[each_event_name] = each_event
            else:
                self.has_encodable_state = False
                #note that the state being decodable means there is no default initial and that it instead comes from the event data
                #initialise the initial state first
                if data['initial'] in self.states:
                    self.initial_state = self.states[data['initial']]
                else:
                    self.initial_state = State(self, data['initial'])
                    self.states[self.initial_state.name] = self.initial_state

                #now go through all the transitions
                for each_state_name, each_state_transitions in data['transitions'].items():
                    each_from_state = None
                    if each_state_name in self.states:
                        each_from_state = self.states[each_state_name]
                    else:
                        each_from_state = State(self, each_state_name)
                        self.states[each_state_name] = each_from_state

                    for each_event_code, each_to_state_name in each_state_transitions.items():
                        each_event = None
                        each_event_name = cleanUpEventCode(each_event_code)
                        if each_event_name in self.events:
                            each_event = self.events[each_event_name]
                        else:
                            each_event = Event(self, each_event_name, each_event_code)
                            self.events[each_event_name] = each_event

                        each_to_state = None
                        if each_to_state_name in self.states:
                            each_to_state = self.states[each_to_state_name]
                        else:
                            each_to_state = State(self, each_to_state_name)
                            self.states[each_to_state_name] = each_to_state

                        each_from_state.transitions[each_event] = each_to_state

    #lists all the attributes available across any event for this entity
    @property
    def attributes(self):
        return list(filter(lambda x: x != self.cleaned_identifier, self.attribute_types.keys()))

    # lists the attributes that aren't the id or state for use with the state classes
    @property
    def specific_attributes(self):
        result = list(filter(lambda x: x != self.cleaned_identifier, self.attribute_types.keys()))

        # don't duplicate the statetype if the state is encodable
        if self.has_encodable_state:
            to_remove = '''{entity.name[0].lower() + entity.name[1:]}State'''.format(entity=self)
            if result.count(to_remove):
                result.remove(to_remove)

        return result

    def __hash__(self):
        #uniquely id each event by the combination of it's name and it's parent'a name
        return self.name.__hash__()

    def __lt__(self, other):
        return self.name < other.name

    def __eq__(self, other):
        return self.name == other.name
