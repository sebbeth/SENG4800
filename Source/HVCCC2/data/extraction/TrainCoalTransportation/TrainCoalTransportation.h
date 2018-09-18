/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#pragma once
#include <string>
#include "../TerminalId.h"
#include "../../util.h"
class TrainCoalTransportationEvent;
class TrainCoalTransportationState;
class TrainCoalTransportation {
public:
    using AssociatedEvent = TrainCoalTransportationEvent;
        using AssociatedState = TrainCoalTransportationState;
    static const std::string ENTITY_NAME;
    static const std::string XML_TAG_PREFIX;
    class Id {
    public:
        using Entity = TrainCoalTransportation;
        std::string name;
        Id();
        Id(const std::string& name);        std::string nameForBinaryFile() const;
        template<class Archive>
        void serialize(Archive & archive);
    };
};

bool operator<(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b);
bool operator==(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b);
bool operator!=(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b);

template<class Archive>
void TrainCoalTransportation::Id::serialize(Archive & archive) {
    archive(name);
}