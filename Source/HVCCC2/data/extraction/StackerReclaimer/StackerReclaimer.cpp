/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "StackerReclaimer.h"

StackerReclaimer::Id::Id(): 
terminal(TerminalId::Invalid),  name("") {
}
StackerReclaimer::Id::Id(TerminalId terminal, const std::string& name): terminal(terminal), name(name) {
}
StackerReclaimer::Id::Id(const Stacker::Id& src): terminal(src.terminal), name(src.name) {
}
StackerReclaimer::Id::Id(const Reclaimer::Id& src): terminal(src.terminal), name(src.name) {
}
const std::string StackerReclaimer::ENTITY_NAME = "StackerReclaimer";

bool operator<(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b) {
    return a.terminal < b.terminal || (a.terminal == b.terminal && a.name < b.name);
}

bool operator==(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b) {
    return a.terminal == b.terminal && a.name == b.name;
}

bool operator!=(const StackerReclaimer::Id& a, const StackerReclaimer::Id& b) {
     return !(a == b);
}

std::string StackerReclaimer::Id::nameForBinaryFile() const {
    return encodeTerminalId(terminal) + '_' + name;
}