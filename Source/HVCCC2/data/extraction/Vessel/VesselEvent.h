/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
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
    int numcargoes;
    std::string terminalID;
    double time;

    bool hasBallast() const;
    bool hasCargo() const;
    bool hasNumcargoes() const;
    bool hasTerminalID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void VesselEvent::serialize(Archive & archive) {
    archive(id, type, ballast, cargo, numcargoes, terminalID, time);
}