/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#include "Dumpstation.h"
const std::string Dumpstation::ENTITY_NAME = "Dumpstation";
const std::string Dumpstation::XML_TAG_PREFIX = "Ds";

    
bool operator<(const Dumpstation::Id& a, const Dumpstation::Id& b) {
    return a.terminal < b.terminal &&a.name < b.name;
}

bool operator==(const Dumpstation::Id& a, const Dumpstation::Id& b) {
    return a.terminal == b.terminal &&a.name == b.name;
}
std::string Dumpstation::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + name;
}