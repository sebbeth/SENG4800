#include "SignalStateTraits.h"
    
SignalState StateTraits<SignalState>::initializeFromEvent(const SignalEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {src.signalState, src.signalID, src.signalState, src.time};
}

SignalState StateTraits<SignalState>::generateNextState(const SignalState& current, const SignalEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    SignalState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = SignalState::determineNextType(current.type, event.type);
    if(event.hasSignalID()) {
        result.signalID = event.signalID;
    }
    if(event.hasSignalState()) {
        result.signalState = event.signalState;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    return result;
}