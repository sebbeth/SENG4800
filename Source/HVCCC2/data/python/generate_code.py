#! /bin/python3
import os
import glob
import itertools
import json
from data_structures import *
from resolve_attributes import *
import argparse
import datetime

parser = argparse.ArgumentParser(description='Generator of C++ code for XML parsing/etc')
parser.add_argument('-j', '--json-file', type=str, required=True)
parser.add_argument('-x', '--xml-directory', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str, required=True)
parser.add_argument('-s', '--generate_stubs', action='store_true')
parser.add_argument('-w', '--only_warnings', action='store_true')

args = parser.parse_args()

# todo: generate entity and event-name mappings for the parser, and possibly the parser?
# todo: test things
# note: must be a csv

json_src_path = args.json_file
xml_src_path = args.xml_directory
code_dst_path = args.output_directory
should_generate_stubs = args.generate_stubs
should_only_print_warnings = args.only_warnings

tab_spaces = ' ' * 4


def generate_entity_class(entity, has_event=True, merge_targets=None):
    decl = '''#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"'''
    if merge_targets:
        for each_target in merge_targets:
            decl += '''
#include "../{1}/{1}.h"'''.format(tab_spaces, each_target)
    if has_event:
        decl += '''
class {1}Event;'''.format(tab_spaces, entity.name)

    decl += ('''
class {1}State;
class {1} {{
public:''' +
             ('''
{0}using AssociatedEvent = {1}Event;''' if has_event else ''
              ) +
             (
                 ('''
{0}using AssociatedEntities = TypeList<''' + ', '.join(merge_targets) + '''>;''') if merge_targets else ''
             )
             +
             '''
{0}{0}using AssociatedState = {1}State;
{0}static const std::string ENTITY_NAME;''').format(tab_spaces, entity.name)
    if has_event:
        decl += '''
{0}static const std::string XML_TAG_PREFIX;'''.format(tab_spaces)
    decl += '''
{0}class Id {{
{0}public:
{0}{0}using Entity = {1};'''.format(tab_spaces, entity.name)

    if entity.has_terminal:
        decl += '''
{0}{0}TerminalId terminal;'''.format(tab_spaces)
    decl += '''
{0}{0}std::string name;
{0}{0}Id();
{0}{0}Id('''.format(tab_spaces)
    if entity.has_terminal:
        decl += '''TerminalId terminal, '''
    decl += '''const std::string& name);'''
    if merge_targets:
        for each_merge in merge_targets:
            decl += '''
{0}{0}Id(const {1}::Id& src);'''.format(tab_spaces, each_merge)
    decl += '''{0}{0}std::string nameForBinaryFile() const;
{0}{0}template<class Archive>
{0}{0}void serialize(Archive & archive);
{0}}};
}};

bool operator<(const {1}::Id& a, const {1}::Id& b);
bool operator==(const {1}::Id& a, const {1}::Id& b);
bool operator!=(const {1}::Id& a, const {1}::Id& b);

template<class Archive>
void {1}::Id::serialize(Archive & archive) {{
{0}archive('''.format(tab_spaces, entity.name)
    if entity.has_terminal:
        decl += '''terminal, '''
    decl += '''name);
}}'''.format(tab_spaces, entity.name)

    impl = '''#include "{1}.h"
'''.format(tab_spaces, entity.name)

    impl += '''
{1}::Id::Id(): 
'''.format(tab_spaces, entity.name)

    if entity.has_terminal:
        impl += '''terminal(TerminalId::Invalid), '''
    impl += ''' name("") {{
}}'''.format(tab_spaces)

    impl += '''
{1}::Id::Id('''.format(tab_spaces, entity.name)
    if entity.has_terminal:
        impl += '''TerminalId terminal, '''
    impl += '''const std::string& name): '''
    if entity.has_terminal:
        impl += '''terminal(terminal), '''
    impl += '''name(name) {{
}}'''.format(tab_spaces)

    if merge_targets:
        for each_merge in merge_targets:
            impl += '''
{1}::Id::Id(const {2}::Id& src): '''.format(tab_spaces, entity.name, each_merge)
            if entity.has_terminal:
                impl += '''terminal(src.terminal), '''.format(tab_spaces)
            impl += '''name(src.name) {{
}}'''.format(tab_spaces)

    impl += '''
const std::string {1}::ENTITY_NAME = "{1}";'''.format(tab_spaces, entity.name)
    if has_event:
        impl += '''
const std::string {1}::XML_TAG_PREFIX = "{2}";
'''.format(tab_spaces, entity.name, entity.prefix)
    impl += '''

bool operator<(const {1}::Id& a, const {1}::Id& b) {{
{0}return '''.format(tab_spaces, entity.name)
    if entity.has_terminal:
        impl += '''a.terminal < b.terminal || (a.terminal == b.terminal && '''
    impl += '''a.name < b.name'''
    if entity.has_terminal:
        impl += ''')'''
    impl += ''';
}}

bool operator==(const {1}::Id& a, const {1}::Id& b) {{
{0}return '''.format(tab_spaces, entity.name)
    if entity.has_terminal:
        impl += '''a.terminal == b.terminal && '''
    impl += '''a.name == b.name;
}}

bool operator!=(const {1}::Id& a, const {1}::Id& b) {{
{0} return !(a == b);
}}

std::string {1}::Id::nameForBinaryFile() const {{
{0}return '''.format(tab_spaces, entity.name)
    if entity.has_terminal:
        impl += '''encodeTerminalId(terminal) + '_' + '''
    impl += '''name;
}}'''.format(tab_spaces)

    return decl, impl


