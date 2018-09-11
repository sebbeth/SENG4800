/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include "../StateTraits.h"
#include "ReclaimerState.h"
template<>
class StateTraits<ReclaimerState> {
public:
    static ReclaimerState initializeFromEvent(const ReclaimerEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, ReclaimerStateType::Idle, src.amount, src.position, src.stockpileID, src.time};
    }

    static ReclaimerState generateNextState(const ReclaimerState& current, const ReclaimerEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        ReclaimerState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = ReclaimerState::determineNextType(current.type, event.type);
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