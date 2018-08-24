#pragma once
#include <string>
#include "StockpileEvent.h"
#include "StockpileStateType.h"

class StockpileState {
public:
    typedef StockpileEvent AssociatedEvent;
    StockpileStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    double length;
    std::string machineID;
    std::string padID;
    double startPosition;
    std::string stockpileID;
    double time;
    std::string vesselID;
    StockpileState() = default;
    static StockpileStateType determineNextType(StockpileStateType stateType, StockpileEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void StockpileState::serialize(Archive & archive) {
    archive(type, amount, length, machineID, padID, startPosition, stockpileID, time, vesselID);
}