def generate_enum(enum_name, codemap, decode=True, encode=None):
    # default to implementing an encode if we're decoding
    if encode is None:
        encode = decode
    decl = '''#pragma once
#include <string>

enum class {1} {{'''.format(tab_spaces, enum_name)

    decl += ''.join(
        '\n{0}{1},'.format(tab_spaces, each)
        for each in sorted(codemap.values())
    )
    impl = None
    decl += '''
{0}Invalid
}};'''.format(tab_spaces)

    if decode or encode:
        decl += '''
'''
        impl = '''#include "{1}.h"
        '''.format(tab_spaces, enum_name)

    if decode:
        decl += '''
{1} decode{1}(const std::string& enumeratorString);'''.format(tab_spaces, enum_name)

        impl += '''
{1} decode{1}(const std::string& enumeratorString) {{
{0}'''.format(tab_spaces, enum_name)

        impl += ' else '.join(
            '''if (enumeratorString == "{1}") {{
{0}{0}return {2}::{3};
{0}}}'''.format(tab_spaces, each_code, enum_name, codemap[each_code])
            for each_code in sorted(codemap)
        )

        impl += ''' else {{
{0}{0}return {1}::Invalid;
{0}}}
}}'''.format(tab_spaces, enum_name)
    if encode:
        decl += '''
std::string encode{1}(const {1}& value);'''.format(tab_spaces, enum_name)

        impl += '''
std::string encode{1}(const {1}& value) {{
{0}switch(value) {{'''.format(tab_spaces, enum_name)
        for each_code, each_name in codemap.items():
            impl += '''
{0}{0}case {1}::{2}:
{0}{0}{0}return "{3}";
{0}{0}{0}break;
'''.format(tab_spaces, enum_name, each_name, each_code)
        impl += '''
{0}{0}default:
{0}{0}{0}return "Invalid";
{0}}}
}}'''.format(tab_spaces)
    return decl, impl


def generate_event_class(entity, decodable_entities):
    decl = '''#pragma once
#include <string>
#include "{0}EventType.h"
#include "{0}.h"
'''.format(entity.name)

    headers_to_add = sorted(list(entity.attribute_headers))
    if entity.has_encodable_state:
        to_remove = '''#include "../{1}/{1}.h"'''.format(tab_spaces, entity.name)
        if headers_to_add.count(to_remove):
            headers_to_add.remove(to_remove)
    decl += '\n'.join(headers_to_add)

    decl += '''
class {1}Event {{
public:
{0}using Entity = {1};
{0}Entity::Id id;
{0}{1}EventType type;
'''.format(tab_spaces, entity.name)

    for each_name in sorted(entity.attributes):
        decl += '''
{0}{1} {2};'''.format(tab_spaces, entity.attribute_types[each_name], each_name)

    decl += '''
'''

    decl += ''.join(
        '''
{0}bool has{1}() const;'''.format(tab_spaces, each_name[0].upper() + each_name[1:])
        for each_name in sorted(entity.attributes)
    )

    decl += '''

{0}template<class Archive>
{0}void serialize(Archive & archive);
}};

template<class Archive>
void {1}Event::serialize(Archive & archive) {{
{0}archive(id, type, '''.format(tab_spaces, entity.name) + ', '.join(sorted(entity.attributes)) + ''');
}'''

    impl = '''#include "{}Event.h"'''.format(entity.name)

    for each_attribute in sorted(entity.attributes):
        case_map = {
            "true": [],
            "false": []
        }

        for each_event in sorted(entity.events):
            case_map[("true" if each_attribute in entity.events[each_event].attributes else "false")].append(each_event)

        impl += '''

bool {1}Event::has{2}() const {{
{0}switch (type) {{'''.format(tab_spaces, entity.name, each_attribute[0].upper() + each_attribute[1:])
        if case_map["true"] and not case_map["false"]:
            impl += '''
{0}{0}case {1}EventType::Invalid:
{0}{0}{0}return false;
{0}{0}default:
{0}{0}{0}return true;
'''.format(tab_spaces, entity.name)
        else:
            impl += ''.join(
                '''
{0}{0}case {1}EventType::{2}:'''.format(tab_spaces, entity.name, each_event)
                for each_event in sorted(case_map["true"])
            )

            impl += '''
{0}{0}{0}return true;'''.format(tab_spaces)

            impl += ''.join(
                '''
{0}{0}case {1}EventType::{2}:'''.format(tab_spaces, entity.name, each_event)
                for each_event in sorted(case_map["false"])
            )

            impl += '''
{0}{0}default:
{0}{0}{0}return false;'''.format(tab_spaces)

        impl += '''
{0}}}
}}'''.format(tab_spaces)

    return decl, impl
    # todo: consider adding getters/setters? (atm these are just structs effectively)


