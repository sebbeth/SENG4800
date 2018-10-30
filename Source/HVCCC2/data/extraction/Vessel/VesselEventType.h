/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class VesselEventType {
    ArriveTerminal,
    AtAnchorage,
    BallastTankEmpty,
    Created,
    DepartTerminal,
    DraftSurveyComplete,
    DraftSurveyStart,
    EnterChannel,
    ExitChannel,
    FullyLoaded,
    HatchChangeComplete,
    HatchChangeStart,
    StartLoading,
    StopForDeballasting,
    StopForDeballastingComplete,
    WaitBerth,
    WaitEnter,
    WaitSail,
    YardSpaceAllocated,
    Invalid
};

VesselEventType decodeVesselEventType(const std::string& enumeratorString);
std::string encodeVesselEventType(const VesselEventType& value);