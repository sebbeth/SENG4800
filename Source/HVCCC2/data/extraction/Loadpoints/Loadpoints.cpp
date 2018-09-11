/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "Loadpoints.h"
const std::string Loadpoints::ENTITY_NAME = "Loadpoints";
const std::string Loadpoints::XML_TAG_PREFIX = "Lp";


bool operator<(const Loadpoints::Id& a, const Loadpoints::Id& b) {
    return a.name < b.name;
}

bool operator==(const Loadpoints::Id& a, const Loadpoints::Id& b) {
    return a.name == b.name;
}
std::string Loadpoints::Id::nameForBinaryFile() const {
    return name;
}