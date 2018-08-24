#pragma once
#include <string>
#include "DumpStationEventType.h"

//forward declare a class to associate with the event
class DumpStationState;

class DumpStationEvent {
public:
    typedef DumpStationState AssociatedState;
    DumpStationEventType type;

    double amountDumped;
    int cycleID;
    std::string dumpStationID;
    std::string stockpileID;
    double time;

    bool hasAmountDumped() const;
    bool hasCycleID() const;
    bool hasDumpStationID() const;
    bool hasStockpileID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void DumpStationEvent::serialize(Archive & archive) {
    archive(type, amountDumped, cycleID, dumpStationID, stockpileID, time);
}