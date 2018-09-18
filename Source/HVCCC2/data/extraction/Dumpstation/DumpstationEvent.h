/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:05:50.446537
 **/
#pragma once
#include <string>
#include "DumpstationEventType.h"
#include "Dumpstation.h"
#include "../Dumpstation/Dumpstation.h"
#include "../Stockpile/Stockpile.h"
class DumpstationEvent {
public:
    using Entity = Dumpstation;
    Entity::Id id;
    DumpstationEventType type;

    double amount;
    int cycleID;
    Stockpile::Id stockpileID;
    double time;

    bool hasAmount() const;
    bool hasCycleID() const;
    bool hasStockpileID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void DumpstationEvent::serialize(Archive & archive) {
    archive(id, type, amount, cycleID, stockpileID, time);
}