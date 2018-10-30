from generation.util import *


def generate_enum(enum_name,  codemap, function_scope='', decode=True, encode=None, base_tabs=''):
    # default to implementing an encode if we're decoding
    if encode is None:
        encode = decode

    decl_template = '''{base_tabs}enum {enum_name} {{
{base_tabs}{tab}{value_list},
{base_tabs}{tab}Invalid
{base_tabs}}};
{base_tabs}{decode_decl}
{base_tabs}{encode_decl}'''

    decode_impl_template = '''{function_scope}{enum_name} {function_scope}decode{enum_name}(const std::string& string) {{
{tab}{if_chains} else {{
{tab}{tab}return Invalid;
{tab}}}
}}'''

    encode_impl_template = '''std::string {function_scope}encode{enum_name}({enum_name} value) {{
{tab}switch(value) {{
{tab}{tab}{cases}
{tab}{tab}default:
{tab}{tab}{tab}return "Invalid";
{tab}}}
}}'''

    if_template = '''if (string == "{each_code}") {{
{tab}{tab}return {each_value};
{tab}}}'''

    case_template = '''case {each_value}:
{tab}{tab}{tab}return "{each_code}";'''

    value_list = ',\n{base_tabs}{tab}'.format(base_tabs=base_tabs, tab=tab).join(sorted(codemap.values()))

    impls = []

    if decode:
        decode_decl = '''{enum_name} decode{enum_name}(const std::string& string);'''.format(enum_name=enum_name)
        impls.append(
            decode_impl_template.format(
                tab=tab,
                enum_name=enum_name,
                function_scope=function_scope,
                if_chains=''' else '''.join(
                    if_template.format(tab=tab, each_code=each_code, each_value=each_value)
                    for each_code, each_value in sorted(codemap.items())
                )
            )
        )
    else:
        decode_decl = '''//{enum_name} is not decodable'''.format(enum_name=enum_name)

    if encode:
        encode_decl = '''std::string encode{enum_name}({enum_name});'''.format(enum_name=enum_name)
        impls.append(
            encode_impl_template.format(
                tab=tab,
                enum_name=enum_name,
                function_scope=function_scope,
                cases='''\n{tab}{tab}'''.format(tab=tab).join(
                    case_template.format(tab=tab, each_code=each_code, each_value=each_value)
                    for each_code, each_value in sorted(codemap.items())
                )
            )
        )
    else:
        encode_decl = '''//{enum_name} is not encodable'''.format(enum_name=enum_name)

    decl = decl_template.format(
        base_tabs=base_tabs,
        tab=tab,
        enum_name=enum_name,
        value_list=value_list,
        decode_decl=decode_decl,
        encode_decl=encode_decl
    )

    impl = '\n'.join(impls)

    return decl, impl
