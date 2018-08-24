#pragma once
#include <string>
#include "StockpileEventType.h"

//forward declare a class to associate with the event
class StockpileState;

class StockpileEvent {
public:
    typedef StockpileState AssociatedState;
    StockpileEventType type;

    double amount;
    double length;
    std::string machineID;
    std::string padID;
    double startPosition;
    std::string stockpileID;
    double time;
    std::string vesselID;

    bool hasAmount() const;
    bool hasLength() const;
    bool hasMachineID() const;
    bool hasPadID() const;
    bool hasStartPosition() const;
    bool hasStockpileID() const;
    bool hasTime() const;
    bool hasVesselID() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void StockpileEvent::serialize(Archive & archive) {
    archive(type, amount, length, machineID, padID, startPosition, stockpileID, time, vesselID);
}