/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#pragma once
#include <string>
template<typename State>
class StateTraits {
public:
    static State initializeFromEvent(const typename State::Entity::AssociatedEvent& src);
    static State generateNextState(const State& current, const typename State::Entity::AssociatedEvent& event);
};