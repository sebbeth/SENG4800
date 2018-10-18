from .util import *
def generate_entity_class(entity, has_event=True, merge_targets=None):
    decl_template = '''#pragma once
#include <string>
#include "../../util.h"

//some forward declarations
{forward_declarations}

class {entity.name} {{
{tab}static const std::string ENTITY_NAME;
{tab}static const std::string XML_TAG_PREFIX;
{tab}{type_defs}
{tab}{comments}
}};

/*
{tab}these includes will work after the above has been defined, such that you only ever need to include this header to access all of them.
{tab}"backward" as in not-forward
*/
{backward_includes}
'''
    forwards_to_declare = []
    relative_backwards_to_include = []
    backward_merges_to_include = []
    relative_forwards_to_declare = ['State', 'Id']
    comments_to_add = [
        '//State::Type is an enum',
        '//Id.name is an std::string'
    ]
    types_to_def = {}

    # conditional inclusions

    if entity.has_terminal:
        comments_to_add.append('//Id.terminal is a TerminalId')
    else:
        comments_to_add.append('//Id.terminal is NOT defined')

    if has_event:
        relative_forwards_to_declare += ['Event']
        comments_to_add.append('//Event::Type is an enum')
    else:
        comments_to_add += [
            '//Event is NOT defined',
            '//Event::Type is NOT defined'
        ]

    # explicitly identify merge targets

    if merge_targets:
        types_to_def['Mergees'] = '''TypeList<{types}>'''.format(types=', '.join(merge_targets))

        backward_merges_to_include = [
            '''"../{each_mergee}/Entity.h"'''.format(each_mergee=each_mergee)
            for each_mergee in merge_targets
        ]

    else:
        comments_to_add.append('//Does not merge other entities')

    # content for types directly related to the entity such as events and states

    for each_relative in relative_forwards_to_declare:
        full_class_name = '''{entity.name}{each_relative}'''.format(each_relative=each_relative, entity=entity)
        forwards_to_declare.append(full_class_name)
        types_to_def[each_relative] = full_class_name
        relative_backwards_to_include.append('''"{each_relative}.h"'''.format(each_relative=each_relative))

    # apply templates to the lists
    forward_declarations = '\n'.join(
        forward_template.format(class_name=each_to_declare)
        for each_to_declare in forwards_to_declare+merge_targets
    )

    type_defs = '''\n{tab}'''.join(
        typedef_template.format(alias=each_alias, target=each_target)
        for each_alias, each_target in types_to_def.items()
    )

    backward_includes = '''\n'''.join(
        include_template.format(path=each_path)
        for each_path in relative_backwards_to_include+backward_merges_to_include
    )

    comments = '''\n{tab}'''.join(
        comments_to_add
    )

    # apply the overall templates;
    decl = decl_template.format(
        tab=tab,
        entity=entity,
        forward_declarations=forward_declarations,
        type_defs=type_defs,
        comments=comments,
        backward_includes=backward_includes
    ).format(
        tab=tab,
        entity=entity
    )  # apply a second time to capture stray tabs etc
    impl = None

    return decl, impl
