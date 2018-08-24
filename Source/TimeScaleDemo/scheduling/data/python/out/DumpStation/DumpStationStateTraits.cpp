#include "DumpStationStateTraits.h"
    
DumpStationState StateTraits<DumpStationState>::initializeFromEvent(const DumpStationEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {DumpStationStateType::Idle, src.amountDumped, src.cycleID, src.dumpStationID, src.stockpileID, src.time};
}

DumpStationState StateTraits<DumpStationState>::generateNextState(const DumpStationState& current, const DumpStationEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    DumpStationState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = DumpStationState::determineNextType(current.type, event.type);
    if(event.hasAmountDumped()) {
        result.amountDumped = event.amountDumped;
    }
    if(event.hasCycleID()) {
        result.cycleID = event.cycleID;
    }
    if(event.hasDumpStationID()) {
        result.dumpStationID = event.dumpStationID;
    }
    if(event.hasStockpileID()) {
        result.stockpileID = event.stockpileID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    return result;
}