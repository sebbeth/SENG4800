/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
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
        return {src.id, tentativeState != DumpstationStateType::Invalid ? tentativeState : DumpstationStateType::Idle, src.amount, src.time, src.trainID};
    }

    static DumpstationState generateNextState(const DumpstationState& current, const DumpstationEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        DumpstationState result = current;
        result.type = DumpstationState::determineNextType(current.type, event.type);

        if(event.hasAmount()) {
        result.amount = event.amount;
        }
		if (event.hasTrainID()) {
			result.trainID = event.trainID;
		}
        if(event.hasTime()) {
        result.time = event.time;
        }
        return result;

    }
};