def generate_state_class(entity, encodable_entities):
    # todo: figure out if/how to implement a hasX() system for states

    decl = '''#pragma once
#include <string>
#include "{1}.h"
#include "{1}Event.h"
#include "{1}StateType.h"
'''.format(tab_spaces, entity.name)

    headers_to_add = sorted(list(entity.attribute_headers))
    if entity.has_encodable_state:
        to_remove = '''#include "../{1}/{1}.h"'''.format(tab_spaces, entity.name)
        if headers_to_add.count(to_remove):
            headers_to_add.remove(to_remove)
    decl += '\n'.join(headers_to_add)

    decl += '''
class {1}State {{
public:
{0}using Entity = {1};
{0}Entity::Id id;
{0}{1}StateType type;
{0}
'''.format(tab_spaces, entity.name)

    if entity.attributes:
        attributes_to_add = list(entity.attributes)

        # don't duplicate the statetype if the state is encodable
        if entity.has_encodable_state:
            attributes_to_add.remove('''{}State'''.format(entity.name[0].lower() + entity.name[1:]))
        for each_name in sorted(attributes_to_add):
            decl += '''
{0}{1} {2};'''.format(tab_spaces, entity.attribute_types[each_name], each_name)
    else:
        attributes_to_add = []
    decl += '''
    
{0}{1}State() = default;

{0}template<class Archive>
{0}void serialize(Archive & archive);'''.format(tab_spaces, entity.name);

    impl = None
    if not entity.has_encodable_state:
        decl += '''
{0}static {1}StateType determineNextType({1}StateType stateType, {1}EventType eventType);'''.format(tab_spaces,
                                                                                                    entity.name)

        impl = '''#include "{1}State.h"

{1}StateType {1}State::determineNextType({1}StateType stateType, {1}EventType eventType) {{'''.format(tab_spaces,
                                                                                                      entity.name)

        impl += '''
{0}switch(stateType) {{'''.format(tab_spaces, entity.name)
        for each_state in entity.states.values():
            impl += '''
{0}{0}case {1}StateType::{2}:'''.format(tab_spaces, entity.name, each_state.name)
            if each_state.transitions:
                impl += '''
{0}{0}{0}switch(eventType) {{'''.format(tab_spaces, entity.name, each_state.name)

                for each_event, each_destination_state in each_state.transitions.items():
                    impl += '''
{0}{0}{0}{0}case {1}EventType::{2}:
{0}{0}{0}{0}{0}return {1}StateType::{3};'''.format(tab_spaces, entity.name, each_event.name,
                                                       each_destination_state.name)

                impl += '''
{0}{0}{0}{0}default:
{0}{0}{0}{0}{0}return {1}StateType::Invalid;
{0}{0}{0}}}'''.format(tab_spaces, entity.name)
            else:
                impl += '''
{0}{0}{0}return {1}StateType::Invalid;'''.format(tab_spaces, entity.name)

        impl += '''
{0}{0}default:
{0}{0}{0}return {1}StateType::Invalid;
{0}}}'''.format(tab_spaces, entity.name)

        impl += '''
}}'''.format(tab_spaces, entity.name)

    decl += '''
}};

template<class Archive>
void {1}State::serialize(Archive & archive) {{
{0}archive(id, type, '''.format(tab_spaces, entity.name) + ', '.join(sorted(attributes_to_add)) + ''');
}}'''.format(tab_spaces, entity.name)

    return decl, impl


