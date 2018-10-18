from .util import *
from .enum import *

def generate_event_class(entity, decodable_entities):
    decl_template = '''#pragma once
#include "{entity.name}.h"
{additional_headers}

class {entity.name}Event {{
public:
{tab}using Entity = {entity.name};
{type_enum_decl}
{tab}Entity::Id id;
{tab}Type type;
{tab}{member_declarations};
{tab}{has_member_declarations};
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

{tab}template<class Archive>
{tab}void {entity.name}Event::serialize(Archive & archive) {{
{tab}{tab}archive(id, type, {member_list});
}}'''

    impl_template = '''#include "{entity.name}.h"

{type_enum_impl}

{has_member_impls}
'''
    has_member_decl_template = '''bool has{member_name[0].upper() + member_name[1:]} const'''

    has_member_impl_template = '''bool {entity.name}Event::has{member_name[0].upper() + member_name[1:]}() const {{
{tab}switch(type) {{
{tab}{tab}{cases}
{tab}{tab}default:
{tab}{tab}{tab}return {default_result};
{tab}}}
}}'''

    case_template = '''case {entity.name}EventType::{enumerator}:
{tab}{tab}{tab}return {result};'''

    event_code_map = {each.code: each.name for each in entity.events.values()}

    headers_to_add = sorted(list(entity.attribute_headers))
    if entity.has_encodable_state:
        to_remove = '''"../{entity.name}/Entity.h"'''.format(entity=entity)
        if headers_to_add.count(to_remove):
            headers_to_add.remove(to_remove)

    additional_headers = '\n'.join(
        include_template.format(path=each_path)
        for each_path in headers_to_add
    )

    type_enum_decl, type_enum_impl = generate_enum('Type', '''{entity.name}Event::'''.format(entity=entity), event_code_map, base_tabs='{tab}')

    member_declarations = ';\n{tab}'.join(
        general_declaration_template.format(name=each_name, type=entity.attribute_types[each_name])
        for each_name in sorted(entity.attributes)
    )

    has_member_declarations = ';\n{tab}'.join(
        has_member_decl_template.format(member_name=each_name)
        for each_name in sorted(entity.attributes)
    )

    member_list = ', '.join(sorted(entity.attributes))

    has_member_impls_to_add = []

    for each_attribute in sorted(entity.attributes):
        case_map = {
            "true": [],
            "false": []
        }

        for each_event in sorted(entity.events):
            case_map[("true" if each_attribute in entity.events[each_event].attributes else "false")].append(each_event)

        if case_map["true"] and not case_map["false"]:
            cases = case_template.format(tab=tab, entity=entity, enumerator='Invalid', result='false')
            default_result = 'true'
        else:
            cases = '\n{tab}{tab}'.join(
                case_template.format(tab=tab, entity=entity, enumerator=each_enumerator, result=each_result)
                for each_result, each_enumerator_list in case_map
                    for each_enumerator in each_enumerator_list
            )
            default_result = 'false'

        has_member_impls_to_add.append(
            has_member_impl_template.format(
                tab=tab,
                entity=entity,
                member_name=each_attribute,
                cases=cases,
                default_result=default_result
            )
        )

    has_member_impls = '\n\n'.join(has_member_impls_to_add)

    decl = decl_template.format(
        tab=tab,
        entity=entity,
        additional_headers=additional_headers,
        type_enum_decl=type_enum_decl,
        member_declarations=member_declarations,
        has_member_declarations=has_member_declarations,
        member_list=member_list
    ).format(
        tab=tab,
        entity=entity
    )  # apply it a second time to capture stray tabs etc

    impl = impl_template.format(
        tab=tab,
        entity=entity,
        has_member_impls=has_member_impls,
        type_enum_impl=type_enum_impl
    ).format(
        tab=tab,
        entity=entity
    )  # apply it a second time to capture stray tabs etc

    return decl, impl
