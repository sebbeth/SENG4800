#! /bin/python3
import os
import glob
import json

from resolve_attributes import *
import argparse
import datetime

from generation.util import *
from generation.cpp_enum import *
from generation.entity_class import *
from generation.id import *
from generation.event import *
from generation.state import *
from generation.merge_state import *
from generation.traits_stub import *
from generation.implemented_entity_list import *
from generation.data_extractor import *

parser = argparse.ArgumentParser(description='Generator of C++ code for XML parsing/etc')
parser.add_argument('-j', '--json-file', type=str, required=True)
parser.add_argument('-x', '--xml-directory', type=str, required=True)
parser.add_argument('-o', '--output-directory', type=str, required=True)
parser.add_argument('-s', '--generate_stubs', action='store_true')
parser.add_argument('-w', '--only_warnings', action='store_true')

args = parser.parse_args()

# todo: generate entity and event-name mappings for the parser, and possibly the parser?
# todo: test things
# note: must be a csv

json_src_path = args.json_file
xml_src_path = args.xml_directory
code_dst_path = args.output_directory
should_generate_stubs = args.generate_stubs
should_only_print_warnings = args.only_warnings


def generate_code(json_file_path, xml_folder, output_root, should_generate_stubs):
    generation_timestamp = '''/**
 * This file contains code generated from/to be compatible with available XML data as at {1}
 **/\n'''.format(tab, str(datetime.datetime.now()))

    entities = {}
    decodable_entities = {}
    terminals = []
    merges = {}
    with open(json_file_path, 'r') as json_file:
        json_data = json.load(json_file)
        for each_name, each_data in json_data['entities'].items():
            each_entity = Entity(each_name, each_data)
            entities[each_name] = each_entity

            if each_entity.has_encodable_state:
                decodable_entities[each_name] = each_entity
        terminals = json_data['terminals']
        merges = json_data['merges']

    resolve_attributes(entities, decodable_entities, xml_folder, should_only_print_warnings)

    file_list = []

    per_entity_path_template = '''{entity.name}/{relative_class_name}.{suffix}'''

    # first generate the Entity class, Id class, Event class, State class, and State-Traits for each entity with events
    for entity in sorted(entities.values()):

        # make a folder for the entity in case it doesn't already exist
        os.makedirs('''{output_root}/{entity.name}'''.format(output_root=output_root, entity=entity), exist_ok=True)

        generated_code_map = {
            'Entity': generate_entity_class(entity),
            'Id': generate_id_class(entity),
            'Event': generate_event_class(entity, decodable_entities),
            'State': generate_state_class(entity, decodable_entities),
        }

        if should_generate_stubs:
            generated_code_map['Traits'] = generate_traits_stub(entity)
        else:
            # add the traits to the file list even if they aren't getting generated/overwritten
            for each_suffix in ['h', 'cpp']:
                file_list.append(per_entity_path_template.format(entity=entity, relative_class_name='Traits', suffix=each_suffix))

        # write the headers and implementation files for each of the generated classes in the generated_code_map
        for each_class_name, (each_decl, each_impl) in generated_code_map.items():
            for each_suffix, each_generated_string in zip(['h', 'cpp'], [each_decl, each_impl]):
                if each_generated_string is not None:  #skip the impl file where it is None
                    each_subpath = per_entity_path_template.format(entity=entity, relative_class_name=each_class_name, suffix=each_suffix)
                    file_list.append(each_subpath)
                    with open('''{output_root}/{each_subpath}'''.format(output_root=output_root, each_subpath=each_subpath), 'w') as each_file:
                        each_file.write(generation_timestamp + each_generated_string)

    # now generate the  Entity class, Id class, and State class for each entity created only by merging others
    for each_name, each_targets in merges.items():
        # the new entity
        # using a 'fake' class
        class entity:
            name = each_name
            has_terminal = all(map(lambda x: entities[x].has_terminal, each_targets))
            has_encodable_state = False

        # make a folder for the entity in case it doesn't already exist
        os.makedirs('''{output_root}/{entity.name}'''.format(output_root=output_root, entity=entity), exist_ok=True)

        generated_code_map = {
            'Entity': generate_entity_class(entity, False),
            'Id': generate_id_class(entity, mergee_names=each_targets),
            'State': generate_merge_state_class(entity, entities, each_targets)
        }

        # write the headers and implementation files for each of the generated classes in the generated_code_map
        for each_class_name, (each_decl, each_impl) in generated_code_map.items():
            for each_suffix, each_generated_string in zip(['h', 'cpp'], [each_decl, each_impl]):
                if each_generated_string is not None:  # skip the impl file where it is None
                    each_subpath = per_entity_path_template.format(entity=entity,
                                                                   relative_class_name=each_class_name,
                                                                   suffix=each_suffix)
                    file_list.append(each_subpath)
                    with open('''{output_root}/{each_subpath}'''.format(output_root=output_root,
                                                                        each_subpath=each_subpath),
                              'w') as each_file:
                        each_file.write(generation_timestamp + each_generated_string)

        out_path = '{}'.format(each_name)

    # now some global stuff

    # an enum for terminals
    decl, impl = generate_enum("TerminalId", {each: each for each in terminals})

    decl += '''
static const int TERMINAL_CODE_LENGTH = {max_string_code_length};
'''.format(max_string_code_length=max(map(len, terminals)))

    each_path = 'TerminalId.h'.format(out_path, entity.name)
    file_list.append(each_path)
    with open('{}/{}'.format(output_root, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + '''#pragma once\n''' + decl)

    each_path = 'TerminalId.cpp'.format(out_path, entity.name)
    file_list.append(each_path)
    with open('{}/{}'.format(output_root, each_path), 'w') as impl_file:
        impl_file.write(generation_timestamp + '''#include "TerminalId.h"\n''' + impl)

    # a header for including all the headers for implemented entities without needing to know which ones they are

    decl = generate_entity_type_lists(entities, merges)
    each_path = 'implementedEntities.h'
    file_list.append(each_path)
    with open('{}/{}'.format(output_root, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    # generate and write out the data extractor
    decl, impl = generate_data_extractor(entities, decodable_entities)
    each_path = 'extractData.h'
    file_list.append(each_path)
    with open('{}/{}'.format(output_root, each_path), 'w') as decl_file:
        decl_file.write(generation_timestamp + decl)

    each_path = 'extractData.cpp'
    file_list.append(each_path)
    with open('{}/{}'.format(output_root, each_path), 'w') as impl_file:
        impl_file.write(generation_timestamp + impl)

    with open('{}/CMakeLists.txt'.format(output_root, each_path), 'w') as cmake_file:
        cmake_file.write(generation_timestamp + '''set(GENERATED
{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/{1}
)'''.format(tab, ('''\n{0}${{CMAKE_CURRENT_SOURCE_DIR}}/python/out/'''.format(tab)).join(file_list)))


generate_code(json_src_path, glob.glob("{}/*.xml".format(xml_src_path)), code_dst_path, should_generate_stubs)