def generate_merge_state_class(entities, merge_name, merge_target_names):
    entities_to_merge = list(filter(lambda x: x.name in merge_target_names, entities.values()))
    decl = '''#pragma once
#include "{1}.h"
#include "{1}StateType.h"'''.format(tab_spaces, merge_name)
    for each_to_merge in entities_to_merge:
        decl += '''
#include "../{1}/{1}State.h"'''.format(tab_spaces, each_to_merge.name)

    decl += '''
class {1}State {{
public:
{0}using Entity = {1};
{0}Entity::Id id;
{0}{1}StateType type;'''.format(tab_spaces, merge_name)

    seen_attributes = set()
    for each_to_merge in entities_to_merge:
        attributes_to_add = each_to_merge.attributes
        if each_to_merge.has_encodable_state:
            attributes_to_add.remove('''{}State'''.format(each_to_merge.name[0].lower() + each_to_merge.name[1:]))
        for each_attribute in attributes_to_add:
            if not each_attribute in seen_attributes:
                decl += '''
{0}{1} {2};'''.format(tab_spaces, each_to_merge.attribute_types[each_attribute], each_attribute)
                seen_attributes.add(each_attribute)
    for each_to_merge in entities_to_merge:
        decl += '''
{0}{1}State(const {2}State& src);'''.format(tab_spaces, merge_name, each_to_merge.name)

    decl += '''
    
{0}{1}State() = default;
    
{0}template<class Archive>
{0}void serialize(Archive & archive);
}};

template<class Archive>
void {1}State::serialize(Archive & archive) {{
{0}archive(id, type, '''.format(tab_spaces, merge_name) + ', '.join(sorted(attributes_to_add)) + ''');
}}'''.format(tab_spaces, merge_name)

    impl = '''#include "{1}State.h"'''.format(tab_spaces, merge_name)
    for each_to_merge in entities_to_merge:
        impl += '''
{1}State::{1}State(const {2}State& src): type({1}StateType::Invalid), id({{src.id.terminal, src.id.name}})'''.format(
            tab_spaces, merge_name, each_to_merge.name)
        for each_attribute in attributes_to_add:
            impl += ''', {1}(src.{1})'''.format(tab_spaces, each_attribute)
        impl += '''{{
{0}switch(src.type) {{'''.format(tab_spaces)
        for each_state in each_to_merge.states:
            impl += '''
{0}{0}case {2}StateType::{3}:
{0}{0}{0}type = {1}StateType::{3};
{0}{0}{0}break;'''.format(tab_spaces, merge_name, each_to_merge.name, each_state)
        impl += '''
{0}{0}default:
{0}{0}{0}type = {1}StateType::Invalid;
{0}}}
}}'''.format(tab_spaces, merge_name)

    return decl, impl


def generate_traits_template():
    decl = '''#pragma once
#include <string>
template<typename State>
class StateTraits {{
public:
{0}static State initializeFromEvent(const typename State::Entity::AssociatedEvent& src);
{0}static State generateNextState(const State& current, const typename State::Entity::AssociatedEvent& event);
}};'''.format(tab_spaces)

    return decl


'''
This generates the stubs for the template specialisations for each type
'''


def generate_traits_stub(entity):
    attributes_to_add = list(entity.attributes)
    # don't duplicate the statetype if the state is encodable
    if entity.has_encodable_state:
        to_remove = '''{}State'''.format(entity.name[0].lower() + entity.name[1:])
        if attributes_to_add.count(to_remove):
            attributes_to_add.remove(to_remove)

    # this is a hackish workaround that I /think/ works but only for current data
    initial_state_selection = None
    if entity.has_encodable_state:
        initial_state_selection = '''src.{0}State'''.format(entity.name[0].lower() + entity.name[1:])
    else:
        initial_state_selection = '''{1}StateType::{2}'''.format(tab_spaces, entity.name, entity.initial_state.name)

    decl = '''#pragma once
#include "../StateTraits.h"
#include "{1}State.h"
template<>
class StateTraits<{1}State> {{
public:
{0}static {1}State initializeFromEvent(const {1}Event& src) {{
{0}{0}/* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
{0}{0}auto tentativeState = {1}State::determineNextType({2}, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
{0}{0}return {{src.id, tentativeState != {1}StateType::Invalid ? tentativeState : {2}, '''.format(tab_spaces, entity.name, initial_state_selection)

    decl += ', '.join(
        '''src.{1}'''.format(tab_spaces, each_name)
        for each_name in filter(lambda x: x != 'type', sorted(attributes_to_add))
    )

    decl += '''}};
{0}}}

{0}static {1}State generateNextState(const {1}State& current, const {1}Event& event) {{

{0}{0}/* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
{0}{0}{1}State result = initializeFromEvent(event);//remove this line if/when you do
{0}{0}result.id = event.id;'''.format(tab_spaces, entity.name)

    # if it has encodable state this will be given by initialising from the event
    if not entity.has_encodable_state:
        decl += '''{0}{0}result.type = {1}State::determineNextType(current.type, event.type);'''.format(tab_spaces,
                                                                                                        entity.name)

    for each_name in filter(lambda x: x != 'type', sorted(attributes_to_add)):
        decl += '''
{0}{0}if(event.has{1}()) {{
{0}{0}result.{2} = event.{2};
{0}{0}}}'''.format(tab_spaces, each_name[0].upper() + each_name[1:], each_name)

    decl += '''
{0}{0}return result;

{0}}}
}};'''.format(tab_spaces)

    return decl, ''


