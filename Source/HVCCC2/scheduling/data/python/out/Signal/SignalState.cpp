#include "SignalState.h"

SignalStateType SignalState::determineNextType(SignalStateType stateType, SignalEventType eventType) {
    switch(eventType) {
        case SignalEventType::StateChange:
            switch(stateType) {
                case SignalStateType::Green:
                    return SignalStateType::Red;
                case SignalStateType::Red:
                    return SignalStateType::Green;
                default:
                    return SignalStateType::Invalid;
            }
        default:
            return SignalStateType::Invalid;
    }
}