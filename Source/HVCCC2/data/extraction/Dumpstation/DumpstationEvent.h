/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>
#include "DumpstationEventType.h"
#include "Dumpstation.h"
#include "../Dumpstation/Dumpstation.h"
#include "../TrainMovement/TrainMovement.h"
class DumpstationEvent {
public:
    using Entity = Dumpstation;
    Entity::Id id;
    DumpstationEventType type;

    double amount;
    double time;
    TrainMovement::Id trainID;

    bool hasAmount() const;
    bool hasTime() const;
    bool hasTrainID() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void DumpstationEvent::serialize(Archive & archive) {
    archive(id, type, amount, time, trainID);
}