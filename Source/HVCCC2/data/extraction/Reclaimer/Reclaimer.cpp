/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "Reclaimer.h"
const std::string Reclaimer::ENTITY_NAME = "Reclaimer";
const std::string Reclaimer::XML_TAG_PREFIX = "Rec";


bool operator<(const Reclaimer::Id& a, const Reclaimer::Id& b) {
    return a.terminal < b.terminal &&a.name < b.name;
}

bool operator==(const Reclaimer::Id& a, const Reclaimer::Id& b) {
    return a.terminal == b.terminal &&a.name == b.name;
}
std::string Reclaimer::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}