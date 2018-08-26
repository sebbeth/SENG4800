#include "SignalStateType.h"

SignalStateType decodeSignalStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Green") {
        return SignalStateType::Green;
    } else if (enumeratorString == "Red") {
        return SignalStateType::Red;
    } else {
        return SignalStateType::Invalid;
    }
}