#pragma once
#include "../StateTraits.h"
#include "ReclaimerState.h"
template<>
class StateTraits<ReclaimerState> {
public:
    typedef ReclaimerEvent AssociatedEvent;
    static ReclaimerState initializeFromEvent(const ReclaimerEvent& src);
    static ReclaimerState generateNextState(const ReclaimerState& current, const ReclaimerEvent& event);
};