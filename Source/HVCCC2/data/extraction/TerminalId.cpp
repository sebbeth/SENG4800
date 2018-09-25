/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#include "TerminalId.h"
        
TerminalId decodeTerminalId(const std::string& enumeratorString) {
    if (enumeratorString == "CCT") {
        return TerminalId::CCT;
    } else if (enumeratorString == "KCT") {
        return TerminalId::KCT;
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

        case TerminalId::KCT:
            return "KCT";
            break;

        case TerminalId::NCT:
            return "NCT";
            break;

        default:
            return "Invalid";
    }
}