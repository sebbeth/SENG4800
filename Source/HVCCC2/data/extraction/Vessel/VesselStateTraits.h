/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include "../StateTraits.h"
#include "VesselState.h"
template<>
class StateTraits<VesselState> {
public:
    static VesselState initializeFromEvent(const VesselEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, VesselStateType::Idle, src.isTidal, src.metermark, src.terminalID, src.time, src.tugs};
    }

    static VesselState generateNextState(const VesselState& current, const VesselEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        VesselState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = VesselState::determineNextType(current.type, event.type);
        if(event.hasIsTidal()) {
        result.isTidal = event.isTidal;
        }
        if(event.hasMetermark()) {
        result.metermark = event.metermark;
        }
        if(event.hasTerminalID()) {
        result.terminalID = event.terminalID;
        }
        if(event.hasTime()) {
        result.time = event.time;
        }
        if(event.hasTugs()) {
        result.tugs = event.tugs;
        }
        return result;

    }
};