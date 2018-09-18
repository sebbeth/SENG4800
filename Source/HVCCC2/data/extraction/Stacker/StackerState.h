/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:05:50.446537
 **/
#pragma once
#include <string>
#include "Stacker.h"
#include "StackerEvent.h"
#include "StackerStateType.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
class StackerState {
public:
    using Entity = Stacker;
    Entity::Id id;
    StackerStateType type;
    

    double amount;
    double position;
    Stockpile::Id stockpileID;
    double time;
    
    StackerState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static StackerStateType determineNextType(StackerStateType stateType, StackerEventType eventType);
};

template<class Archive>
void StackerState::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time);
}