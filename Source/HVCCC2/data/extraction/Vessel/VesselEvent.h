/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
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

    bool isTidal;
    double metermark;
    std::string terminalID;
    double time;
    int tugs;

    bool hasIsTidal() const;
    bool hasMetermark() const;
    bool hasTerminalID() const;
    bool hasTime() const;
    bool hasTugs() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void VesselEvent::serialize(Archive & archive) {
    archive(id, type, isTidal, metermark, terminalID, time, tugs);
}