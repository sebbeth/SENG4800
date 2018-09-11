/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#pragma once
#include <string>
#include "SignalEventType.h"
#include "Signal.h"
#include "../Signal/SignalStateType.h"
class SignalEvent {
public:
    using Entity = Signal;
    Entity::Id id;
    SignalEventType type;

    SignalStateType signalState;
    double time;

    bool hasSignalState() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void SignalEvent::serialize(Archive & archive) {
    archive(id, type, signalState, time);
}