/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "Shiploader.h"

Shiploader::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
Shiploader::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
const std::string Shiploader::ENTITY_NAME = "Shiploader";
const std::string Shiploader::XML_TAG_PREFIX = "Sl";


bool operator<(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Shiploader::Id& a, const Shiploader::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const Shiploader::Id& a, const Shiploader::Id& b) {
     return !(a == b);
}

std::string Shiploader::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}