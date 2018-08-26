#pragma once
#include "../StateTraits.h"
#include "StockpileState.h"
template<>
class StateTraits<StockpileState> {
public:
    typedef StockpileEvent AssociatedEvent;
    static StockpileState initializeFromEvent(const StockpileEvent& src);
    static StockpileState generateNextState(const StockpileState& current, const StockpileEvent& event);
};