/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 22:50:11.670896
 **/
#pragma once
#include <string>
#include "Signal.h"
#include "SignalEvent.h"
#include "SignalStateType.h"
#include "../Signal/SignalStateType.h"
class SignalState {
public:
    using Entity = Signal;
    Entity::Id id;
    SignalStateType type;
    

    double time;
    
    SignalState() = default;

    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void SignalState::serialize(Archive & archive) {
    archive(id, type, time);
}