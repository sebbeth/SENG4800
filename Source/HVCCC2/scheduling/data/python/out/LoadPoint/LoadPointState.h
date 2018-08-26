#pragma once
#include <string>
#include "LoadPointEvent.h"
#include "LoadPointStateType.h"

class LoadPointState {
public:
    typedef LoadPointEvent AssociatedEvent;
    LoadPointStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    int cycleID;
    std::string loadPointID;
    std::string loadPointName;
    double time;
    LoadPointState() = default;
    static LoadPointStateType determineNextType(LoadPointStateType stateType, LoadPointEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void LoadPointState::serialize(Archive & archive) {
    archive(type, amount, cycleID, loadPointID, loadPointName, time);
}