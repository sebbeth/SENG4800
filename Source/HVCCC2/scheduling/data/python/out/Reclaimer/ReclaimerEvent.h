#pragma once
#include <string>
#include "ReclaimerEventType.h"

//forward declare a class to associate with the event
class ReclaimerState;

class ReclaimerEvent {
public:
    typedef ReclaimerState AssociatedState;
    ReclaimerEventType type;

    double amount;
    std::string machineID;
    double position;
    std::string stockpileID;
    double time;

    bool hasAmount() const;
    bool hasMachineID() const;
    bool hasPosition() const;
    bool hasStockpileID() const;
    bool hasTime() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void ReclaimerEvent::serialize(Archive & archive) {
    archive(type, amount, machineID, position, stockpileID, time);
}