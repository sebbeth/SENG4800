/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
 **/
#pragma once
#include "../StateTraits.h"
#include "DumpstationState.h"
template<>
class StateTraits<DumpstationState> {
public:
    static DumpstationState initializeFromEvent(const DumpstationEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = DumpstationState::determineNextType(DumpstationStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != DumpstationStateType::Invalid ? tentativeState : DumpstationStateType::Idle, src.amount, src.cycleID, src.stockpileID, src.time};
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