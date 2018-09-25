/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#pragma once
#include <string>

enum class VesselEventType {
    ArriveTerminal,
    AtAnchorage,
    Created,
    DepartTerminal,
    DraftSurveyComplete,
    DraftSurveyStart,
    EnterChannel,
    ExitChannel,
    HatchChangeComplete,
    StartLoading,
    StopForDeballasting,
    StopForDeballastingComplete,
    WaitBerth,
    WaitEnter,
    WaitSail,
    Invalid
};

VesselEventType decodeVesselEventType(const std::string& enumeratorString);
std::string encodeVesselEventType(const VesselEventType& value);