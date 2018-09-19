/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include <string>
#include "TrainMovementEventType.h"
#include "TrainMovement.h"
#include "../TrainMovement/TrainMovement.h"
class TrainMovementEvent {
public:
    using Entity = TrainMovement;
    Entity::Id id;
    TrainMovementEventType type;

    std::string direction;
    std::string sectionID;
    std::string signalID;
    std::string signalState;
    double speed;
    double time;
    std::string trackID;
    std::string trainID;

    bool hasDirection() const;
    bool hasSectionID() const;
    bool hasSignalID() const;
    bool hasSignalState() const;
    bool hasSpeed() const;
    bool hasTime() const;
    bool hasTrackID() const;
    bool hasTrainID() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void TrainMovementEvent::serialize(Archive & archive) {
    archive(id, type, direction, sectionID, signalID, signalState, speed, time, trackID, trainID);
}