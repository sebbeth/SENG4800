from .util import *


def generate_enum(enum_name, function_scope, codemap, decode=True, encode=None, base_tabs=''):
    # default to implementing an encode if we're decoding
    if encode is None:
        encode = decode

    decl_template = '''
{base_tabs}enum {enum_name} {{
{base_tabs}{tab}{value_list}
{base_tabs}}};
{base_tabs}{decode_decl}
{base_tabs}{encode_decl}
'''

    decode_impl_template = '''{enum_name} {function_scope}decode{enum_name}(const std::string& string) {{
{tab}using {function_scope}{using_list};
{tab}{if_chains}
{tab}}} else {{
{tab}{tab}return Invalid;
{tab}}}
}}
'''

    encode_impl_template = '''std::string {function_scope}encode{enum_name}({enum_name} value) {{
{tab}using {function_scope}{using_list};
{tab}switch(value) {{
{tab}{tab}{cases}
{tab}{tab}default:
{tab}{tab}{tab}return "Invalid";
{tab}}}
}}
'''

    if_template = '''if (string == "{each_code}") {{
{tab}{tab}return {each_value};
{tab}}}
'''

    case_template = '''case {each_value}:
{tab}{tab}{tab}return "{each_code}";'''

    value_list = ',\n{base_tabs}{tab}'.join(codemap.keys())
    using_list = ',\n{base_tabs}{tab}{function_scope}'.join(codemap.keys())

    impls = []

    if decode:
        decode_decl = '''{enum_name} decode{enum_name}(const std::string& string);'''
        impls.append(
            decode_impl_template.format(
                tab=tab,
                enum_name=enum_name,
                function_scope=function_scope,
                using_list=using_list,
                if_chains='''\n{tab}}} else'''.join(
                    if_template.format(tab=tab, each_code=each_code, each_value=each_value)
                    for each_code, each_value in codemap
                )
            )
        )
    else:
        decode_decl = '''//{enum_name} is not decodable'''

    if encode:
        encode_decl = '''std::string encode{enum_name}({enum_name});'''
        impls.append(
            encode_impl_template.format(
                tab=tab,
                enum_name=enum_name,
                function_scope=function_scope,
                using_list=using_list,
                cases='\n{tab}{tab}'.join(
                    case_template.format(tab=tab, each_code=each_code, each_value=each_value)
                    for each_code, each_value in codemap
                )
            )
        )
    else:
        encode_decl = '''//{enum_name} is not encodable'''

    decl = decl_template.format(
        base_tabs=base_tabs,
        tab=tab,
        enum_name=enum_name,
        value_list=value_list,
        decode_decl=decode_decl,
        encode_decl=encode_decl
    ).format(
        tab=tab,
        base_tabs=base_tabs,
        enum_name=enum_name,
        function_scope=function_scope
    )  # apply it a second time to capture stray tabs etc

    impl = '\n'.join(impls).format(
        tab=tab,
        enum_name=enum_name
    )  # apply it a second time to capture stray tabs etc

    return decl, impl
