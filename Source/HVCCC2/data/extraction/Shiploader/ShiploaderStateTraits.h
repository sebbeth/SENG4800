/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#pragma once
#include "../StateTraits.h"
#include "ShiploaderState.h"
template<>
class StateTraits<ShiploaderState> {
public:
    static ShiploaderState initializeFromEvent(const ShiploaderEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = ShiploaderState::determineNextType(ShiploaderStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != ShiploaderStateType::Invalid ? tentativeState : ShiploaderStateType::Idle, src.amount, src.position, src.stockpileID, src.time, src.vesselID};
    }

    static ShiploaderState generateNextState(const ShiploaderState& current, const ShiploaderEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        ShiploaderState result = current;
        result.type = ShiploaderState::determineNextType(current.type, event.type);

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