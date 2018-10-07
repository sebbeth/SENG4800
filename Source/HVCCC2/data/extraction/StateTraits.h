/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include <string>
template<typename State>
class StateTraits {
public:
    static State initializeFromEvent(const typename State::Entity::AssociatedEvent& src);
    static State generateNextState(const State& current, const typename State::Entity::AssociatedEvent& event);
};