#pragma once
#include <string>
#include "SignalEvent.h"
#include "SignalStateType.h"

class SignalState {
public:
    typedef SignalEvent AssociatedEvent;
    SignalStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    std::string signalID;
    SignalStateType signalState;
    double time;
    SignalState() = default;
    static SignalStateType determineNextType(SignalStateType stateType, SignalEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void SignalState::serialize(Archive & archive) {
    archive(type, signalID, signalState, time);
}