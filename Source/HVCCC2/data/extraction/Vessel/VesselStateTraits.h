/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include "../StateTraits.h"
#include "VesselState.h"
template<>
class StateTraits<VesselState> {
public:
    static VesselState initializeFromEvent(const VesselEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, VesselStateType::Idle, src.ballast, src.cargo, src.numcargoes, src.terminalID, src.time};
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