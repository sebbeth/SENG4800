#pragma once
#include "../StateTraits.h"
#include "StackerState.h"
template<>
class StateTraits<StackerState> {
public:
    typedef StackerEvent AssociatedEvent;
    static StackerState initializeFromEvent(const StackerEvent& src);
    static StackerState generateNextState(const StackerState& current, const StackerEvent& event);
};