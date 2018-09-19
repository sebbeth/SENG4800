/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include "../StateTraits.h"
#include "StackerState.h"
template<>
class StateTraits<StackerState> {
public:
    static StackerState initializeFromEvent(const StackerEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, StackerStateType::Idle, src.amount, src.position, src.stockpileID, src.time};
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