/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "VesselEventType.h"
        
VesselEventType decodeVesselEventType(const std::string& enumeratorString) {
    if (enumeratorString == "ArriveTerminal") {
        return VesselEventType::ArriveTerminal;
    } else if (enumeratorString == "AtEA") {
        return VesselEventType::AtAnchorage;
    } else if (enumeratorString == "Created") {
        return VesselEventType::Created;
    } else if (enumeratorString == "DepTerminal") {
        return VesselEventType::DepartTerminal;
    } else if (enumeratorString == "DraftSurveyComplete") {
        return VesselEventType::DraftSurveyComplete;
    } else if (enumeratorString == "DraftSurveyStart") {
        return VesselEventType::DraftSurveyStart;
    } else if (enumeratorString == "EnterChannel") {
        return VesselEventType::EnterChannel;
    } else if (enumeratorString == "ExitChannel") {
        return VesselEventType::ExitChannel;
    } else if (enumeratorString == "HatchChangeComplete") {
        return VesselEventType::HatchChangeComplete;
    } else if (enumeratorString == "StartLoading") {
        return VesselEventType::StartLoading;
    } else if (enumeratorString == "StopForDeballasting") {
        return VesselEventType::StopForDeballasting;
    } else if (enumeratorString == "StopForDeballastingComplete") {
        return VesselEventType::StopForDeballastingComplete;
    } else if (enumeratorString == "WaitBerth") {
        return VesselEventType::WaitBerth;
    } else if (enumeratorString == "WaitEnter") {
        return VesselEventType::WaitEnter;
    } else if (enumeratorString == "WaitSail") {
        return VesselEventType::WaitSail;
    } else {
        return VesselEventType::Invalid;
    }
}
std::string encodeVesselEventType(const VesselEventType& value) {
    switch(value) {
        case VesselEventType::AtAnchorage:
            return "AtEA";
            break;

        case VesselEventType::Created:
            return "Created";
            break;

        case VesselEventType::WaitBerth:
            return "WaitBerth";
            break;

        case VesselEventType::WaitEnter:
            return "WaitEnter";
            break;

        case VesselEventType::EnterChannel:
            return "EnterChannel";
            break;

        case VesselEventType::ArriveTerminal:
            return "ArriveTerminal";
            break;

        case VesselEventType::StartLoading:
            return "StartLoading";
            break;

        case VesselEventType::HatchChangeComplete:
            return "HatchChangeComplete";
            break;

        case VesselEventType::DraftSurveyStart:
            return "DraftSurveyStart";
            break;

        case VesselEventType::StopForDeballasting:
            return "StopForDeballasting";
            break;

        case VesselEventType::DraftSurveyComplete:
            return "DraftSurveyComplete";
            break;

        case VesselEventType::StopForDeballastingComplete:
            return "StopForDeballastingComplete";
            break;

        case VesselEventType::WaitSail:
            return "WaitSail";
            break;

        case VesselEventType::DepartTerminal:
            return "DepTerminal";
            break;

        case VesselEventType::ExitChannel:
            return "ExitChannel";
            break;

        default:
            return "Invalid";
    }
}