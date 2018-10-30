/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class VesselStateType {
    Berthed,
    ChangingHatches,
    Exited,
    Idle,
    InterimDraftSurvey,
    Loaded,
    Loading,
    StoppedForDeballasting,
    TravellingFromTerminal,
    TravellingToTerminal,
    WaitingForBerth,
    WaitingForCoal,
    WaitingToEnter,
    WaitingToSail,
    Invalid
};

VesselStateType decodeVesselStateType(const std::string& enumeratorString);
std::string encodeVesselStateType(const VesselStateType& value);