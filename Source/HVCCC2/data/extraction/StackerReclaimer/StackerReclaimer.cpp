/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "StackerReclaimer.h"
const std::string StackerReclaimer::ENTITY_NAME = "StackerReclaimer";

bool operator<(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b) {
    return a.terminal < b.terminal &&a.name < b.name;
}

bool operator==(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b) {
    return a.terminal == b.terminal &&a.name == b.name;
}
std::string StackerReclaimer::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}