from generation.util import *

def generate_id_class(entity, mergee_names=[]):
    decl_template = '''#pragma once
#include <string>
#include "../../util.h"
#include "Entity.h"
{terminal_id_include}
{additional_headers}

class {entity.name}Id {{
public:
{tab}using Entity = {entity.name};
{tab}{member_declarations};
{tab}{entity.name}Id();
{tab}{entity.name}Id({member_parameters});
{merging_constructor_decls}
{tab}std::string nameForBinaryFile() const;
{tab}template<class Archive>
{tab}void serialize(Archive & archive);
}};

template<class Archive>
void {entity.name}Id::serialize(Archive & archive) {{
{tab}archive({member_list});
}}

bool operator<(const {entity.name}::Id& a, const {entity.name}::Id& b);
bool operator==(const {entity.name}::Id& a, const {entity.name}::Id& b);
bool operator!=(const {entity.name}::Id& a, const {entity.name}::Id& b);'''

    impl_template = '''
#include "Id.h"

{entity.name}Id::{entity.name}Id(): {member_defaults} {{
}}

{entity.name}Id::{entity.name}Id({member_parameters}): {member_initializations} {{
}}

{merging_constructor_impls}

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
}}'''

    merging_constructor_decl_template = '''{tab}{entity.name}Id(const {mergee_name}::Id& src);'''

    merging_constructor_impl_template = '''{entity.name}Id::{entity.name}Id(const {mergee_name}::Id& src): {src_member_initializations} {{
}}'''

    src_member_initialization_template = '''{member_name}(src.member_name)'''

    attributes = {'name': 'std::string'}
    param_types = {
        'name': 'const std::string&',
        'terminal': 'TerminalId'
    }
    member_default_values = {
        'name': '',
        'terminal': 'TerminalId::Invalid'
    }

    if entity.has_terminal:
        terminal_id_include = include_template.format(path='"../TerminalId.h"')
        attributes['terminal'] = 'TerminalId'
    else:
        terminal_id_include = '''//TerminalId is not used'''

    additional_headers = '\n'.join(
        include_template.format(path='''"../{each_mergee_name}/Entity.h"'''.format(each_mergee_name=each_mergee_name))
        for each_mergee_name in sorted(mergee_names)
    )

    member_declarations = ''';\n{tab}'''.format(tab=tab).join(
        general_declaration_template.format(name=each_name, type=each_type)
        for each_name, each_type in sorted(attributes.items())
    )
    member_parameters = ', '.join(
        general_declaration_template.format(name=each_name, type=each_type)
        for each_name, each_type in sorted(param_types.items())
    )

    merging_constructor_decls = '''\n'''.join(
        merging_constructor_decl_template.format(
            tab=tab,
            entity=entity,
            mergee_name=each_name
        )
        for each_name in sorted(mergee_names)
    )

    member_list = ', '.join(sorted(attributes))

    member_defaults = ', '.join(
        '''{each_name}({each_value})'''.format(each_name=each_name,each_value=each_value)
        for each_name, each_value in sorted(member_default_values.items())
    )

    member_initializations = ', '.join(
        '''{each_name}({each_name})'''.format(each_name=each_name)
        for each_name in sorted(attributes.keys())
    )

    merging_constructor_impls = '\n\n'.join(
        merging_constructor_impl_template.format(
            tab=tab,
            entity=entity,
            mergee_name=each_mergee_name,
            src_member_initializations=', '.join(
                src_member_initialization_template.format(
                    member_name=each_member_name
                )
                for each_member_name in sorted(attributes)
            )
        )
        for each_mergee_name in sorted(mergee_names)
    )

    lt_compares = '''{terminal_equality}(a.name == b.name)'''.format(
        terminal_equality='''a.terminal < b.terminal || ''' if entity.has_terminal else ''
    )

    eq_compares = ' && '.join(
        '''a.{each_member} == b.{each_member}'''.format(each_member=each_member)
        for each_member in sorted(attributes.keys())
    )

    decl = decl_template.format(
        tab=tab,
        entity=entity,
        terminal_id_include=terminal_id_include,
        additional_headers=additional_headers,
        member_declarations=member_declarations,
        member_parameters=member_parameters,
        merging_constructor_decls=merging_constructor_decls,
        member_list=member_list
    )

    impl = impl_template.format(
        tab=tab,
        entity=entity,
        member_defaults=member_defaults,
        member_parameters=member_parameters,
        member_initializations=member_initializations,
        merging_constructor_impls=merging_constructor_impls,
        lt_compares=lt_compares,
        eq_compares=eq_compares
    )

    return decl, impl
