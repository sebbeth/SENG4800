/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
 **/
#pragma once
#include <string>
#include "TrainMovement.h"
#include "TrainMovementEvent.h"
#include "TrainMovementStateType.h"
#include "../TrainMovement/TrainMovement.h"
class TrainMovementState {
public:
    using Entity = TrainMovement;
    Entity::Id id;
    TrainMovementStateType type;
    

    std::string direction;
    std::string sectionID;
    std::string signalID;
    std::string signalState;
    double speed;
    double time;
    std::string trackID;
    std::string trainID;
    
    TrainMovementState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static TrainMovementStateType determineNextType(TrainMovementStateType stateType, TrainMovementEventType eventType);
};

template<class Archive>
void TrainMovementState::serialize(Archive & archive) {
    archive(id, type, direction, sectionID, signalID, signalState, speed, time, trackID, trainID);
}