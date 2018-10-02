/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
 **/
#pragma once
#include <string>
#include "Dumpstation.h"
#include "DumpstationEvent.h"
#include "DumpstationStateType.h"
#include "../Dumpstation/Dumpstation.h"
#include "../Stockpile/Stockpile.h"
#include "../TrainMovement/TrainMovement.h"
class DumpstationState {
public:
    using Entity = Dumpstation;
    Entity::Id id;
    DumpstationStateType type;
    

    double amount;
    TrainMovement::Id cycleID;
    Stockpile::Id stockpileID;
    double time;
    
    DumpstationState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static DumpstationStateType determineNextType(DumpstationStateType stateType, DumpstationEventType eventType);
};

template<class Archive>
void DumpstationState::serialize(Archive & archive) {
    archive(id, type, amount, cycleID, stockpileID, time);
}