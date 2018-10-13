/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#pragma once
#include "../StateTraits.h"
#include "VesselState.h"
template<>
class StateTraits<VesselState> {
public:
    static VesselState initializeFromEvent(const VesselEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = VesselState::determineNextType(VesselStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != VesselStateType::Invalid ? tentativeState : VesselStateType::Idle, src.isTidal, src.metermark, src.terminalID, src.time, src.tugs};
    }

    static VesselState generateNextState(const VesselState& current, const VesselEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        VesselState result = current;
        result.type = VesselState::determineNextType(current.type, event.type);

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