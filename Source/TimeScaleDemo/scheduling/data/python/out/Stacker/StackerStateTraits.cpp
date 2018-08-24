#include "StackerStateTraits.h"
    
StackerState StateTraits<StackerState>::initializeFromEvent(const StackerEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {StackerStateType::Idle, src.amount, src.machineID, src.position, src.stockpileID, src.time};
}

StackerState StateTraits<StackerState>::generateNextState(const StackerState& current, const StackerEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    StackerState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = StackerState::determineNextType(current.type, event.type);
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