/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "Stockpile.h"

Stockpile::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
Stockpile::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
const std::string Stockpile::ENTITY_NAME = "Stockpile";
const std::string Stockpile::XML_TAG_PREFIX = "Sp";


bool operator<(const Stockpile::Id& a, const Stockpile::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Stockpile::Id& a, const Stockpile::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const Stockpile::Id& a, const Stockpile::Id& b) {
     return !(a == b);
}

std::string Stockpile::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}