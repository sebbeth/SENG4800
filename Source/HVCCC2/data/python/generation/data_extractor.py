from generation.util import tab


def generate_data_extractor(entities, decodable_entities):
    decl_template = '''#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cstdio>

#include "../tinyxml2/tinyxml2.h"

#include "implementedEntities.h"

//This macro prints out an error message if the XMLError holds anything that isn't an tinyxml2::XML_SUCCESS
#ifndef XMLCheckResult
{tab}//#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS){{ std::printf("Error: %i\\n", a_eResult); return a_eResult;}}

{tab}#define XMLCheckResult(a_eResult, doPrint) if (a_eResult != tinyxml2::XML_SUCCESS){{ if (doPrint) {{std::printf("Error: %i\\n", a_eResult); }} return a_eResult;}}
#endif

template<typename Entities...>
using EventVectorTuple = std::tuple<std::vector<Entities>...>;

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode) {{
{tab}Event event;
{tab}tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode);
{tab}XMLCheckResult(result, 1);
{tab}destination.push_back(event);
{tab}return result;
}}

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode, TerminalId theTerminal) {{
{tab}Event event;
{tab}tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode, theTerminal);
{tab}XMLCheckResult(result, 1);
{tab}destination.push_back(event);
{tab}return result;
}}

template<typename T>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, T& destination, const std::string& attributeName) {{
{tab}//hack to get around the bug where QueryAttribute returns an int instead of the enum instance
{tab}tinyxml2::XMLError result = static_cast<tinyxml2::XMLError>(source.QueryAttribute(attributeName.c_str(), &destination));
{tab}XMLCheckResult(result, 1);
{tab}return result;
}}

template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, std::string& destination, const std::string& attributeName) {{
{tab}const char* tmp;
{tab}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{tab}XMLCheckResult(result, 1);
{tab}destination = tmp;
{tab}return result;
}}

{extract_decodable_state_decls}

{event_extraction_method_decls};

tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple<EntitiesWithEvents>& destination);'''

    impl_template = '''#include "extractData.h"

{event_extraction_method_impls}

tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple<EntitiesWithEvents>& destination) {{
{tab}tinyxml2::XMLDocument document;
{tab}tinyxml2::XMLNode* root;
{tab}tinyxml2::XMLElement* eachElement;

{tab}int fileNameIndex = std::max(int(srcFilePath.rfind('/')), int(srcFilePath.rfind('\\\\')))+1;
{tab}std::string terminalName = srcFilePath.substr(fileNameIndex, TERMINAL_CODE_LENGTH);
{tab}TerminalId theTerminal = decodeTerminalId(terminalName); //not that this could easily be null;

{tab}tinyxml2::XMLError eResult = document.LoadFile(srcFilePath.c_str());
{tab}XMLCheckResult(eResult, 0);

{tab}//Set the root pointer to point to the root element; this is different to FirstChild and should skip the xml version declaration node
{tab}root = document.RootElement();
{tab}if (root == nullptr) {{
{tab}{tab}return tinyxml2::XML_ERROR_FILE_READ_ERROR;
{tab}}}

{tab}eachElement = root->FirstChildElement();
{tab}if (eachElement == nullptr) {{
{tab}{tab}return tinyxml2::XML_ERROR_PARSING_ELEMENT;
{tab}}}

{tab}//The program keeps looping until all of the elements have been read:
{tab}while (eachElement != nullptr) {{
{tab}{tab}std::string tagName = eachElement->Name();
{tab}{tab}std::string entityTypeCode, eventTypeCode;
{tab}{tab}std::regex prefixRegex("^[A-Z][a-z]+");
{tab}{tab}std::sregex_iterator regItBegin(tagName.begin(), tagName.end(), prefixRegex);

{tab}{tab}if (regItBegin != std::sregex_iterator()) {{
{tab}{tab}{tab}entityTypeCode = (*regItBegin).str();
{tab}{tab}{tab}eventTypeCode = tagName.substr(entityTypeCode.size());
{tab}{tab}{tab}
{tab}{tab}{tab}{event_extraction_method_calls} else {{
{tab}{tab}{tab}{tab}//state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
{tab}{tab}{tab}{tab}std::printf("Warning: unrecognised tag '%s'\\n", tagName.c_str()); //todo: should probably print a better warning, etc
{tab}{tab}{tab}}}
{tab}{tab}}} else {{
{tab}{tab}{tab}//if it's an element that we know might have children we want, check those instead of assuming it's wrong
{tab}{tab}{tab}if (std::string(tagName.c_str()) == "railEvents" && !eachElement->NoChildren()) {{
{tab}{tab}{tab}{tab}eachElement = eachElement->FirstChildElement();
{tab}{tab}{tab}{tab}continue;
{tab}{tab}{tab}}} else {{
{tab}{tab}{tab}{tab}//state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
{tab}{tab}{tab}{tab}std::printf("Warning: unrecognised tag '%s'\\n", tagName.c_str()); //todo: should probably print a better warning, etc
{tab}{tab}{tab}}}
{tab}{tab}}}
{tab}{tab}//Moves the element pointer to the next event element:
{tab}{tab}tinyxml2::XMLElement* nextElement = eachElement->NextSiblingElement();

{tab}{tab}//if we reach the end of a sublist and there's a parent, move onto that. instead of giving up
{tab}{tab}if (nextElement == nullptr && eachElement->Parent() != nullptr) {{
{tab}{tab}{tab}nextElement = eachElement->Parent()->NextSiblingElement();
{tab}{tab}}}
{tab}{tab}eachElement = nextElement;
{tab}}}
{tab}return tinyxml2::XML_SUCCESS;
}}'''

    extract_decodable_state_decl_template = '''//this is for encoding signalState, if need be
template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, {entity.name}::State::Type& destination, const std::string& attributeName) {{
{tab}const char* tmp;
{tab}tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
{tab}XMLCheckResult(result, 1);
{tab}destination = {entity.name}::State::decodeType(tmp);
{tab}return result;
}}'''

    event_extraction_method_signature_template = '''tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, {entity.name}::Event& destination, const std::string& eventTypeCode{terminal_parameter})'''

    event_extraction_method_impl_template = '''{event_extraction_method_signature} {{
{tab}destination.type = {entity.name}::Event::decodeType(eventTypeCode);
{tab}if (destination.type == {entity.name}::Event::Type::Invalid) {{
{tab}{tab}XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
{tab}}}
{tab}//extract the identifying name
{tab}XMLCheckResult(extractAttribute(source, destination.id.name, "{entity.identifier}"), 0);
{tab}{terminal_addition}
{encodable_state_extraction}
{tab}{attribute_extractions}
}}'''

    event_extraction_method_call_template = '''if (entityTypeCode == {entity.name}::XML_TAG_PREFIX) {{
{tab}{tab}{tab}{tab}extractEvent(*eachElement, std::get<std::vector<{entity.name}::Event>>(destination), eventTypeCode{terminal_argument});
{tab}{tab}{tab}}}'''

    attribute_extraction_method_call_template = '''if (event.has{pascal_cased_member_name}()) {{
{tab}{tab}XMLCheckResult(extractAttribute(source, destination.{member_name}, "{member_code}"), 0);
{tab}}}'''

    encodable_type_extraction_method_call_template = '''if (event.has{entity.name}State()) {{
{tab}{tab}XMLCheckResult(extractAttribute(source, destination.type, "{camel_case_entity_name}State"), 0);
{tab}}}'''


    decl = decl_template.format(
        tab=tab,
        extract_decodable_state_decls='\n\n'.join(
            extract_decodable_state_decl_template.format(
                tab=tab,
                entity=each_entity
            )
            for each_entity in decodable_entities
        ),
        event_extraction_method_decls=';\n\n'.join(
            event_extraction_method_signature_template.format(
                entity=each_entity,
                terminal_parameter=', TerminalId terminal' if each_entity.has_terminal else ''
            )
            for each_entity in sorted(entities.values())
        )
    )

    impl = impl_template.format(
        tab=tab,
        event_extraction_method_impls='\n\n'.join(
            event_extraction_method_impl_template.format(
                tab=tab,
                entity=each_entity,
                event_extraction_method_signature=event_extraction_method_signature_template.format(
                    entity=each_entity,
                    terminal_parameter=', TerminalId terminal' if each_entity.has_terminal else ''
                ),
                terminal_addition='''destination.id.terminal = terminal;''' if each_entity.has_terminal else '',
                encodable_state_extraction=encodable_type_extraction_method_call_template.format(
                    tab=tab,
                    entity=each_entity,
                    camel_case_entity_name=each_entity.name[0].lower() + each_entity.name[1:]
                ) if each_entity.has_encodable_state else '',
                attribute_extractions='''\n{tab}'''.format(tab=tab).join(
                    attribute_extraction_method_call_template.format(
                        tab=tab,
                        entity=each_entity,
                        member_name=each_name,
                        member_code=each_entity.attribute_codes[each_name],
                        pascal_cased_member_name=each_name[0].upper() + each_name[1:]
                    )
                    for each_name in sorted(each_entity.specific_attributes)
                )
            )
            for each_entity in sorted(entities.values())
        ),
        event_extraction_method_calls=''' else '''.format(tab=tab).join(
            event_extraction_method_call_template.format(
                tab=tab,
                entity=each_entity,
                terminal_argument=', terminal' if each_entity.has_terminal else ''
            )
            for each_entity in sorted(entities.values())
        )
    )

    return decl, impl
