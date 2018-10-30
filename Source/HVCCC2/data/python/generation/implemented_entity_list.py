from generation.util import *

def generate_entity_type_lists(entities, merges):
    decl_template = '''#pragma once
#include "../util.h"
#include <map>
#include <tuple>

{entity_includes}

#define EntitiesWithEvents {entities_with_events}
#define MergeEntities {merges}
#define AllEntities {all_entities}
'''

    decl = decl_template.format(
        entity_includes='\n'.join(
            include_template.format(
                path='''"{entity_name}/Entity.h"'''.format(
                    entity_name=each_name
                )
            )
            for each_name in sorted(list(entities.keys())+list(merges.keys()))
        ),
        entities_with_events=', '.join(
            sorted(entities.keys())
        ),
        merges=', '.join(
            sorted(merges.keys())
        ),
        all_entities=', '.join(
            sorted(list(entities.keys())+list(merges.keys()))
        )
    )

    return decl