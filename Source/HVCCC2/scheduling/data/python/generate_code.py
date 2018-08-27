# import sys
import os
import glob
import itertools
from parse_code_file import *
from parse_xml_for_corrections import *

import argparse

parser = argparse.ArgumentParser(description='Generator of C++ code for XML parsing/etc')
parser.add_argument('-c', '--codes-file', type=str, required=True)
parser.add_argument('-x', '--xml-directory', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str, required=True)
parser.add_argument('-s', '--generate_stubs', action='store_true')

args = parser.parse_args()

# todo: generate entity and event-name mappings for the parser, and possibly the parser?
# todo: test things
# note: must be a csv

info_src_path = args.codes_file
xml_src_path = args.xml_directory
code_dst_path = args.output_directory
should_generate_stubs = args.generate_stubs


tab_spaces = ' ' * 4


def generate_enum(enum_name, codemap, decode=True):
    decl = '''#pragma once
#include <string>

enum class {1} {{'''.format(tab_spaces, enum_name)

    decl += ''.join(
        '\n{0}{1},'.format(tab_spaces, each)
        for each in sorted(codemap.values())
    )

    decl += '''
{0}Invalid
}};'''.format(tab_spaces)
    if decode:
        decl += '''

{1} decode{1}(const std::string& enumeratorString);'''.format(tab_spaces, enum_name)

        impl = '''#include "{1}.h"

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
    else:
        impl = None
    return decl, impl


def generate_event_class(entity):
    decl = '''#pragma once
#include <string>
#include "{0}EventType.h"

//forward declare a class to associate with the event
class {0}State;
'''.format(entity.name)

    if 'signalState' in entity.attributes:
        decl += '''
#include "../Signal/SignalStateType.h"'''
    decl += '''
class {1}Event {{
public:
{0}typedef {1}State AssociatedState;
{0}{1}EventType type;
'''.format(tab_spaces, entity.name)

    decl += ''.join(
        '''
{0}{1} {2};'''.format(tab_spaces, entity.attribute_types[each_name], each_name)
        for each_name in sorted(entity.attributes)
    )

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

{0}//STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
}};

