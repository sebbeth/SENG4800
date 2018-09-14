/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#pragma once
#include "../StateTraits.h"
#include "ShiploaderState.h"
template<>
class StateTraits<ShiploaderState> {
public:
    static ShiploaderState initializeFromEvent(const ShiploaderEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, ShiploaderStateType::Idle, src.amount, src.position, src.stockpileID, src.time, src.vesselID};
    }

    static ShiploaderState generateNextState(const ShiploaderState& current, const ShiploaderEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        ShiploaderState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = ShiploaderState::determineNextType(current.type, event.type);
        if(event.hasAmount()) {
        result.amount = event.amount;
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
        if(event.hasVesselID()) {
        result.vesselID = event.vesselID;
        }
        return result;

    }
};