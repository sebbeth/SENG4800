from generation.util import *
from generation.cpp_enum import *


def generate_merge_state_class(entity, entities, mergee_names):
    decl_template = '''#pragma once
#include "Entity.h"
{merge_headers}

class {entity.name}State {{
public:
{tab}using Entity = {entity.name};
{type_enum_decl}
{tab}Entity::Id id;
{tab}Type type;
{tab}{member_declarations};
{tab}{merging_constructor_decls};
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

template<class Archive>
void {entity.name}State::serialize(Archive & archive) {{
{tab}archive(id, type, {member_list});
}}'''

    impl_template = '''#include "State.h"

{type_enum_impl}
{merging_constructor_impls}'''

    merging_constructor_decl_template = '''{entity.name}State(const {mergee.name}::State& src)'''

    merging_constructor_impl_template = '''{entity.name}State::{entity.name}State(const {mergee.name}::State& src): type({entity.name}State::Type::Invalid), id(src.id), {member_initializations} {{
{tab}switch(src.type) {{
{tab}{tab}{cases}
{tab}{tab}default:
{tab}{tab}{tab}return Invalid;
{tab}}}
}}'''

    member_initializations_template = '''{member_name}(src.{member_name})'''

    case_template = '''case {mergee.name}::State::{state_name}:
{tab}{tab}{tab}return {state_name};'''

    mergees = list(map(lambda each_name: entities[each_name], mergee_names))

    # this gets a set of all (usable) attributes in the mergees, in (name, type format)
    attributes = list(
        set.union(
            set(
                [
                    each_inner
                    for each_outer in map(
                        lambda each_mergee: filter(
                            lambda x: x[0] != each_mergee.cleaned_identifier,
                            each_mergee.attribute_types.items()
                        ),
                        mergees
                    )
                        for each_inner in each_outer
                ]
            )
        )
    )

    attributes_to_add = sorted(attributes)
    # don't duplicate the statetype if the state is encodable
    if entity.has_encodable_state:
        to_remove = '''{entity.name[0].lower() + entity.name[1:]}State'''.format(entity=entity)
        if attributes_to_add.count(to_remove):
            attributes_to_add.remove(to_remove)
    states = list(
        set.union(
            *list(set(list(each_mergee.states.values()))
                for each_mergee in mergees)
        )
    )
    state_code_map = {each.code: each.name for each in sorted(states)}

    merge_headers = '\n'.join(
        include_template.format(path='''"../{each_mergee.name}/Entity.h"'''.format(each_mergee=each_mergee))
        for each_mergee in sorted(mergees)
    )

    type_enum_decl, type_enum_impl = generate_enum(
        'Type',
        state_code_map,
        function_scope='''{entity.name}State::'''.format(entity=entity),
        base_tabs='{tab}'.format(tab=tab)
    )

    member_declarations = ''';\n{tab}'''.format(tab=tab).join(
        general_declaration_template.format(name=each_name, type=each_type)
        for each_name, each_type in attributes_to_add
    )

    merging_constructor_decls = ''';\n{tab}'''.format(tab=tab).join(
        merging_constructor_decl_template.format(
            entity=entity,
            mergee=each_mergee
        )
        for each_mergee in sorted(mergees)
    )

    member_list = ', '.join(
        each_name
        for each_name, _ in attributes_to_add
    )

    merging_constructor_impls='\n\n'.join(
        merging_constructor_impl_template.format(
            tab=tab,
            entity=entity,
            mergee=each_mergee,
            member_initializations=', '.join(
                member_initializations_template.format(member_name=each_name)
                for each_name, _ in attributes_to_add
            ),
            cases='''\n{tab}{tab}'''.format(tab=tab).join(
                case_template.format(
                    tab=tab,
                    mergee=each_mergee,
                    state_name=each_state_name
                )
                for each_state_name in each_mergee.states
            )
        )
        for each_mergee in sorted(mergees)
    )

    decl = decl_template.format(
        tab=tab,
        entity=entity,
        merge_headers=merge_headers,
        type_enum_decl=type_enum_decl,
        member_declarations=member_declarations,
        merging_constructor_decls=merging_constructor_decls,
        member_list=member_list
    )

    impl = impl_template.format(
        type_enum_impl=type_enum_impl,
        merging_constructor_impls=merging_constructor_impls
    )

    return decl, impl
