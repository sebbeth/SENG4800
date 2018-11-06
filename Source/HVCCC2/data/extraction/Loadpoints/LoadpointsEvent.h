/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>
#include "LoadpointsEventType.h"
#include "Loadpoints.h"
#include "../Loadpoints/Loadpoints.h"
class LoadpointsEvent {
public:
    using Entity = Loadpoints;
    Entity::Id id;
    LoadpointsEventType type;

    double amount;
    std::string loadpointName;
    double time;

    bool hasAmount() const;
    bool hasLoadpointName() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void LoadpointsEvent::serialize(Archive & archive) {
    archive(id, type, amount, loadpointName, time);
}