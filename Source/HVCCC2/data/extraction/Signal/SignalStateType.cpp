/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 22:50:11.670896
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