def generate_data_extractor(entities, decodable_entities):
    tuple_signature = '''std::tuple<''' + ', '.join(
        '''
{0}std::vector<{1}Event>'''.format(tab_spaces, each_entity.name)
        for each_entity in sorted(entities.values())
    ) + '''
>''';

    decl = '''#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cstdio>

#include "../tinyxml2/tinyxml2.h"'''

    decl += ''.join(
        '''
#include "{0}/{0}Event.h"'''.format(each.name)
        for each in sorted(entities.values())
    )

    decl += '''

//This macro prints out an error message if the XMLError holds anything that isn't an tinyxml2::XML_SUCCESS
#ifndef XMLCheckResult
{0}//#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS){{ std::printf("Error: %i\\n", a_eResult); return a_eResult;}}

{0}#define XMLCheckResult(a_eResult, doPrint) if (a_eResult != tinyxml2::XML_SUCCESS){{ if (doPrint) {{std::printf("Error: %i\\n", a_eResult); }} return a_eResult;}}
#endif    

typedef {1} EventVectorTuple;

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode) {{
{0}Event event;
{0}tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode);
{0}XMLCheckResult(result, 1);
{0}destination.push_back(event);
{0}return result; 
}}

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode, TerminalId theTerminal) {{
{0}Event event;
{0}tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode, theTerminal);
{0}XMLCheckResult(result, 1);
{0}destination.push_back(event);
{0}return result; 
}}

template<typename T>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, T& destination, const std::string& attributeName) {{
{0}//hack to get around the bug where QueryAttribute returns an int instead of the enum instance
{0}tinyxml2::XMLError result = static_cast<tinyxml2::XMLError>(source.QueryAttribute(attributeName.c_str(), &destination));
{0}XMLCheckResult(result, 1);
{0}return result;
}}


template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, std::string& destination, const std::string& attributeName) {{
{0}const char* tmp;
{0}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{0}XMLCheckResult(result, 1);
{0}destination = tmp;
{0}return result;
}}'''.format(tab_spaces, tuple_signature)

    for each_entity in decodable_entities.values():
        decl += '''

template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, {1}StateType& destination, const std::string& attributeName) {{
{0}const char* tmp;
{0}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{0}XMLCheckResult(result, 1);
{0}destination = decode{1}StateType(tmp);
{0}return result;
}}'''.format(tab_spaces, each_entity.name)

    impl = '''#include "extractData.h"
#include <regex>'''.format(tab_spaces)

    for each_entity in sorted(entities.values()):
        extraction_signature = '''tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, {1}Event& destination, const std::string& eventTypeCode{2})'''.format(
            tab_spaces, each_entity.name, ', TerminalId theTerminal' if each_entity.has_terminal else '')
        decl += '''

{};'''.format(extraction_signature)

        impl += '''

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {{...extractEvent(source,&destination.x,"attributeTextX")..}} for each attribute
{1} {{
{0}destination.type = decode{2}EventType(eventTypeCode);
{0}if (destination.type == {2}EventType::Invalid) {{
{0}{0}XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
{0}}}
{0}//extract the identifying name
{0}XMLCheckResult(extractAttribute(source, destination.id.name, "{3}"), 0);
'''.format(tab_spaces, extraction_signature, each_entity.name, each_entity.identifier)
        if each_entity.has_terminal:
            impl += '''{0}destination.id.terminal = theTerminal;
'''.format(tab_spaces)

        allEventAttributes = set(each_entity.attributes)
        for each_event in each_entity.events.values():
            allEventAttributes = allEventAttributes & set(each_event.attributes)
        if allEventAttributes:
            for each_attribute in sorted(allEventAttributes):
                is_id_attr = False
                impl += '''
{0}XMLCheckResult(extractAttribute(source, destination.'''.format(tab_spaces)

                if '::Id' in each_entity.attribute_types[each_attribute]:
                    is_id_attr = True
                    impl += 'id.name'
                else:
                    impl += each_attribute

                impl += ''', "{1}"), 0);'''.format(tab_spaces, each_entity.attribute_codes[each_attribute])

                if is_id_attr:
                    impl += '''
{0}destination.id.terminal = theTerminal'''.format(tab_spaces)

        if set(each_entity.attributes) - allEventAttributes:
            allEventAttributes.add(each_entity.cleaned_identifier)
            # if there are some that aren't in every event type, do those
            impl += '''
{0}switch(destination.type) {{'''.format(tab_spaces, each_entity.name)

            # collect events with the same leftover set together
            leftover_map = {}
            for each_event in sorted(each_entity.events.values()):
                leftover_attributes = set(each_event.attributes) - allEventAttributes
                if leftover_attributes:
                    stringified_leftovers = str(leftover_attributes)
                    if stringified_leftovers not in leftover_map:
                        target = (leftover_attributes, [])
                        leftover_map[stringified_leftovers] = target
                    else:
                        target = leftover_map[stringified_leftovers]
                    target[1].append(each_event)

            # now generate the code for each of the unique sets
            for leftovers, events in sorted(leftover_map.values()):
                for each_event in sorted(events):
                    impl += '''
{0}{0}case {1}EventType::{2}:'''.format(tab_spaces, each_entity.name, each_event.name)

                for each_attribute in sorted(leftovers):
                    is_id_attr = False
                    impl += '''
{0}{0}{0}XMLCheckResult(extractAttribute(source, destination.'''.format(tab_spaces)

                    if '::Id' in each_entity.attribute_types[each_attribute]:
                        is_id_attr = True
                        impl += '{1}.name'.format(tab_spaces, each_attribute)
                    else:
                        impl += each_attribute

                    impl += ''', "{1}"), 0);'''.format(tab_spaces, each_entity.attribute_codes[each_attribute])

                    if is_id_attr and entities[each_entity.attribute_types[each_attribute].split('::Id')[0]].has_terminal:
                        impl += '''
{0}{0}{0}destination.{1}.terminal = theTerminal;'''.format(tab_spaces, each_attribute)
                impl += '''
{0}{0}{0}break;'''.format(tab_spaces)
            impl += '''
{0}}}'''.format(tab_spaces)
        impl += '''
{0}return tinyxml2::XML_SUCCESS;
}}'''.format(tab_spaces)

    extraction_signature = '''tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple& destination)'''

    decl += '''

{};'''.format(extraction_signature)

    impl += '''

{1} {{
{0}tinyxml2::XMLDocument document;
{0}tinyxml2::XMLNode* root;
{0}tinyxml2::XMLElement* eachElement;

{0}int fileNameIndex = std::max(int(srcFilePath.rfind('/')), int(srcFilePath.rfind('\\\\')))+1;
{0}std::string terminalName = srcFilePath.substr(fileNameIndex, TERMINAL_CODE_LENGTH);
{0}TerminalId theTerminal = decodeTerminalId(terminalName); //not that this could easily be null;

{0}tinyxml2::XMLError eResult = document.LoadFile(srcFilePath.c_str());
{0}XMLCheckResult(eResult, 0);

{0}//Set the root pointer to point to the root element; this is different to FirstChild and should skip the xml version declaration node
{0}root = document.RootElement();
{0}if (root == nullptr) {{
{0}{0}return tinyxml2::XML_ERROR_FILE_READ_ERROR;
{0}}}

{0}eachElement = root->FirstChildElement();
{0}if (eachElement == nullptr) {{
{0}{0}return tinyxml2::XML_ERROR_PARSING_ELEMENT;
{0}}}

{0}//The program keeps looping until all of the elements have been read:
{0}while (eachElement != nullptr) {{
{0}{0}std::string tagName = eachElement->Name();
{0}{0}std::string entityTypeCode, eventTypeCode;
{0}{0}std::regex prefixRegex("^[A-Z][a-z]+");
{0}{0}std::sregex_iterator regItBegin(tagName.begin(), tagName.end(), prefixRegex);

{0}{0}if (regItBegin != std::sregex_iterator()) {{
{0}{0}{0}entityTypeCode = (*regItBegin).str();
{0}{0}{0}eventTypeCode = tagName.substr(entityTypeCode.size());
{0}{0}{0}'''.format(tab_spaces, extraction_signature)

    impl += ' else '.join(
        ('''if (entityTypeCode == {1}::XML_TAG_PREFIX) {{
{0}{0}{0}{0}extractEvent(*eachElement, std::get<std::vector<{1}Event>>(destination), eventTypeCode''' + (
            ', theTerminal' if each.has_terminal else '') + '''); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
{0}{0}{0}}}''').format(tab_spaces, each.name)
        for each in sorted(entities.values())
    )

    impl += ''' else {{
{0}{0}{0}{0}//state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
{0}{0}{0}{0}std::printf("Warning: unrecognised tag '%s'\\n", tagName.c_str()); //todo: should probably print a better warning, etc
{0}{0}{0}}}
{0}{0}}} else {{
{0}{0}{0}//if it's an element that we know might have children we want, check those instead of assuming it's wrong
{0}{0}{0}if (std::string(tagName.c_str()) == "railEvents" && !eachElement->NoChildren()) {{
{0}{0}{0}{0}eachElement = eachElement->FirstChildElement();
{0}{0}{0}{0}continue;
{0}{0}{0}}} else {{
{0}{0}{0}{0}//state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
{0}{0}{0}{0}std::printf("Warning: unrecognised tag '%s'\\n", tagName.c_str()); //todo: should probably print a better warning, etc
{0}{0}{0}}}
{0}{0}}}
{0}{0}//Moves the element pointer to the next event element:
{0}{0}tinyxml2::XMLElement* nextElement = eachElement->NextSiblingElement();

{0}{0}//if we reach the end of a sublist and there's a parent, move onto that. instead of giving up
{0}{0}if (nextElement == nullptr && eachElement->Parent() != nullptr) {{
{0}{0}{0}nextElement = eachElement->Parent()->NextSiblingElement();
{0}{0}}}
{0}{0}eachElement = nextElement;
{0}}}
{0}return tinyxml2::XML_SUCCESS;
}}'''.format(tab_spaces)

    return decl, impl


