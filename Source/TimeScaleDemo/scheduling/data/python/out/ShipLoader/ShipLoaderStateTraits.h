#pragma once
#include "../StateTraits.h"
#include "ShipLoaderState.h"
template<>
class StateTraits<ShipLoaderState> {
public:
    typedef ShipLoaderEvent AssociatedEvent;
    static ShipLoaderState initializeFromEvent(const ShipLoaderEvent& src);
    static ShipLoaderState generateNextState(const ShipLoaderState& current, const ShipLoaderEvent& event);
};