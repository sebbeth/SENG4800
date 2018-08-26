#pragma once
#include <string>
#include "SignalEventType.h"

//forward declare a class to associate with the event
class SignalState;

#include "../Signal/SignalStateType.h"
class SignalEvent {
public:
    typedef SignalState AssociatedState;
    SignalEventType type;

    std::string signalID;
    SignalStateType signalState;
    double time;

    bool hasSignalID() const;
    bool hasSignalState() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void SignalEvent::serialize(Archive & archive) {
    archive(type, signalID, signalState, time);
}