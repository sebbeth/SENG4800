/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
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
    

    int ballast;
    int cargo;
    int numcargoes;
    std::string terminalID;
    double time;
    
    VesselState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static VesselStateType determineNextType(VesselStateType stateType, VesselEventType eventType);
};

template<class Archive>
void VesselState::serialize(Archive & archive) {
    archive(id, type, ballast, cargo, numcargoes, terminalID, time);
}