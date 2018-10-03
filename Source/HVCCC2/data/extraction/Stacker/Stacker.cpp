/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "Stacker.h"

Stacker::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
Stacker::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
const std::string Stacker::ENTITY_NAME = "Stacker";
const std::string Stacker::XML_TAG_PREFIX = "Stk";


bool operator<(const Stacker::Id& a, const Stacker::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Stacker::Id& a, const Stacker::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const Stacker::Id& a, const Stacker::Id& b) {
     return !(a == b);
}

std::string Stacker::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}