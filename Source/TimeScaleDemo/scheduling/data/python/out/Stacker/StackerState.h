#pragma once
#include <string>
#include "StackerEvent.h"
#include "StackerStateType.h"

class StackerState {
public:
    typedef StackerEvent AssociatedEvent;
    StackerStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    std::string machineID;
    double position;
    std::string stockpileID;
    double time;
    StackerState() = default;
    static StackerStateType determineNextType(StackerStateType stateType, StackerEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void StackerState::serialize(Archive & archive) {
    archive(type, amount, machineID, position, stockpileID, time);
}