template<class Archive>
void {1}Event::serialize(Archive & archive) {{
{0}archive(type, '''.format(tab_spaces, entity.name) + ', '.join(sorted(entity.attributes)) + ''');
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


def generate_state_class(entity):
    # todo: figure out if/how to implement a hasX() system for states

    decl = '''#pragma once
#include <string>
#include "{1}Event.h"
#include "{1}StateType.h"

class {1}State {{
public:
{0}typedef {1}Event AssociatedEvent;
{0}{1}StateType type;
{0}/* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */
'''.format(tab_spaces, entity.name)

    decl += ''.join(
        '''
{0}{1} {2};'''.format(tab_spaces, entity.attribute_types[each_name], each_name)
        for each_name in sorted(entity.attributes)
    )

    decl += '''
{0}{1}State() = default;
{0}static {1}StateType determineNextType({1}StateType stateType, {1}EventType eventType);
{0}template<class Archive>
{0}void serialize(Archive & archive);
}};

template<class Archive>
void {1}State::serialize(Archive & archive) {{
{0}archive(type, '''.format(tab_spaces, entity.name) + ', '.join(sorted(entity.attributes)) + ''');
}'''

    impl = '''#include "{1}State.h"

{1}StateType {1}State::determineNextType({1}StateType stateType, {1}EventType eventType) {{
{0}switch(eventType) {{'''.format(tab_spaces, entity.name)

    impl += ''.join(
        '''
{0}{0}case {1}EventType::{2}:
{0}{0}{0}switch(stateType) {{'''.format(tab_spaces, entity.name, each_event.name) +
        ''.join(
            '''
{0}{0}{0}{0}case {1}StateType::{2}:
{0}{0}{0}{0}{0}return {1}StateType::{3};'''.format(tab_spaces, entity.name, from_state,
                                                   each_event.state_map[from_state] if each_event.state_map[
                                                                                           from_state] is not None else 'Invalid')
            # special handling to create a placeholder for the event for which the CODES.xslx is missing a to-state; so this still "works" until that is clarified
            for from_state in sorted(each_event.state_map)
        ) +
        '''
{0}{0}{0}{0}default:
{0}{0}{0}{0}{0}return {1}StateType::Invalid;
{0}{0}{0}}}'''.format(tab_spaces, entity.name)
        for each_event in sorted(entity.events.values())
    )
    impl += '''
{0}{0}default:
{0}{0}{0}return {1}StateType::Invalid;
{0}}}
}}'''.format(tab_spaces, entity.name)

    return decl, impl

def generate_traits_template():
    decl = '''#pragma once
template<typename State>
class StateTraits {{
public:
{0}typedef typename State::AssociatedEvent AssociatedEvent;
{0}static State initializeFromEvent(const AssociatedEvent& src);
{0}static State generateNextState(const State& current, const AssociatedEvent& event);
}};'''.format(tab_spaces)

    return decl

'''
This generates the stubs for the template specialisations for each type
'''
def generate_traits_stub(entity):
    decl = '''#pragma once
#include "../StateTraits.h"
#include "{1}State.h"
template<>
class StateTraits<{1}State> {{
public:
{0}typedef {1}Event AssociatedEvent;
{0}static {1}State initializeFromEvent(const {1}Event& src);
{0}static {1}State generateNextState(const {1}State& current, const {1}Event& event);
}};'''.format(tab_spaces, entity.name)

    #this is a hackish workaround that I /think/ works but only for current data
    default_state_options = list(filter(lambda x: x in entity.states,['NA', 'Idle', 'Created']))
    default_state = '''{0}StateType::{1}'''.format(entity.name, default_state_options[0]) if default_state_options else 'src.signalState'

    impl = '''#include "{1}StateTraits.h"
    
{1}State StateTraits<{1}State>::initializeFromEvent(const {1}Event& src) {{
{0}/* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
{0}return {{{2}, '''.format(tab_spaces, entity.name, default_state)

    impl += ', '.join(
        '''src.{1}'''.format(tab_spaces, each_name)
        for each_name in filter(lambda x: x != 'type', sorted(entity.attributes))
    )

    impl += '''}};
}}

{1}State StateTraits<{1}State>::generateNextState(const {1}State& current, const {1}Event& event) {{
{0}/* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
{0}{1}State result = current;
{0}result.type = {1}State::determineNextType(current.type, event.type);'''.format(tab_spaces, entity.name)

    for each_name in filter(lambda x: x != 'type', sorted(entity.attributes)):
        impl += '''
{0}if(event.has{1}()) {{
{0}{0}result.{2} = event.{2};
{0}}}'''.format(tab_spaces, each_name[0].upper()+each_name[1:], each_name)

    impl += '''
{0}return result;
}}'''.format(tab_spaces, entity.name)

    return decl, impl

def generate_data_extractor(entities):
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

#include "../../tinyxml2/tinyxml2.h"'''

    decl += ''.join(
        '''
#include "{0}/{0}Event.h"'''.format(each.name)
        for each in sorted(entities.values())
    )

#     decl += '''
#
# class RawEventCollection {
# public:'''
#
#     decl += ''.join(
#         '''
# {0}std::vector<{1}Event> {2}s;'''.format(tab_spaces, each.name, each.name[:1].lower() + each.name[1:])
#         for each in sorted(entities.values())
#     )
#
#     decl += '''
# {0}//note: this method expects the full path to the file (and this will likely standardise better/not need changing when file prompts are used). Temporary/custom path resolution can be in it's own stand alone thing
# {0}tinyxml2::XMLError extractAll(const std::string& srcFilePath);
# }};'''.format(tab_spaces)

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
}}

template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, SignalStateType& destination, const std::string& attributeName) {{
{0}const char* tmp;
{0}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{0}XMLCheckResult(result, 1);
{0}destination = decodeSignalStateType(tmp);
{0}return result;
}}'''.format(tab_spaces, tuple_signature)

    impl = '''#include "extractData.h"
#include <regex>'''.format(tab_spaces)

    for each_entity in sorted(entities.values()):
        extraction_signature = '''tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, {}Event& destination, const std::string& eventTypeCode)'''.format(each_entity.name)
        decl += '''
        
{};'''.format(extraction_signature)

        impl += '''

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {{...extractEvent(source,&destination.x,"attributeTextX")..}} for each attribute
{1} {{
{0}destination.type = decode{2}EventType(eventTypeCode);
{0}if (destination.type == {2}EventType::Invalid) {{
{0}{0}XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
{0}}}
'''.format(tab_spaces, extraction_signature, each_entity.name)
        allEventAttributes = set(next(iter(each_entity.events.values())).attributes)
        for each_event in each_entity.events.values():
            allEventAttributes = allEventAttributes & set(each_event.attributes)
        if allEventAttributes:
            for each_attribute in sorted(allEventAttributes):
                impl += '''
{0}XMLCheckResult(extractAttribute(source, destination.{1}, "{2}"), 0);'''.format(tab_spaces, each_attribute,
                                                                                   each_entity.attribute_codes[
                                                                                       each_attribute])
            impl += '''
'''

        if set(each_entity.attributes) - allEventAttributes:
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
                    impl += '''
{0}{0}{0}XMLCheckResult(extractAttribute(source, destination.{1}, "{2}"), 0);'''.format(tab_spaces, each_attribute,
                                                                                         each_entity.attribute_codes[
                                                                                             each_attribute])
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
        '''if (entityTypeCode == "{1}") {{
{0}{0}{0}{0}XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<{2}Event>>(destination), eventTypeCode), 0);    
{0}{0}{0}}}'''.format(tab_spaces, each.code, each.name)
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

