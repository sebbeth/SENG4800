/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>
#include "StackerEventType.h"
#include "Stacker.h"
#include "../Stacker/Stacker.h"
#include "../Stockpile/Stockpile.h"
class StackerEvent {
public:
    using Entity = Stacker;
    Entity::Id id;
    StackerEventType type;

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
void StackerEvent::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time);
}