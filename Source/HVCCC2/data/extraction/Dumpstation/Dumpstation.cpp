/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "Dumpstation.h"

Dumpstation::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
Dumpstation::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
const std::string Dumpstation::ENTITY_NAME = "Dumpstation";
const std::string Dumpstation::XML_TAG_PREFIX = "Ds";


bool operator<(const Dumpstation::Id& a, const Dumpstation::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Dumpstation::Id& a, const Dumpstation::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const Dumpstation::Id& a, const Dumpstation::Id& b) {
     return !(a == b);
}

std::string Dumpstation::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}