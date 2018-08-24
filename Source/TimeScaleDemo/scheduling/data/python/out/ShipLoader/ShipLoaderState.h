#pragma once
#include <string>
#include "ShipLoaderEvent.h"
#include "ShipLoaderStateType.h"

class ShipLoaderState {
public:
    typedef ShipLoaderEvent AssociatedEvent;
    ShipLoaderStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    double position;
    std::string shipLoaderID;
    std::string stockpileID;
    double time;
    int vesselID;
    ShipLoaderState() = default;
    static ShipLoaderStateType determineNextType(ShipLoaderStateType stateType, ShipLoaderEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void ShipLoaderState::serialize(Archive & archive) {
    archive(type, amount, position, shipLoaderID, stockpileID, time, vesselID);
}