def generate_code(info_file, xml_folder, out_folder, should_generate_stubs):
    entities = parseFile(info_file)
    resolve_types(entities, xml_folder)

    file_list = []

    del entities['Track']
    # del entities['Signal']

    for entity in sorted(entities.values()):
        tmp = entity.events.values()
        out_path = '{}'.format(entity.name)
        os.makedirs('{}/{}'.format(out_folder, out_path), exist_ok=True)

        #lazily set the train's states to the event name for now
        if entity.name == 'Train':
            for each_event in entity.events.values():
                for each_other_event_name in map(cleanUpTrainStateName, entity.events):
                    each_event.state_map[each_other_event_name] = cleanUpTrainStateName(each_event.name)

        #lazily make train states flip-flop
        if entity.name == 'Signal':
            states = list(entity.states)
            next(iter(entity.events.values())).state_map = {states[0]: states[1], states[1]: states[0]}

        # generate and write-to-file the eventtype enum
        event_code_map = {each.code: each.name for each in entity.events.values()}
        event_type_enum_name = '{}EventType'.format(entity.name)

        decl, impl = generate_enum(event_type_enum_name, event_code_map)
        each_path = '{}/{}.h'.format(out_path, event_type_enum_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(decl)

        each_path = '{}/{}.cpp'.format(out_path, event_type_enum_name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(impl)

        # generate and write the main event class
        decl, impl = generate_event_class(entity)
        each_path = '{}/{}Event.h'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(decl)

        each_path = '{}/{}Event.cpp'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(impl)

        # generate and write the StateType enum
        state_id_enum_state = '{}StateType'.format(entity.name)
        state_enum_map = {each: each for each in filter(lambda each: each is not None, entity.states)}

        decl, impl = generate_enum(state_id_enum_state, state_enum_map,
                                   decode=entity.name == 'Signal')
        each_path = '{}/{}.h'.format(out_path, state_id_enum_state)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(decl)

        if entity.name == 'Signal':
            each_path = '{}/{}.cpp'.format(out_path, state_id_enum_state)
            file_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
                impl_file.write(impl)

        # generate and write the state class
        decl, impl = generate_state_class(entity)
        each_path = '{}/{}State.h'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
            decl_file.write(decl)

        each_path = '{}/{}State.cpp'.format(out_path, entity.name)
        file_list.append(each_path)
        with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
            impl_file.write(impl)

        if should_generate_stubs:
            decl, impl = generate_traits_stub(entity)
            each_path = '{}/{}StateTraits.h'.format(out_path, entity.name)
            file_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
                decl_file.write(decl)

            each_path = '{}/{}StateTraits.cpp'.format(out_path, entity.name)
            file_list.append(each_path)
            with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
                impl_file.write(impl)
        else:
            each_path = '{}/{}StateTraits.h'.format(out_path, entity.name)
            file_list.append(each_path)
            each_path = '{}/{}StateTraits.cpp'.format(out_path, entity.name)
            file_list.append(each_path)

    # write the base template for all traits
    decl = generate_traits_template()
    each_path = 'StateTraits.h'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(decl)

    # generate and write out the data extractor
    decl, impl = generate_data_extractor(entities)
    each_path = 'extractData.h'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as decl_file:
        decl_file.write(decl)

    each_path = 'extractData.cpp'
    file_list.append(each_path)
    with open('{}/{}'.format(out_folder, each_path), 'w') as impl_file:
        impl_file.write(impl)

    with open('{}/CMakeLists.txt'.format(out_folder, each_path), 'w') as cmake_file:
        cmake_file.write("""set(GENERATED
{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/{1}
)""".format(tab_spaces, ('\n{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/'.format(tab_spaces)).join(file_list)))


generate_code(info_src_path, glob.glob("{}/*.xml".format(xml_src_path)), code_dst_path, should_generate_stubs)

