/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include "../StateTraits.h"
#include "SignalState.h"
template<>
class StateTraits<SignalState> {
public:
    static SignalState initializeFromEvent(const SignalEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        return {src.id, src.signalState, src.time};
    }

    static SignalState generateNextState(const SignalState& current, const SignalEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        SignalState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;
        if(event.hasTime()) {
        result.time = event.time;
        }
        return result;

    }
};