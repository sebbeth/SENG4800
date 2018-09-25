/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "TerminalId.h"
        
TerminalId decodeTerminalId(const std::string& enumeratorString) {
    if (enumeratorString == "CCT") {
        return TerminalId::CCT;
    } else if (enumeratorString == "KTC") {
        return TerminalId::KTC;
    } else if (enumeratorString == "NCT") {
        return TerminalId::NCT;
    } else {
        return TerminalId::Invalid;
    }
}
std::string encodeTerminalId(const TerminalId& value) {
    switch(value) {
        case TerminalId::CCT:
            return "CCT";
            break;

        case TerminalId::KTC:
            return "KTC";
            break;

        case TerminalId::NCT:
            return "NCT";
            break;

        default:
            return "Invalid";
    }
}