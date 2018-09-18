/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#include "TrainCoalTransportation.h"

TrainCoalTransportation::Id::Id(): 
 name("") {
}
TrainCoalTransportation::Id::Id(const std::string& name): name(name) {
}
const std::string TrainCoalTransportation::ENTITY_NAME = "TrainCoalTransportation";
const std::string TrainCoalTransportation::XML_TAG_PREFIX = "Tct";


bool operator<(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b) {
    return a.name < b.name;
}

bool operator==(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b) {
    return a.name == b.name;
}

bool operator!=(const TrainCoalTransportation::Id& a, const TrainCoalTransportation::Id& b) {
     return !(a == b);
}

std::string TrainCoalTransportation::Id::nameForBinaryFile() const {
    return name;
}