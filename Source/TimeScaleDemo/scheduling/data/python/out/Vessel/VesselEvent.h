#pragma once
#include <string>
#include "VesselEventType.h"

//forward declare a class to associate with the event
class VesselState;

class VesselEvent {
public:
    typedef VesselState AssociatedState;
    VesselEventType type;

    bool isTidal;
    double meterMark;
    int numberOfTugs;
    std::string terminalID;
    double time;
    int vesselID;

    bool hasIsTidal() const;
    bool hasMeterMark() const;
    bool hasNumberOfTugs() const;
    bool hasTerminalID() const;
    bool hasTime() const;
    bool hasVesselID() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void VesselEvent::serialize(Archive & archive) {
    archive(type, isTidal, meterMark, numberOfTugs, terminalID, time, vesselID);
}