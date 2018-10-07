/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include "../StateTraits.h"
#include "LoadpointsState.h"
template<>
class StateTraits<LoadpointsState> {
public:
    static LoadpointsState initializeFromEvent(const LoadpointsEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = LoadpointsState::determineNextType(LoadpointsStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != LoadpointsStateType::Invalid ? tentativeState : LoadpointsStateType::Idle, src.amount, src.cycleID, src.loadpointName, src.time};
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