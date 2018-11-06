/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "Reclaimer.h"

Reclaimer::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
Reclaimer::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
const std::string Reclaimer::ENTITY_NAME = "Reclaimer";
const std::string Reclaimer::XML_TAG_PREFIX = "Rec";


bool operator<(const Reclaimer::Id& a, const Reclaimer::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Reclaimer::Id& a, const Reclaimer::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const Reclaimer::Id& a, const Reclaimer::Id& b) {
     return !(a == b);
}

std::string Reclaimer::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}