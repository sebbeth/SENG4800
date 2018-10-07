/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include "../StateTraits.h"
#include "StackerState.h"
template<>
class StateTraits<StackerState> {
public:
    static StackerState initializeFromEvent(const StackerEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = StackerState::determineNextType(StackerStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != StackerStateType::Invalid ? tentativeState : StackerStateType::Idle, src.amount, src.position, src.stockpileID, src.time};
    }

    static StackerState generateNextState(const StackerState& current, const StackerEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        StackerState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = StackerState::determineNextType(current.type, event.type);
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