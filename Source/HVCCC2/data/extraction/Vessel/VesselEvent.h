/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#pragma once
#include <string>
#include "VesselEventType.h"
#include "Vessel.h"
#include "../Vessel/Vessel.h"
class VesselEvent {
public:
    using Entity = Vessel;
    Entity::Id id;
    VesselEventType type;

    int ballast;
    int cargo;
    std::string terminalID;
    double time;

    bool hasBallast() const;
    bool hasCargo() const;
    bool hasTerminalID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void VesselEvent::serialize(Archive & archive) {
    archive(id, type, ballast, cargo, terminalID, time);
}