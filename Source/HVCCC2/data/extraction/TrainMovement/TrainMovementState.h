/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
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
    

    int cycleID;
    std::string direction;
    std::string sectionID;
    double speed;
    double time;
    std::string trackID;
    
    TrainMovementState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static TrainMovementStateType determineNextType(TrainMovementStateType stateType, TrainMovementEventType eventType);
};

template<class Archive>
void TrainMovementState::serialize(Archive & archive) {
    archive(id, type, cycleID, direction, sectionID, speed, time, trackID);
}