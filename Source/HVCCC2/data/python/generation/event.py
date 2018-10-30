from .util import *
from .cpp_enum import *

def generate_event_class(entity, decodable_entities):
    decl_template = '''#pragma once
#include "Entity.h"
{additional_headers}

class {entity.name}Event {{
public:
{type_enum_decl}

{tab}using Entity = {entity.name};

{tab}Entity::Id id;
{tab}Type type;
{tab}{member_declarations};
{tab}{has_member_declarations};
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

template<class Archive>
void {entity.name}Event::serialize(Archive & archive) {{
{tab}archive(id, type, {member_list});
}}'''

    impl_template = '''#include "Event.h"

{type_enum_impl}

{has_member_impls}'''
    has_member_decl_template = '''bool has{pascal_cased_member_name}() const'''

    has_member_impl_template = '''bool {entity.name}Event::has{pascal_cased_member_name}() const {{
{tab}switch(type) {{
{tab}{tab}{cases}
{tab}{tab}default:
{tab}{tab}{tab}return {default_result};
{tab}}}
}}'''

    case_template = '''case {entity.name}::Event::Type::{enumerator}:
{tab}{tab}{tab}return {result};'''

    event_code_map = {each.code: each.name for each in entity.events.values()}

    headers_to_add = sorted(list(entity.attribute_headers))
    to_remove = '''"../{entity.name}/Entity.h"'''.format(entity=entity)
    if headers_to_add.count(to_remove):
        headers_to_add.remove(to_remove)

    # for events we want the state attribute to stick for encodables; but that won't be the case for states
    attributes_to_add = sorted(entity.attributes)

    additional_headers = '\n'.join(
        include_template.format(path=each_path)
        for each_path in sorted(headers_to_add)
    )

    type_enum_decl, type_enum_impl = generate_enum('Type', event_code_map, function_scope='''{entity.name}Event::'''.format(entity=entity), base_tabs='{tab}'.format(tab=tab))

    member_declarations = ''';\n{tab}'''.format(tab=tab).join(
        general_declaration_template.format(name=each_name, type=entity.attribute_types[each_name])
        for each_name in attributes_to_add
    )

    has_member_declarations = ''';\n{tab}'''.format(tab=tab).join(
        has_member_decl_template.format(
            member_name=each_name,
            pascal_cased_member_name=each_name[0].upper()+each_name[1:]
        )
        for each_name in attributes_to_add
    )

    member_list = ', '.join(attributes_to_add)

    has_member_impls_to_add = []

    for each_attribute in attributes_to_add:
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
            cases = '''\n{tab}{tab}'''.format(tab=tab).join(
                case_template.format(tab=tab, entity=entity, enumerator=each_enumerator, result=each_result)
                for each_result, each_enumerator_list in sorted(case_map.items())
                    for each_enumerator in sorted(each_enumerator_list)
            )
            default_result = 'false'

        has_member_impls_to_add.append(
            has_member_impl_template.format(
                tab=tab,
                entity=entity,
                member_name=each_attribute,
                pascal_cased_member_name=each_attribute[0].upper()+each_attribute[1:],
                cases=cases,
                default_result=default_result
            )
        )

    has_member_impls = '\n\n'.join(sorted(has_member_impls_to_add))

    decl = decl_template.format(
        tab=tab,
        entity=entity,
        additional_headers=additional_headers,
        type_enum_decl=type_enum_decl,
        member_declarations=member_declarations,
        has_member_declarations=has_member_declarations,
        member_list=member_list
    )

    impl = impl_template.format(
        tab=tab,
        entity=entity,
        has_member_impls=has_member_impls,
        type_enum_impl=type_enum_impl
    )
    return decl, impl
