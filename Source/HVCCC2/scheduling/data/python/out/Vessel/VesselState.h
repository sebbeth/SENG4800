#pragma once
#include <string>
#include "VesselEvent.h"
#include "VesselStateType.h"

class VesselState {
public:
    typedef VesselEvent AssociatedEvent;
    VesselStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    bool isTidal;
    double meterMark;
    int numberOfTugs;
    std::string terminalID;
    double time;
    int vesselID;
    VesselState() = default;
    static VesselStateType determineNextType(VesselStateType stateType, VesselEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void VesselState::serialize(Archive & archive) {
    archive(type, isTidal, meterMark, numberOfTugs, terminalID, time, vesselID);
}