/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "Shiploader.h"
const std::string Shiploader::ENTITY_NAME = "Shiploader";
const std::string Shiploader::XML_TAG_PREFIX = "Sl";


bool operator<(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}
std::string Shiploader::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}