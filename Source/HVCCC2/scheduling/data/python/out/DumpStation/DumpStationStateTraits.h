#pragma once
#include "../StateTraits.h"
#include "DumpStationState.h"
template<>
class StateTraits<DumpStationState> {
public:
    typedef DumpStationEvent AssociatedEvent;
    static DumpStationState initializeFromEvent(const DumpStationEvent& src);
    static DumpStationState generateNextState(const DumpStationState& current, const DumpStationEvent& event);
};