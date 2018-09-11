/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#include "Signal.h"
const std::string Signal::ENTITY_NAME = "Signal";
const std::string Signal::XML_TAG_PREFIX = "Signal";

    
bool operator<(const Signal::Id& a, const Signal::Id& b) {
    return a.name < b.name;
}

bool operator==(const Signal::Id& a, const Signal::Id& b) {
    return a.name == b.name;
}
std::string Signal::Id::nameForBinaryFile() const {
    return name;
}