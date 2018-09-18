/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#pragma once
#include <string>
#include "Reclaimer.h"
#include "ReclaimerEvent.h"
#include "ReclaimerStateType.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
class ReclaimerState {
public:
    using Entity = Reclaimer;
    Entity::Id id;
    ReclaimerStateType type;
    

    double amount;
    double position;
    Stockpile::Id stockpileID;
    double time;
    
    ReclaimerState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static ReclaimerStateType determineNextType(ReclaimerStateType stateType, ReclaimerEventType eventType);
};

template<class Archive>
void ReclaimerState::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time);
}