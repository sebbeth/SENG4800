#pragma once
#include "../StateTraits.h"
#include "TrainState.h"
template<>
class StateTraits<TrainState> {
public:
    typedef TrainEvent AssociatedEvent;
    static TrainState initializeFromEvent(const TrainEvent& src);
    static TrainState generateNextState(const TrainState& current, const TrainEvent& event);
};