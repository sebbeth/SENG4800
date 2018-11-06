/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ShiploaderEventType.h"
        
ShiploaderEventType decodeShiploaderEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Fail") {
        return ShiploaderEventType::Fail;
    } else if (enumeratorString == "FinishVesselDraftSurvey") {
        return ShiploaderEventType::FinishVesselDraftSurvey;
    } else if (enumeratorString == "Fix") {
        return ShiploaderEventType::Fix;
    } else if (enumeratorString == "HatchChangeStart") {
        return ShiploaderEventType::HatchChangeStart;
    } else if (enumeratorString == "LoadComp") {
        return ShiploaderEventType::LoadComplete;
    } else if (enumeratorString == "LoadOpComp") {
        return ShiploaderEventType::LoadOperationComplete;
    } else if (enumeratorString == "LoadOpStart") {
        return ShiploaderEventType::LoadOperationStart;
    } else if (enumeratorString == "LoadStart") {
        return ShiploaderEventType::LoadStart;
    } else if (enumeratorString == "MaintComp") {
        return ShiploaderEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return ShiploaderEventType::MaintenanceStart;
    } else if (enumeratorString == "OnHatchChangeComplete") {
        return ShiploaderEventType::OnHatchChangeComplete;
    } else if (enumeratorString == "OnMove") {
        return ShiploaderEventType::OnMove;
    } else if (enumeratorString == "OnStopMove") {
        return ShiploaderEventType::OnStopMove;
    } else if (enumeratorString == "StartVesselDraftSurvey") {
        return ShiploaderEventType::StartVesselDraftSurvey;
    } else if (enumeratorString == "StartVesselLoad") {
        return ShiploaderEventType::StartVesselLoad;
    } else if (enumeratorString == "SyncedFail") {
        return ShiploaderEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return ShiploaderEventType::SyncedFix;
    } else if (enumeratorString == "WrapUp") {
        return ShiploaderEventType::WrapUp;
    } else {
        return ShiploaderEventType::Invalid;
    }
}
std::string encodeShiploaderEventType(const ShiploaderEventType& value) {
    switch(value) {
        case ShiploaderEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case ShiploaderEventType::OnMove:
            return "OnMove";
            break;

        case ShiploaderEventType::StartVesselLoad:
            return "StartVesselLoad";
            break;

        case ShiploaderEventType::LoadOperationStart:
            return "LoadOpStart";
            break;

        case ShiploaderEventType::WrapUp:
            return "WrapUp";
            break;

        case ShiploaderEventType::MaintenanceComplete:
            return "MaintComp";
            break;

        case ShiploaderEventType::OnStopMove:
            return "OnStopMove";
            break;

        case ShiploaderEventType::LoadStart:
            return "LoadStart";
            break;

        case ShiploaderEventType::Fail:
            return "Fail";
            break;

        case ShiploaderEventType::SyncedFail:
            return "SyncedFail";
            break;

        case ShiploaderEventType::Fix:
            return "Fix";
            break;

        case ShiploaderEventType::SyncedFix:
            return "SyncedFix";
            break;

        case ShiploaderEventType::LoadComplete:
            return "LoadComp";
            break;

        case ShiploaderEventType::StartVesselDraftSurvey:
            return "StartVesselDraftSurvey";
            break;

        case ShiploaderEventType::HatchChangeStart:
            return "HatchChangeStart";
            break;

        case ShiploaderEventType::LoadOperationComplete:
            return "LoadOpComp";
            break;

        case ShiploaderEventType::FinishVesselDraftSurvey:
            return "FinishVesselDraftSurvey";
            break;

        case ShiploaderEventType::OnHatchChangeComplete:
            return "OnHatchChangeComplete";
            break;

        default:
            return "Invalid";
    }
}