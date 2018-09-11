/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "Vessel.h"
const std::string Vessel::ENTITY_NAME = "Vessel";
const std::string Vessel::XML_TAG_PREFIX = "Vessel";


bool operator<(const Vessel::Id& a, const Vessel::Id& b) {
    return a.name < b.name;
}

bool operator==(const Vessel::Id& a, const Vessel::Id& b) {
    return a.name == b.name;
}
std::string Vessel::Id::nameForBinaryFile() const {
    return name;
}