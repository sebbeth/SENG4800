from .util import *

def generate_entity_id(entity):
    decl_template = '''#pragma once
#include <string>
{terminal_id_include}
#include "../../util.h"

class {entity.name}Id {{
public:
{tab}using Entity = {entity.name};
{tab}{member_declarations};
{tab}Id();
{tab}Id({member_parameters});
{tab}std::string nameForBinaryFile() const;
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

bool operator<(const {entity.name}::Id& a, const {entity.name}::Id& b);
bool operator==(const {entity.name}::Id& a, const {entity.name}::Id& b);
bool operator!=(const {entity.name}::Id& a, const {entity.name}::Id& b);
'''

    impl_template = '''
#include "{entity.name}Id.h"

{entity.name}Id::{entity.name}Id(): {member_defaults} {{
}}

{entity.name}Id::{entity.name}Id({member_parameters}): {member_initialisations} {{
}}

bool operator<(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return {lt_compares};
}}

bool operator==(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return {eq_compares};
}}

bool operator!=(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return !(a == b);
}}

bool operator<=(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return (a < b) || (a == b);
}}

bool operator>(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return !(a < b) && (a != b)
}}

bool operator>=(const {entity.name}::Id& a, const {entity.name}::Id& b) {{
{tab}return (a == b) || !(a < b)
}}

'''
    members = {'name': 'std::string'}
    param_types = {
        'name': 'const std::string&',
        'terminal': 'terminal'
    }
    member_default_values = {
        'name': '',
        'terminal': 'TerminalId::Invalid'
    }
    if entity.has_terminal:
        terminal_id_include = include_template.format(path='../TerminalId.h')
        members['terminal'] = 'TerminalId'
    else:
        terminal_id_include = '''//TerminalId is not used'''

    member_declarations = ';\n{tab}'.join(
        general_declaration_template.format(name=each_name, type=each_type)
        for each_name, each_type in members.items()
    )

    member_parameters = ', '.join(
        general_declaration_template.format(name=each_name, type=each_type)
        for each_name, each_type in param_types.items()
    )

    member_defaults = ', '.join(
        '''{each_name}({each_value})'''.format(each_name=each_name,each_value=each_value)
        for each_name, each_value in member_default_values.items()
    )

    member_initialisations = ', '.join(
        '''{each_name}({each_name})'''.format(each_name=each_name)
        for each_name in members.keys()
    )

    lt_compares = '''{terminal_equality}(a.name == b.name)'''.format(
        terminal_equality='''a.terminal < b.terminal || ''' if entity.has_terminal else ''
    )

    eq_compares = ' && '.join(
        '''a.{each_member} == b.{each_member}'''.format(each_member=each_member)
        for each_member in members.keys()
    )

    decl = decl_template.format(
        entity=entity,
        terminal_id_include=terminal_id_include,
        member_declarations=member_declarations,
        member_parameters=member_parameters
    ).format(
        tab=tab,
        entity=entity
    )  # apply a second time to capture stray tabs etc

    impl = impl_template.format(
        tab=tab,
        entity=entity,
        member_defaults=member_defaults,
        member_parameters=member_parameters,
        member_initialisations=member_initialisations,
        lt_compares=lt_compares,
        eq_compares=eq_compares
    ).format(
        tab=tab,
        entity=entity
    )  # apply a second time to capture stray tabs etc

    return decl, impl
