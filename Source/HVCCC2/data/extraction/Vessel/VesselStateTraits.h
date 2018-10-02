/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
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
        return {src.id, tentativeState != VesselStateType::Invalid ? tentativeState : VesselStateType::Idle, src.ballast, src.cargo, src.numcargoes, src.terminalID, src.time};
    }

    static VesselState generateNextState(const VesselState& current, const VesselEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        VesselState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = VesselState::determineNextType(current.type, event.type);
        if(event.hasBallast()) {
        result.ballast = event.ballast;
        }
        if(event.hasCargo()) {
        result.cargo = event.cargo;
        }
        if(event.hasNumcargoes()) {
        result.numcargoes = event.numcargoes;
        }
        if(event.hasTerminalID()) {
        result.terminalID = event.terminalID;
        }
        if(event.hasTime()) {
        result.time = event.time;
        }
        return result;

    }
};