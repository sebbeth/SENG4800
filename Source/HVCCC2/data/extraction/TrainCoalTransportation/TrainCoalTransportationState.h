/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#pragma once
#include <string>
#include "TrainCoalTransportation.h"
#include "TrainCoalTransportationEvent.h"
#include "TrainCoalTransportationStateType.h"

class TrainCoalTransportationState {
public:
    using Entity = TrainCoalTransportation;
    Entity::Id id;
    TrainCoalTransportationStateType type;
    

    
    TrainCoalTransportationState() = default;

    template<class Archive>
    void serialize(Archive & archive);
    static TrainCoalTransportationStateType determineNextType(TrainCoalTransportationStateType stateType, TrainCoalTransportationEventType eventType);
};

template<class Archive>
void TrainCoalTransportationState::serialize(Archive & archive) {
    archive(id, type, );
}