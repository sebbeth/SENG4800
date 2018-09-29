/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
 **/
#pragma once
#include "../StateTraits.h"
#include "TrainMovementState.h"
template<>
class StateTraits<TrainMovementState> {
public:
    static TrainMovementState initializeFromEvent(const TrainMovementEvent& src) {
        /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
        auto tentativeState = TrainMovementState::determineNextType(TrainMovementStateType::Idle, src.type);//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though
        return {src.id, tentativeState != TrainMovementStateType::Invalid ? tentativeState : TrainMovementStateType::Idle, src.direction, src.sectionID, src.signalID, src.signalState, src.speed, src.time, src.trackID, src.trainID};
    }

    static TrainMovementState generateNextState(const TrainMovementState& current, const TrainMovementEvent& event) {

        /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
        TrainMovementState result = initializeFromEvent(event);//remove this line if/when you do
        result.id = event.id;        result.type = TrainMovementState::determineNextType(current.type, event.type);
        if(event.hasDirection()) {
        result.direction = event.direction;
        }
        if(event.hasSectionID()) {
        result.sectionID = event.sectionID;
        }
        if(event.hasSignalID()) {
        result.signalID = event.signalID;
        }
        if(event.hasSignalState()) {
        result.signalState = event.signalState;
        }
        if(event.hasSpeed()) {
        result.speed = event.speed;
        }
        if(event.hasTime()) {
        result.time = event.time;
        }
        if(event.hasTrackID()) {
        result.trackID = event.trackID;
        }
        if(event.hasTrainID()) {
        result.trainID = event.trainID;
        }
        return result;

    }
};