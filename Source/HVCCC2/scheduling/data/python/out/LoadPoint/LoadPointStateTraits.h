#pragma once
#include "../StateTraits.h"
#include "LoadPointState.h"
template<>
class StateTraits<LoadPointState> {
public:
    typedef LoadPointEvent AssociatedEvent;
    static LoadPointState initializeFromEvent(const LoadPointEvent& src);
    static LoadPointState generateNextState(const LoadPointState& current, const LoadPointEvent& event);
};