/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#include "Shiploader.h"
const std::string Shiploader::ENTITY_NAME = "Shiploader";
const std::string Shiploader::XML_TAG_PREFIX = "Sl";

    
bool operator<(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal < b.terminal &&a.name < b.name;
}

bool operator==(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal == b.terminal &&a.name == b.name;
}
std::string Shiploader::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + name;
}