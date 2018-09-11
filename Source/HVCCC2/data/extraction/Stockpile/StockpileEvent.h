/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>
#include "StockpileEventType.h"
#include "Stockpile.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
#include "../Vessel/Vessel.h"
class StockpileEvent {
public:
    using Entity = Stockpile;
    Entity::Id id;
    StockpileEventType type;

    double amount;
    double length;
    Stacker::Id machineID;
    std::string padID;
    double position;
    double time;
    Vessel::Id vesselID;

    bool hasAmount() const;
    bool hasLength() const;
    bool hasMachineID() const;
    bool hasPadID() const;
    bool hasPosition() const;
    bool hasTime() const;
    bool hasVesselID() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void StockpileEvent::serialize(Archive & archive) {
    archive(id, type, amount, length, machineID, padID, position, time, vesselID);
}