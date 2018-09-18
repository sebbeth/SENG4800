/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#pragma once
#include <string>
#include "TrainCoalTransportationEventType.h"
#include "TrainCoalTransportation.h"

class TrainCoalTransportationEvent {
public:
    using Entity = TrainCoalTransportation;
    Entity::Id id;
    TrainCoalTransportationEventType type;



    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void TrainCoalTransportationEvent::serialize(Archive & archive) {
    archive(id, type, );
}