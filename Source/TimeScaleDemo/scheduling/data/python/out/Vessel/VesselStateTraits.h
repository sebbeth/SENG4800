#pragma once
#include "../StateTraits.h"
#include "VesselState.h"
template<>
class StateTraits<VesselState> {
public:
    typedef VesselEvent AssociatedEvent;
    static VesselState initializeFromEvent(const VesselEvent& src);
    static VesselState generateNextState(const VesselState& current, const VesselEvent& event);
};