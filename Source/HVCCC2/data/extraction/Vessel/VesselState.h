/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>
#include "Vessel.h"
#include "VesselEvent.h"
#include "VesselStateType.h"
#include "../Vessel/Vessel.h"
class VesselState {
public:
    using Entity = Vessel;
    Entity::Id id;
    VesselStateType type;
    

    bool isTidal;
    double metermark;
    std::string terminalID;
    double time;
    int tugs;
    
    VesselState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static VesselStateType determineNextType(VesselStateType stateType, VesselEventType eventType);
};

template<class Archive>
void VesselState::serialize(Archive & archive) {
    archive(id, type, isTidal, metermark, terminalID, time, tugs);
}