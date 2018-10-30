#! /bin/python3

from .util import *
'''Deprecated'''
def generate_traits_template():
    decl = '''#pragma once
#include <string>
template<typename State>
class StateTraits {{
public:
{tab}static State initializeFromEvent(const typename State::Entity::AssociatedEvent& src);
{tab}static State generateNextState(const State& current, const typename State::Entity::AssociatedEvent& event);
}};'''.format(tab=tab)

    return decl, None