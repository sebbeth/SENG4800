/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#pragma once
#include "../StateTraits.h"
#include "DumpstationState.h"
template<>
class StateTraits<DumpstationState> {
public:
    static DumpstationState initializeFromEvent(const DumpstationEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, DumpstationStateType::idle, src.amount, src.cycleID, src.stockpileID, src.time};
    }

    static DumpstationState generateNextState(const DumpstationState& current, const DumpstationEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        DumpstationState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = DumpstationState::determineNextType(current.type, event.type);
        if(event.hasAmount()) {
        result.amount = event.amount;
        }
        if(event.hasCycleID()) {
        result.cycleID = event.cycleID;
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