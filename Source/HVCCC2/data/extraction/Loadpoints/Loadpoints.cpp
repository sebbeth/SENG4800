/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "Loadpoints.h"

Loadpoints::Id::Id(): 
 name("") {
}
Loadpoints::Id::Id(const std::string& name): name(name) {
}
const std::string Loadpoints::ENTITY_NAME = "Loadpoints";
const std::string Loadpoints::XML_TAG_PREFIX = "Lp";


bool operator<(const Loadpoints::Id& a, const Loadpoints::Id& b) {
    return a.name < b.name;
}

bool operator==(const Loadpoints::Id& a, const Loadpoints::Id& b) {
    return a.name == b.name;
}

bool operator!=(const Loadpoints::Id& a, const Loadpoints::Id& b) {
     return !(a == b);
}

std::string Loadpoints::Id::nameForBinaryFile() const {
    return name;
}