#include "VesselEventType.h"

VesselEventType decodeVesselEventType(const std::string& enumeratorString) {
    if (enumeratorString == "ArriveTerminal") {
        return VesselEventType::ArriveTerminal;
    } else if (enumeratorString == "AtEA") {
        return VesselEventType::AtAnchorage;
    } else if (enumeratorString == "DepTerminal") {
        return VesselEventType::DepartTerminal;
    } else if (enumeratorString == "EnterChannel") {
        return VesselEventType::EnterChannel;
    } else if (enumeratorString == "ExitChannel") {
        return VesselEventType::ExitChannel;
    } else if (enumeratorString == "MoveToSwingBasin") {
        return VesselEventType::MoveToSwingBasin;
    } else if (enumeratorString == "WaitBerth") {
        return VesselEventType::WaitBerth;
    } else if (enumeratorString == "WaitEnter") {
        return VesselEventType::WaitEnter;
    } else if (enumeratorString == "WaitSail") {
        return VesselEventType::WaitSail;
    } else if (enumeratorString == "YardSpaceAllocated") {
        return VesselEventType::YardSpaceAllocated;
    } else {
        return VesselEventType::Invalid;
    }
}