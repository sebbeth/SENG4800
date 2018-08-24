#include "LoadPointStateTraits.h"
    
LoadPointState StateTraits<LoadPointState>::initializeFromEvent(const LoadPointEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {LoadPointStateType::Idle, src.amount, src.cycleID, src.loadPointID, src.loadPointName, src.time};
}

LoadPointState StateTraits<LoadPointState>::generateNextState(const LoadPointState& current, const LoadPointEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    LoadPointState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = LoadPointState::determineNextType(current.type, event.type);
    if(event.hasAmount()) {
        result.amount = event.amount;
    }
    if(event.hasCycleID()) {
        result.cycleID = event.cycleID;
    }
    if(event.hasLoadPointID()) {
        result.loadPointID = event.loadPointID;
    }
    if(event.hasLoadPointName()) {
        result.loadPointName = event.loadPointName;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    return result;
}