#pragma once
#include "../StateTraits.h"
#include "SignalState.h"
template<>
class StateTraits<SignalState> {
public:
    typedef SignalEvent AssociatedEvent;
    static SignalState initializeFromEvent(const SignalEvent& src);
    static SignalState generateNextState(const SignalState& current, const SignalEvent& event);
};