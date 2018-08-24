#pragma once
#include <string>

enum class VesselStateType {
    Berthed,
    Exited,
    Idle,
    NA,
    TravellingFromTerminal,
    TravellingToTerminal,
    WaitingForBerth,
    WaitingForCoal,
    WaitingToEnter,
    WaitingToSail,
    Invalid
};