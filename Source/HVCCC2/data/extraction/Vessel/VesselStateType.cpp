/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "VesselStateType.h"
        
VesselStateType decodeVesselStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Berthed") {
        return VesselStateType::Berthed;
    } else if (enumeratorString == "ChangingHatches") {
        return VesselStateType::ChangingHatches;
    } else if (enumeratorString == "Exited") {
        return VesselStateType::Exited;
    } else if (enumeratorString == "Idle") {
        return VesselStateType::Idle;
    } else if (enumeratorString == "InterimDraftSurvey") {
        return VesselStateType::InterimDraftSurvey;
    } else if (enumeratorString == "Loaded") {
        return VesselStateType::Loaded;
    } else if (enumeratorString == "Loading") {
        return VesselStateType::Loading;
    } else if (enumeratorString == "StoppedForDeballasting") {
        return VesselStateType::StoppedForDeballasting;
    } else if (enumeratorString == "TravellingFromTerminal") {
        return VesselStateType::TravellingFromTerminal;
    } else if (enumeratorString == "TravellingToTerminal") {
        return VesselStateType::TravellingToTerminal;
    } else if (enumeratorString == "WaitingForBerth") {
        return VesselStateType::WaitingForBerth;
    } else if (enumeratorString == "WaitingForCoal") {
        return VesselStateType::WaitingForCoal;
    } else if (enumeratorString == "WaitingToEnter") {
        return VesselStateType::WaitingToEnter;
    } else if (enumeratorString == "WaitingToSail") {
        return VesselStateType::WaitingToSail;
    } else {
        return VesselStateType::Invalid;
    }
}
std::string encodeVesselStateType(const VesselStateType& value) {
    switch(value) {
        case VesselStateType::Idle:
            return "Idle";
            break;

        case VesselStateType::WaitingForCoal:
            return "WaitingForCoal";
            break;

        case VesselStateType::WaitingForBerth:
            return "WaitingForBerth";
            break;

        case VesselStateType::WaitingToEnter:
            return "WaitingToEnter";
            break;

        case VesselStateType::TravellingToTerminal:
            return "TravellingToTerminal";
            break;

        case VesselStateType::Berthed:
            return "Berthed";
            break;

        case VesselStateType::Loading:
            return "Loading";
            break;

        case VesselStateType::ChangingHatches:
            return "ChangingHatches";
            break;

        case VesselStateType::InterimDraftSurvey:
            return "InterimDraftSurvey";
            break;

        case VesselStateType::StoppedForDeballasting:
            return "StoppedForDeballasting";
            break;

        case VesselStateType::Loaded:
            return "Loaded";
            break;

        case VesselStateType::WaitingToSail:
            return "WaitingToSail";
            break;

        case VesselStateType::TravellingFromTerminal:
            return "TravellingFromTerminal";
            break;

        case VesselStateType::Exited:
            return "Exited";
            break;

        default:
            return "Invalid";
    }
}