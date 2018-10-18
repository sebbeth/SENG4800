#! /bin/python3
import os
import glob
import json
from generation.state import generate_state_class
from resolve_attributes import *
import argparse
import datetime

from .util import *
from .enum import *
from .entity_class import *
from .event import *
from .state import *

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


def generate_merge_state_class(entities, merge_name, merge_target_names):
    entities_to_merge = list(filter(lambda x: x.name in merge_target_names, entities.values()))
    decl = '''#pragma once
#include "{1}.h"
#include "{1}StateType.h"'''.format(tab, merge_name)
    for each_to_merge in entities_to_merge:
        decl += '''
#include "../{1}/{1}State.h"'''.format(tab, each_to_merge.name)

    decl += '''
class {1}State {{
public:
{0}using Entity = {1};
{0}Entity::Id id;
{0}{1}StateType type;'''.format(tab, merge_name)

    seen_attributes = set()
    for each_to_merge in entities_to_merge:
        attributes_to_add = each_to_merge.attributes
        if each_to_merge.has_encodable_state:
            attributes_to_add.remove('''{}State'''.format(each_to_merge.name[0].lower() + each_to_merge.name[1:]))
        for each_attribute in attributes_to_add:
            if not each_attribute in seen_attributes:
                decl += '''
{0}{1} {2};'''.format(tab, each_to_merge.attribute_types[each_attribute], each_attribute)
                seen_attributes.add(each_attribute)
    for each_to_merge in entities_to_merge:
        decl += '''
{0}{1}State(const {2}State& src);'''.format(tab, merge_name, each_to_merge.name)

    decl += '''
    
{0}{1}State() = default;
    
{0}template<class Archive>
{0}void serialize(Archive & archive);
}};

template<class Archive>
void {1}State::serialize(Archive & archive) {{
{0}archive(id, type, '''.format(tab, merge_name) + ', '.join(sorted(attributes_to_add)) + ''');
}}'''.format(tab, merge_name)

    impl = '''#include "{1}State.h"'''.format(tab, merge_name)
    for each_to_merge in entities_to_merge:
        impl += '''
{1}State::{1}State(const {2}State& src): type({1}StateType::Invalid), id({{src.id.terminal, src.id.name}})'''.format(
            tab, merge_name, each_to_merge.name)
        for each_attribute in attributes_to_add:
            impl += ''', {1}(src.{1})'''.format(tab, each_attribute)
        impl += '''{{
{0}switch(src.type) {{'''.format(tab)
        for each_state in each_to_merge.states:
            impl += '''
{0}{0}case {2}StateType::{3}:
{0}{0}{0}type = {1}StateType::{3};
{0}{0}{0}break;'''.format(tab, merge_name, each_to_merge.name, each_state)
        impl += '''
{0}{0}default:
{0}{0}{0}type = {1}StateType::Invalid;
{0}}}
}}'''.format(tab, merge_name)

    return decl, impl


def generate_traits_template():
    decl = '''#pragma once
#include <string>
template<typename State>
class StateTraits {{
public:
{0}static State initializeFromEvent(const typename State::Entity::AssociatedEvent& src);
{0}static State generateNextState(const State& current, const typename State::Entity::AssociatedEvent& event);
}};'''.format(tab)

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
        initial_state_selection = '''{1}StateType::{2}'''.format(tab, entity.name, entity.initial_state.name)

    decl = '''#pragma once
#include "../StateTraits.h"
#include "{1}State.h"
template<>
class StateTraits<{1}State> {{
public:
{0}static {1}State initializeFromEvent(const {1}Event& src) {{
{0}{0}/* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
{0}{0}auto tentativeState = {1}State::determineNextType({2}, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
{0}{0}return {{src.id, tentativeState != {1}StateType::Invalid ? tentativeState : {2}, '''.format(tab, entity.name, initial_state_selection)

    decl += ', '.join(
        '''src.{1}'''.format(tab, each_name)
        for each_name in filter(lambda x: x != 'type', sorted(attributes_to_add))
    )

    decl += '''}};
{0}}}

{0}static {1}State generateNextState(const {1}State& current, const {1}Event& event) {{

{0}{0}/* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
{0}{0}{1}State result = current;'''.format(tab, entity.name)

    # if it has encodable state this will be given by initialising from the event
    if not entity.has_encodable_state:
        decl += '''
{0}{0}result.type = {1}State::determineNextType(current.type, event.type);
'''.format(tab, entity.name)

    for each_name in filter(lambda x: x != 'type', sorted(attributes_to_add)):
        decl += '''
{0}{0}if(event.has{1}()) {{
{0}{0}result.{2} = event.{2};
{0}{0}}}'''.format(tab, each_name[0].upper() + each_name[1:], each_name)

    decl += '''
{0}{0}return result;

{0}}}
}};'''.format(tab)

    return decl, ''


