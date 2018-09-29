/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#pragma once
#include "../StateTraits.h"
#include "StockpileState.h"
template<>
class StateTraits<StockpileState> {
public:
    static StockpileState initializeFromEvent(const StockpileEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, StockpileStateType::Idle, src.amount, src.length, src.machineID, src.padID, src.position, src.time, src.vesselID};
    }

    static StockpileState generateNextState(const StockpileState& current, const StockpileEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        StockpileState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = StockpileState::determineNextType(current.type, event.type);
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
        if(event.hasPosition()) {
        result.position = event.position;
        }
        if(event.hasTime()) {
        result.time = event.time;
        }
        if(event.hasVesselID()) {
        result.vesselID = event.vesselID;
        }
        return result;

    }
};