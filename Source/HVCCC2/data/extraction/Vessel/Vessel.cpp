/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "Vessel.h"

Vessel::Id::Id(): 
 name("") {
}
Vessel::Id::Id(const std::string& name): name(name) {
}
const std::string Vessel::ENTITY_NAME = "Vessel";
const std::string Vessel::XML_TAG_PREFIX = "Vessel";


bool operator<(const Vessel::Id& a, const Vessel::Id& b) {
    return a.name < b.name;
}

bool operator==(const Vessel::Id& a, const Vessel::Id& b) {
    return a.name == b.name;
}

bool operator!=(const Vessel::Id& a, const Vessel::Id& b) {
     return !(a == b);
}

std::string Vessel::Id::nameForBinaryFile() const {
    return name;
}