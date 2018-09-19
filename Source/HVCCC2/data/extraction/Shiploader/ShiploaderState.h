/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include <string>
#include "Shiploader.h"
#include "ShiploaderEvent.h"
#include "ShiploaderStateType.h"
#include "../Shiploader/Shiploader.h"
#include "../Stockpile/Stockpile.h"
#include "../Vessel/Vessel.h"
class ShiploaderState {
public:
    using Entity = Shiploader;
    Entity::Id id;
    ShiploaderStateType type;
    

    double amount;
    double position;
    Stockpile::Id stockpileID;
    double time;
    Vessel::Id vesselID;
    
    ShiploaderState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static ShiploaderStateType determineNextType(ShiploaderStateType stateType, ShiploaderEventType eventType);
};

template<class Archive>
void ShiploaderState::serialize(Archive & archive) {
    archive(id, type, amount, position, stockpileID, time, vesselID);
}