def generate_entity_type_lists(entities, merges):
    decl = '''#pragma once
#include "../util.h"
#include <map>
#include <tuple>
'''
    for each_name in entities:
        decl += '''
#include "{1}/{1}.h"
#include "{1}/{1}Event.h"
#include "{1}/{1}State.h"'''.format(tab_spaces, each_name)

    for each_name in merges:
        decl += '''
#include "{1}/{1}.h"
#include "{1}/{1}State.h"'''.format(tab_spaces, each_name)

    decl += '''

#define EntitiesWithEvents {1}
#define MergeEntities {2}
#define AllEntities {3}'''.format(
        tab_spaces,
        ', '.join(sorted(entities)),
        ', '.join(sorted(merges.keys())),
        ', '.join(sorted(list(entities) + list(merges.keys()))))

    return decl


def generate_code(json_file_path, xml_folder, out_folder, should_generate_stubs):
    generation_timestamp = '''/**
 * This file contains code generated from/to be compatible with available XML data as at {1}
 **/\n'''.format(tab_spaces, str(datetime.datetime.now()))

    entities = {}
    decodable_entities = {}
    terminals = []
    merges = {}
    with open(json_file_path, 'r') as json_file:
        json_data = json.load(json_file)
        for each_name, each_data in json_data['entities'].items():
            each_entity = Entity(each_name, each_data)
            entities[each_name] = each_entity

            if each_entity.has_encodable_state:
                decodable_entities[each_name] = each_entity
        terminals = json_data['terminals']
        merges = json_data['merges']

    resolve_attributes(entities, decodable_entities, xml_folder, should_only_print_warnings)

    file_list = []
    traits_header_list = []

    for entity in sorted(entities.values()):
        tmp = entity.events.values()
        out_path = '{}'.format(entity.name)
        os.makedirs('{}/{}'.format(out_folder, out_path), exist_ok=True)

        # generate base entity traits like the id type and the string associated with the entity
        # generate and write the main event class
        decl, impl = generate_entity_class(entity)
        each_path = '{}/{}.h'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        each_path = '{}/{}.cpp'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(generation_timestamp + impl)

        # generate and write-to-file the eventtype enum
        event_code_map = {each.code: each.name for each in entity.events.values()}
        event_type_enum_name = '{}EventType'.format(entity.name)

        decl, impl = generate_enum(event_type_enum_name, event_code_map)
        each_path = '{}/{}.h'.format(out_path, event_type_enum_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        each_path = '{}/{}.cpp'.format(out_path, event_type_enum_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(generation_timestamp + impl)

        # generate and write the main event class
        decl, impl = generate_event_class(entity, decodable_entities)
        each_path = '{}/{}Event.h'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        each_path = '{}/{}Event.cpp'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(generation_timestamp + impl)

        # generate and write the StateType enum
        state_id_enum_state = '{}StateType'.format(entity.name)
        state_enum_map = {each.code: each.name for each in entity.states.values()}

        decl, impl = generate_enum(state_id_enum_state, state_enum_map,
                                   decode=entity.has_encodable_state)
        each_path = '{}/{}.h'.format(out_path, state_id_enum_state)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        if entity.has_encodable_state:
            each_path = '{}/{}.cpp'.format(out_path, state_id_enum_state)
            file_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
                impl_file.write(generation_timestamp + impl)

        # generate and write the state class
        decl, impl = generate_state_class(entity, decodable_entities)
        each_path = '{}/{}State.h'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        if not entity.has_encodable_state:
            each_path = '{}/{}State.cpp'.format(out_path, entity.name)
            file_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
                impl_file.write(generation_timestamp + impl)

        if should_generate_stubs:
            decl, impl = generate_traits_stub(entity)
            each_path = '{}/{}StateTraits.h'.format(out_path, entity.name)
            file_list.append(each_path)
            traits_header_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
                decl_file.write(generation_timestamp + decl)

            # each_path = '{}/{}StateTraits.cpp'.format(out_path, entity.name)
            # file_list.append(each_path)
            # traits_header_list.append(each_path)
            # with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            #     impl_file.write(generation_timestamp+impl)
        else:
            each_path = '{}/{}StateTraits.h'.format(out_path, entity.name)
            file_list.append(each_path)
            traits_header_list.append(each_path)

            # each_path = '{}/{}StateTraits.cpp'.format(out_path, entity.name)
            # file_list.append(each_path)
            # traits_header_list.append(each_path)

    # now do merges

    for each_name, each_targets in merges.items():
        out_path = '{}'.format(each_name)
        os.makedirs('{}/{}'.format(out_folder, out_path), exist_ok=True)
        event_code_map = {}
        for each_target in map(lambda x: entities[x], each_targets):
            for each_state in each_target.states:
                event_code_map[each_state] = each_state
        state_type_enum_name = '{}StateType'.format(each_name)

        # the new state enum
        decl, impl = generate_enum(state_type_enum_name, event_code_map, False, each_targets)
        each_path = '{}/{}.h'.format(out_path, state_type_enum_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        # the new entity
        # using a fake class
        class fake:
            name = each_name
            has_terminal = all(map(lambda x: entities[x].has_terminal, each_targets))

        decl, impl = generate_entity_class(fake, False, each_targets)
        each_path = '{}/{}.h'.format(out_path, each_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        each_path = '{}/{}.cpp'.format(out_path, each_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(generation_timestamp + impl)

        # the new state class itself
        decl, impl = generate_merge_state_class(entities, each_name, each_targets)
        each_path = '{}/{}State.h'.format(out_path, each_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(generation_timestamp + decl)

        each_path = '{}/{}State.cpp'.format(out_path, each_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(generation_timestamp + impl)

    # now some global stuff

    # an enum for terminals
    decl, impl = generate_enum("TerminalId", {each: each for each in terminals}, decode=True)

    decl += '''
static const int TERMINAL_CODE_LENGTH = {1};
'''.format(tab_spaces, max(map(len, terminals)))

    each_path = 'TerminalId.h'.format(out_path, entity.name)
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    each_path = 'TerminalId.cpp'.format(out_path, entity.name)
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
        impl_file.write(generation_timestamp + impl)

    # write the base template for all traits
    decl = generate_traits_template()
    each_path = 'StateTraits.h'
    file_list.append(each_path)
    traits_header_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    # create a header including all the traits we actually use
    decl = '''#pragma once\n''' + '\n'.join('''#include "{0}"'''.format(each_path) for each_path in traits_header_list)
    each_path = 'implementedTraits.h'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    # create a header for the type lists
    decl = generate_entity_type_lists(entities, merges)
    each_path = 'implementedEntities.h'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    # generate and write out the data extractor
    decl, impl = generate_data_extractor(entities, decodable_entities)
    each_path = 'extractData.h'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    each_path = 'extractData.cpp'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
        impl_file.write(generation_timestamp + impl)

    with open('{}/CMakeLists.txt'.format(out_folder, each_path), 'w') as cmake_file:
        cmake_file.write(generation_timestamp + '''set(GENERATED
{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/{1}
)'''.format(tab_spaces, ('''\n{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/'''.format(tab_spaces)).join(file_list)))


generate_code(json_src_path, glob.glob("{}/*.xml".format(xml_src_path)), code_dst_path, should_generate_stubs)