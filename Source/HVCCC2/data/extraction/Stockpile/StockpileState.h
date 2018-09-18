/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#pragma once
#include <string>
#include "Stockpile.h"
#include "StockpileEvent.h"
#include "StockpileStateType.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
#include "../Vessel/Vessel.h"
class StockpileState {
public:
    using Entity = Stockpile;
    Entity::Id id;
    StockpileStateType type;
    

    double amount;
    double length;
    Stacker::Id machineID;
    std::string padID;
    double position;
    double time;
    Vessel::Id vesselID;
    
    StockpileState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static StockpileStateType determineNextType(StockpileStateType stateType, StockpileEventType eventType);
};

template<class Archive>
void StockpileState::serialize(Archive & archive) {
    archive(id, type, amount, length, machineID, padID, position, time, vesselID);
}