#pragma once
#include <string>
#include "ShipLoaderEventType.h"

//forward declare a class to associate with the event
class ShipLoaderState;

class ShipLoaderEvent {
public:
    typedef ShipLoaderState AssociatedState;
    ShipLoaderEventType type;

    double amount;
    double position;
    std::string shipLoaderID;
    std::string stockpileID;
    double time;
    int vesselID;

    bool hasAmount() const;
    bool hasPosition() const;
    bool hasShipLoaderID() const;
    bool hasStockpileID() const;
    bool hasTime() const;
    bool hasVesselID() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void ShipLoaderEvent::serialize(Archive & archive) {
    archive(type, amount, position, shipLoaderID, stockpileID, time, vesselID);
}