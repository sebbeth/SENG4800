#pragma once
#include <string>
#include "ReclaimerEvent.h"
#include "ReclaimerStateType.h"

class ReclaimerState {
public:
    typedef ReclaimerEvent AssociatedEvent;
    ReclaimerStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    std::string machineID;
    double position;
    std::string stockpileID;
    double time;
    ReclaimerState() = default;
    static ReclaimerStateType determineNextType(ReclaimerStateType stateType, ReclaimerEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void ReclaimerState::serialize(Archive & archive) {
    archive(type, amount, machineID, position, stockpileID, time);
}