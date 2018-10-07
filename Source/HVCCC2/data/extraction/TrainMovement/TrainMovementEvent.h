/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
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

    int cycleID;
    std::string direction;
    std::string sectionID;
    double speed;
    double time;
    std::string trackID;

    bool hasCycleID() const;
    bool hasDirection() const;
    bool hasSectionID() const;
    bool hasSpeed() const;
    bool hasTime() const;
    bool hasTrackID() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void TrainMovementEvent::serialize(Archive & archive) {
    archive(id, type, cycleID, direction, sectionID, speed, time, trackID);
}