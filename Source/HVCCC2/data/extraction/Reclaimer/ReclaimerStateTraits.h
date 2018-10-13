/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#pragma once
#include "../StateTraits.h"
#include "ReclaimerState.h"
template<>
class StateTraits<ReclaimerState> {
public:
    static ReclaimerState initializeFromEvent(const ReclaimerEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = ReclaimerState::determineNextType(ReclaimerStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != ReclaimerStateType::Invalid ? tentativeState : ReclaimerStateType::Idle, src.amount, src.position, src.stockpileID, src.time};
    }

    static ReclaimerState generateNextState(const ReclaimerState& current, const ReclaimerEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        ReclaimerState result = current;
        result.type = ReclaimerState::determineNextType(current.type, event.type);

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
        return result;

    }
};