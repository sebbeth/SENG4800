/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
 **/
#pragma once
#include <string>
#include "ShiploaderEventType.h"
#include "Shiploader.h"
#include "../Shiploader/Shiploader.h"
#include "../Stockpile/Stockpile.h"
#include "../Vessel/Vessel.h"
class ShiploaderEvent {
public:
    using Entity = Shiploader;
    Entity::Id id;
    ShiploaderEventType type;

    double amount;
    double position;
    Stockpile::Id stockpileID;
    double time;
    Vessel::Id vesselID;

    bool hasAmount() const;
    bool hasPosition() const;
    bool hasStockpileID() const;
    bool hasTime() const;
    bool hasVesselID() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void ShiploaderEvent::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time, vesselID);
}