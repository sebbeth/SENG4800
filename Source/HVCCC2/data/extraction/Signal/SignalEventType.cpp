/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "SignalEventType.h"
        
SignalEventType decodeSignalEventType(const std::string& enumeratorString) {
    if (enumeratorString == "StateChange") {
        return SignalEventType::StateChange;
    } else {
        return SignalEventType::Invalid;
    }
}
std::string encodeSignalEventType(const SignalEventType& value) {
    switch(value) {
        case SignalEventType::StateChange:
            return "StateChange";
            break;

        default:
            return "Invalid";
    }
}