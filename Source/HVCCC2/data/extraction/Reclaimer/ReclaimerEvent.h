/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#pragma once
#include <string>
#include "ReclaimerEventType.h"
#include "Reclaimer.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
class ReclaimerEvent {
public:
    using Entity = Reclaimer;
    Entity::Id id;
    ReclaimerEventType type;

    double amount;
    double position;
    Stockpile::Id stockpileID;
    double time;

    bool hasAmount() const;
    bool hasPosition() const;
    bool hasStockpileID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void ReclaimerEvent::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time);
}