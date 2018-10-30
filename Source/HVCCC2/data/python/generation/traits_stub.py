from generation.util import tab


def generate_traits_stub(entity):


    decl_template = '''#pragma once
#include "Entity.h"

//additional implementation logic which is more specific to the particular entity and harder to automate; intended for editing by hand;
class {entity.name}Traits {{
public:
{tab}static {entity.name}::State initializeFromEvent(const {entity.name}::Event& src);

{tab}static {entity.name}::State generateNextState(const {entity.name}::State& current, const {entity.name}Event& event);
}};'''
    
    impl_template = '''#include "Traits.h"
{entity.name}::State {entity.name}Traits::initializeFromEvent(const {entity.name}::Event& src) {{
{tab}/* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
{tab}{entity.name}::State::Type initialState = {initial_state};
{tab}if (initialState == {entity.name}::State::Type::Invalid) {{
{tab}{tab}initialState = {entity.name}::State::Type::{entity.initial_state.name};
{tab}}}
{tab}return {{src.id, initialState, {src_member_list}}};
}}

static {entity.name}::State generateNextState(const {entity.name}::State& current, const {entity.name}Event& event) {{
{tab}/* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
{tab}{entity.name}::State result = current;
{tab}result.type = {entity.name}::State::determineNextType(current.type, event.type);
{conditional_applications}
{tab}return result;
}}'''

    conditional_application_template = '''{tab}if (event.has{pascal_cased_member_name}()) {{
{tab}{tab}result.{member_name} = event.{member_name};
{tab}}}'''

    if entity.has_encodable_state:
        initial_state = '''src.{camel_case_entity_name}State'''.format(camel_case_entity_name=entity.name[0].lower()+entity.name[1:])
    else:
        initial_state = '''{entity.name}::State::determineNextType({entity.name}::State::Type::{entity.initial_state.name}, src.type)'''.format(entity=entity)

    attributes_to_add = sorted(entity.specific_attributes)

    src_member_list = ', '.join(
        '''src.{member_name}'''.format(member_name=each_name)
        for each_name in attributes_to_add
    )

    conditional_applications = '\n{tab}'.format(tab=tab).join(
        conditional_application_template.format(
            tab=tab,
            entity=entity,
            member_name=each_name,
            pascal_cased_member_name=each_name[0].upper()+each_name[1:]
        )
        for each_name in attributes_to_add
    )

    decl = decl_template.format(
        tab=tab,
        entity=entity,
    )
    impl = impl_template.format(
        tab=tab,
        entity=entity,
        initial_state=initial_state,
        src_member_list=src_member_list,
        conditional_applications=conditional_applications
    )
    return decl, impl