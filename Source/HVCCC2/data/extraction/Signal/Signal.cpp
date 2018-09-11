/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "Signal.h"

Signal::Id::Id(): 
 name("") {
}
Signal::Id::Id(const std::string& name): name(name) {
}
const std::string Signal::ENTITY_NAME = "Signal";
const std::string Signal::XML_TAG_PREFIX = "Signal";


bool operator<(const Signal::Id& a, const Signal::Id& b) {
    return a.name < b.name;
}

bool operator==(const Signal::Id& a, const Signal::Id& b) {
    return a.name == b.name;
}

bool operator!=(const Signal::Id& a, const Signal::Id& b) {
     return !(a == b);
}

std::string Signal::Id::nameForBinaryFile() const {
    return name;
}