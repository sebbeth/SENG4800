#pragma once
#include <string>

enum class VesselEventType {
    ArriveTerminal,
    AtAnchorage,
    DepartTerminal,
    EnterChannel,
    ExitChannel,
    MoveToSwingBasin,
    WaitBerth,
    WaitEnter,
    WaitSail,
    YardSpaceAllocated,
    Invalid
};

VesselEventType decodeVesselEventType(const std::string& enumeratorString);