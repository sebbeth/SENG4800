/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "Stockpile.h"
const std::string Stockpile::ENTITY_NAME = "Stockpile";
const std::string Stockpile::XML_TAG_PREFIX = "Sp";


bool operator<(const Stockpile::Id& a, const Stockpile::Id& b) {
    return a.terminal < b.terminal &&a.name < b.name;
}

bool operator==(const Stockpile::Id& a, const Stockpile::Id& b) {
    return a.terminal == b.terminal &&a.name == b.name;
}
std::string Stockpile::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}