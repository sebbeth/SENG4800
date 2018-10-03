/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
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