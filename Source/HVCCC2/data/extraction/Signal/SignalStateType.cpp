/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "SignalStateType.h"
        
SignalStateType decodeSignalStateType(const std::string& enumeratorString) {
    if (enumeratorString == "GREEN") {
        return SignalStateType::Green;
    } else if (enumeratorString == "RED") {
        return SignalStateType::Red;
    } else {
        return SignalStateType::Invalid;
    }
}
std::string encodeSignalStateType(const SignalStateType& value) {
    switch(value) {
        case SignalStateType::Green:
            return "GREEN";
            break;

        case SignalStateType::Red:
            return "RED";
            break;

        default:
            return "Invalid";
    }
}