#include "VesselStateTraits.h"
    
VesselState StateTraits<VesselState>::initializeFromEvent(const VesselEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {VesselStateType::NA, src.isTidal, src.meterMark, src.numberOfTugs, src.terminalID, src.time, src.vesselID};
}

VesselState StateTraits<VesselState>::generateNextState(const VesselState& current, const VesselEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    VesselState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = VesselState::determineNextType(current.type, event.type);
    if(event.hasIsTidal()) {
        result.isTidal = event.isTidal;
    }
    if(event.hasMeterMark()) {
        result.meterMark = event.meterMark;
    }
    if(event.hasNumberOfTugs()) {
        result.numberOfTugs = event.numberOfTugs;
    }
    if(event.hasTerminalID()) {
        result.terminalID = event.terminalID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    if(event.hasVesselID()) {
        result.vesselID = event.vesselID;
    }
    return result;
}