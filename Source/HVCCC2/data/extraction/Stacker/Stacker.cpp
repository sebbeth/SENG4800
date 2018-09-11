/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "Stacker.h"
const std::string Stacker::ENTITY_NAME = "Stacker";
const std::string Stacker::XML_TAG_PREFIX = "Stk";


bool operator<(const Stacker::Id& a, const Stacker::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const Stacker::Id& a, const Stacker::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}
std::string Stacker::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}