/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
 **/
#pragma once
#include <string>
#include "Loadpoints.h"
#include "LoadpointsEvent.h"
#include "LoadpointsStateType.h"
#include "../Loadpoints/Loadpoints.h"
class LoadpointsState {
public:
    using Entity = Loadpoints;
    Entity::Id id;
    LoadpointsStateType type;
    

    double amount;
    int cycleID;
    std::string loadpointName;
    double time;
    
    LoadpointsState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static LoadpointsStateType determineNextType(LoadpointsStateType stateType, LoadpointsEventType eventType);
};

template<class Archive>
void LoadpointsState::serialize(Archive & archive) {
    archive(id, type, amount, cycleID, loadpointName, time);
}