/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>
#include "Dumpstation.h"
#include "DumpstationEvent.h"
#include "DumpstationStateType.h"
#include "../Dumpstation/Dumpstation.h"
#include "../TrainMovement/TrainMovement.h"
class DumpstationState {
public:
    using Entity = Dumpstation;
    Entity::Id id;
    DumpstationStateType type;
    

    double amount;
    double time;
    TrainMovement::Id trainID;
    
    DumpstationState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static DumpstationStateType determineNextType(DumpstationStateType stateType, DumpstationEventType eventType);
};

template<class Archive>
void DumpstationState::serialize(Archive & archive) {
    archive(id, type, amount, time, trainID);
}