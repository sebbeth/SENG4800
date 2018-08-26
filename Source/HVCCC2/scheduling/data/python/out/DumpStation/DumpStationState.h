#pragma once
#include <string>
#include "DumpStationEvent.h"
#include "DumpStationStateType.h"

class DumpStationState {
public:
    typedef DumpStationEvent AssociatedEvent;
    DumpStationStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amountDumped;
    int cycleID;
    std::string dumpStationID;
    std::string stockpileID;
    double time;
    DumpStationState() = default;
    static DumpStationStateType determineNextType(DumpStationStateType stateType, DumpStationEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void DumpStationState::serialize(Archive & archive) {
    archive(type, amountDumped, cycleID, dumpStationID, stockpileID, time);
}