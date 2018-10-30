from generation.util import *
from generation.cpp_enum import *


def generate_state_class(entity, encodable_entities):
    # todo: figure out if/how to implement a hasX() system for states

    decl_template = '''#pragma once
#include "Entity.h"
{additional_headers}

class {entity.name}State {{
public:
{type_enum_decl}

{tab}using Entity = {entity.name};

{tab}Entity::Id id;
{tab}Type type;
{tab}{member_declarations};
{tab}{next_type_determination_decl}
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

template<class Archive>
void {entity.name}State::serialize(Archive & archive) {{
{tab}archive(id, type, {member_list});
}}'''

    impl_template = '''#include "State.h"

{type_enum_impl}
{next_type_determination_impl}'''

    next_type_determination_decl_template = '''Type determineNextType({entity.name}::State::Type stateType, {entity.name}::Event::Type eventType);'''.format(entity=entity)

    next_type_determination_impl_template = '''#include "State.h"
{entity.name}::State::Type {entity.name}::State::determineNextType({entity.name}::State::Type stateType, {entity.name}::Event::Type eventType) {{
{tab}using Event = {entity.name}::Event;
{tab}switch(stateType) {{
{tab}{tab}{state_cases}
{tab}{tab}default:
{tab}{tab}{tab}return Invalid;
{tab}}}
}}'''

    state_case_template = '''case {state_type}:
{tab}{tab}{tab}switch(eventType) {{
{tab}{tab}{tab}{tab}{event_cases}
{tab}{tab}{tab}{tab}default:
{tab}{tab}{tab}{tab}{tab}return Invalid;
{tab}{tab}{tab}}}'''

    event_case_template = '''case Event::{event_type}:
{tab}{tab}{tab}{tab}{tab}return {result};'''

    state_code_map = {each.code: each.name for each in entity.states.values()}

    headers_to_add = sorted(list(entity.attribute_headers))
    to_remove = '''"../{entity.name}/Entity.h"'''.format(entity=entity)
    if headers_to_add.count(to_remove):
        headers_to_add.remove(to_remove)

    # we don't want the state attribute for state classes since it's covered by type; even though we did for events
    attributes_to_add = sorted(entity.specific_attributes)
    additional_headers = '\n'.join(
        include_template.format(path=each_path)
        for each_path in headers_to_add
    )

    type_enum_decl, type_enum_impl = generate_enum(
        'Type',
        state_code_map,
        function_scope='''{entity.name}State::'''.format(entity=entity),
        base_tabs='{tab}'.format(tab=tab)
    )

    member_declarations = ''';\n{tab}'''.format(tab=tab).join(
        general_declaration_template.format(name=each_name, type=entity.attribute_types[each_name])
        for each_name in attributes_to_add
    )

    member_list = ', '.join(attributes_to_add)

    if entity.has_encodable_state:
        next_type_determination_decl = '''//{next_type_determination_decl_template} is not implemented as the state is directly encoded into event data'''.format(next_type_determination_decl_template=next_type_determination_decl_template)
        next_type_determination_impl = ''
    else:
        next_type_determination_decl = next_type_determination_decl_template  # leave resolution of tabs and entity.name for the final pass
        next_type_determination_impl = next_type_determination_impl_template.format(
            tab=tab,
            entity=entity,
            state_cases='''\n{tab}{tab}'''.format(tab=tab).join(
                state_case_template.format(
                    tab=tab,
                    entity=entity,
                    state_type=each_state.name,
                    event_cases='''\n{tab}{tab}{tab}{tab}'''.format(tab=tab).join(
                        event_case_template.format(
                            tab=tab,
                            event_type=each_event.name,
                            result=each_destination_state.name
                        )
                        for each_event, each_destination_state in sorted(each_state.transitions.items())
                    )
                )
                for each_state in sorted(entity.states.values())
            )
        )

    decl = decl_template.format(
        tab=tab,
        entity=entity,
        additional_headers=additional_headers,
        type_enum_decl=type_enum_decl,
        member_declarations=member_declarations,
        next_type_determination_decl=next_type_determination_decl,
        member_list=member_list
    )

    impl = impl_template.format(
        type_enum_impl=type_enum_decl,
        next_type_determination_impl=next_type_determination_impl
    )

    return decl, impl
