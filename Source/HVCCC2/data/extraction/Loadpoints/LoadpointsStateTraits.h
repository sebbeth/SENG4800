/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include "../StateTraits.h"
#include "LoadpointsState.h"
template<>
class StateTraits<LoadpointsState> {
public:
    static LoadpointsState initializeFromEvent(const LoadpointsEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, LoadpointsStateType::Idle, src.amount, src.cycleID, src.loadpointName, src.time};
    }

    static LoadpointsState generateNextState(const LoadpointsState& current, const LoadpointsEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        LoadpointsState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = LoadpointsState::determineNextType(current.type, event.type);
        if(event.hasAmount()) {
        result.amount = event.amount;
        }
        if(event.hasCycleID()) {
        result.cycleID = event.cycleID;
        }
        if(event.hasLoadpointName()) {
        result.loadpointName = event.loadpointName;
        }
        if(event.hasTime()) {
        result.time = event.time;
        }
        return result;

    }
};