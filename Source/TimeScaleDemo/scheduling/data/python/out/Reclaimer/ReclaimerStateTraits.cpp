#include "ReclaimerStateTraits.h"
    
ReclaimerState StateTraits<ReclaimerState>::initializeFromEvent(const ReclaimerEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {ReclaimerStateType::Idle, src.amount, src.machineID, src.position, src.stockpileID, src.time};
}

ReclaimerState StateTraits<ReclaimerState>::generateNextState(const ReclaimerState& current, const ReclaimerEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    ReclaimerState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = ReclaimerState::determineNextType(current.type, event.type);
    if(event.hasAmount()) {
        result.amount = event.amount;
    }
    if(event.hasMachineID()) {
        result.machineID = event.machineID;
    }
    if(event.hasPosition()) {
        result.position = event.position;
    }
    if(event.hasStockpileID()) {
        result.stockpileID = event.stockpileID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    return result;
}