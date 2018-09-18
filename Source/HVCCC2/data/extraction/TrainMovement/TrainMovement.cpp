/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#include "TrainMovement.h"

TrainMovement::Id::Id(): 
 name("") {
}
TrainMovement::Id::Id(const std::string& name): name(name) {
}
const std::string TrainMovement::ENTITY_NAME = "TrainMovement";
const std::string TrainMovement::XML_TAG_PREFIX = "Train";


bool operator<(const TrainMovement::Id& a, const TrainMovement::Id& b) {
    return a.name < b.name;
}

bool operator==(const TrainMovement::Id& a, const TrainMovement::Id& b) {
    return a.name == b.name;
}

bool operator!=(const TrainMovement::Id& a, const TrainMovement::Id& b) {
     return !(a == b);
}

std::string TrainMovement::Id::nameForBinaryFile() const {
    return name;
}