def generate_data_extractor(entities, decodable_entities):
    tuple_signature = '''std::tuple<''' + ', '.join(
        '''
{0}std::vector<{1}Event>'''.format(tab, each_entity.name)
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
}}'''.format(tab, tuple_signature)

    for each_entity in decodable_entities.values():
        decl += '''

template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, {1}StateType& destination, const std::string& attributeName) {{
{0}const char* tmp;
{0}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{0}XMLCheckResult(result, 1);
{0}destination = decode{1}StateType(tmp);
{0}return result;
}}'''.format(tab, each_entity.name)

    impl = '''#include "extractData.h"
#include <regex>'''.format(tab)

    for each_entity in sorted(entities.values()):
        extraction_signature = '''tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, {1}Event& destination, const std::string& eventTypeCode{2})'''.format(
            tab, each_entity.name, ', TerminalId theTerminal' if each_entity.has_terminal else '')
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
'''.format(tab, extraction_signature, each_entity.name, each_entity.identifier)
        if each_entity.has_terminal:
            impl += '''{0}destination.id.terminal = theTerminal;
'''.format(tab)

        allEventAttributes = set(each_entity.attributes)
        for each_event in each_entity.events.values():
            allEventAttributes = allEventAttributes & set(each_event.attributes)
        if allEventAttributes:
            for each_attribute in sorted(allEventAttributes):
                is_id_attr = False
                impl += '''
{0}XMLCheckResult(extractAttribute(source, destination.'''.format(tab)

                if '::Id' in each_entity.attribute_types[each_attribute]:
                    is_id_attr = True
                    impl += 'id.name'
                else:
                    impl += each_attribute

                impl += ''', "{1}"), 0);'''.format(tab, each_entity.attribute_codes[each_attribute])

                if is_id_attr:
                    impl += '''
{0}destination.id.terminal = theTerminal'''.format(tab)

        if set(each_entity.attributes) - allEventAttributes:
            allEventAttributes.add(each_entity.cleaned_identifier)
            # if there are some that aren't in every event type, do those
            impl += '''
{0}switch(destination.type) {{'''.format(tab, each_entity.name)

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
{0}{0}case {1}EventType::{2}:'''.format(tab, each_entity.name, each_event.name)

                for each_attribute in sorted(leftovers):
                    is_id_attr = False
                    impl += '''
{0}{0}{0}XMLCheckResult(extractAttribute(source, destination.'''.format(tab)

                    if '::Id' in each_entity.attribute_types[each_attribute]:
                        is_id_attr = True
                        impl += '{1}.name'.format(tab, each_attribute)
                    else:
                        impl += each_attribute

                    impl += ''', "{1}"), 0);'''.format(tab, each_entity.attribute_codes[each_attribute])

                    if is_id_attr and entities[each_entity.attribute_types[each_attribute].split('::Id')[0]].has_terminal:
                        impl += '''
{0}{0}{0}destination.{1}.terminal = theTerminal;'''.format(tab, each_attribute)
                impl += '''
{0}{0}{0}break;'''.format(tab)
            impl += '''
{0}}}'''.format(tab)
        impl += '''
{0}return tinyxml2::XML_SUCCESS;
}}'''.format(tab)

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
{0}{0}{0}'''.format(tab, extraction_signature)

    impl += ' else '.join(
        ('''if (entityTypeCode == {1}::XML_TAG_PREFIX) {{
{0}{0}{0}{0}extractEvent(*eachElement, std::get<std::vector<{1}Event>>(destination), eventTypeCode''' + (
            ', theTerminal' if each.has_terminal else '') + '''); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
{0}{0}{0}}}''').format(tab, each.name)
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
}}'''.format(tab)

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
#include "{1}/{1}State.h"'''.format(tab, each_name)

    for each_name in merges:
        decl += '''
#include "{1}/{1}.h"
#include "{1}/{1}State.h"'''.format(tab, each_name)

    decl += '''

#define EntitiesWithEvents {1}
#define MergeEntities {2}
#define AllEntities {3}'''.format(
        tab,
        ', '.join(sorted(entities)),
        ', '.join(sorted(merges.keys())),
        ', '.join(sorted(list(entities) + list(merges.keys()))))

    return decl


def generate_code(json_file_path, xml_folder, out_folder, should_generate_stubs):
    generation_timestamp = '''/**
 * This file contains code generated from/to be compatible with available XML data as at {1}
 **/\n'''.format(tab, str(datetime.datetime.now()))

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
'''.format(tab, max(map(len, terminals)))

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
)'''.format(tab, ('''\n{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/'''.format(tab)).join(file_list)))


generate_code(json_src_path, glob.glob("{}/*.xml".format(xml_src_path)), code_dst_path, should_generate_stubs)