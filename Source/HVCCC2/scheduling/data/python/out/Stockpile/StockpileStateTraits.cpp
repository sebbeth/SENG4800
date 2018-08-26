#include "StockpileStateTraits.h"
    
StockpileState StateTraits<StockpileState>::initializeFromEvent(const StockpileEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {StockpileStateType::Idle, src.amount, src.length, src.machineID, src.padID, src.startPosition, src.stockpileID, src.time, src.vesselID};
}

StockpileState StateTraits<StockpileState>::generateNextState(const StockpileState& current, const StockpileEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    StockpileState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = StockpileState::determineNextType(current.type, event.type);
    if(event.hasAmount()) {
        result.amount = event.amount;
    }
    if(event.hasLength()) {
        result.length = event.length;
    }
    if(event.hasMachineID()) {
        result.machineID = event.machineID;
    }
    if(event.hasPadID()) {
        result.padID = event.padID;
    }
    if(event.hasStartPosition()) {
        result.startPosition = event.startPosition;
    }
    if(event.hasStockpileID()) {
        result.stockpileID = event.stockpileID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    if(event.hasVesselID()) {
        result.vesselID = event.vesselID;
    }
    return result;
}