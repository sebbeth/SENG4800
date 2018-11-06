/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ShiploaderStateType.h"
        
ShiploaderStateType decodeShiploaderStateType(const std::string& enumeratorString) {
    if (enumeratorString == "ChangingHatches") {
        return ShiploaderStateType::ChangingHatches;
    } else if (enumeratorString == "ChangingHatchesFailed") {
        return ShiploaderStateType::ChangingHatchesFailed;
    } else if (enumeratorString == "ChangingHatchesSyncedFail") {
        return ShiploaderStateType::ChangingHatchesSyncedFail;
    } else if (enumeratorString == "ChangingHatchesSyncedFailed") {
        return ShiploaderStateType::ChangingHatchesSyncedFailed;
    } else if (enumeratorString == "ChaningHatches") {
        return ShiploaderStateType::ChaningHatches;
    } else if (enumeratorString == "Idle") {
        return ShiploaderStateType::Idle;
    } else if (enumeratorString == "InterimDraftSurvey") {
        return ShiploaderStateType::InterimDraftSurvey;
    } else if (enumeratorString == "InterimDraftSyncFail") {
        return ShiploaderStateType::InterimDraftSyncFail;
    } else if (enumeratorString == "Maintenance") {
        return ShiploaderStateType::Maintenance;
    } else if (enumeratorString == "Moving") {
        return ShiploaderStateType::Moving;
    } else if (enumeratorString == "PostLoadFailed") {
        return ShiploaderStateType::PostLoadFailed;
    } else if (enumeratorString == "PostLoadReserved") {
        return ShiploaderStateType::PostLoadReserved;
    } else if (enumeratorString == "PostLoadSyncedFail") {
        return ShiploaderStateType::PostLoadSyncedFail;
    } else if (enumeratorString == "PreLoadFailed") {
        return ShiploaderStateType::PreLoadFailed;
    } else if (enumeratorString == "PreLoadReserved") {
        return ShiploaderStateType::PreLoadReserved;
    } else if (enumeratorString == "PreLoadSyncedFail") {
        return ShiploaderStateType::PreLoadSyncedFail;
    } else if (enumeratorString == "Working") {
        return ShiploaderStateType::Working;
    } else if (enumeratorString == "WorkingFailed") {
        return ShiploaderStateType::WorkingFailed;
    } else if (enumeratorString == "WorkingSyncedFail") {
        return ShiploaderStateType::WorkingSyncedFail;
    } else if (enumeratorString == "WrappedUp") {
        return ShiploaderStateType::WrappedUp;
    } else {
        return ShiploaderStateType::Invalid;
    }
}
std::string encodeShiploaderStateType(const ShiploaderStateType& value) {
    switch(value) {
        case ShiploaderStateType::Idle:
            return "Idle";
            break;

        case ShiploaderStateType::Maintenance:
            return "Maintenance";
            break;

        case ShiploaderStateType::Moving:
            return "Moving";
            break;

        case ShiploaderStateType::PreLoadReserved:
            return "PreLoadReserved";
            break;

        case ShiploaderStateType::WrappedUp:
            return "WrappedUp";
            break;

        case ShiploaderStateType::Working:
            return "Working";
            break;

        case ShiploaderStateType::PreLoadFailed:
            return "PreLoadFailed";
            break;

        case ShiploaderStateType::PreLoadSyncedFail:
            return "PreLoadSyncedFail";
            break;

        case ShiploaderStateType::WorkingFailed:
            return "WorkingFailed";
            break;

        case ShiploaderStateType::PostLoadReserved:
            return "PostLoadReserved";
            break;

        case ShiploaderStateType::InterimDraftSurvey:
            return "InterimDraftSurvey";
            break;

        case ShiploaderStateType::WorkingSyncedFail:
            return "WorkingSyncedFail";
            break;

        case ShiploaderStateType::ChaningHatches:
            return "ChaningHatches";
            break;

        case ShiploaderStateType::PostLoadSyncedFail:
            return "PostLoadSyncedFail";
            break;

        case ShiploaderStateType::PostLoadFailed:
            return "PostLoadFailed";
            break;

        case ShiploaderStateType::InterimDraftSyncFail:
            return "InterimDraftSyncFail";
            break;

        case ShiploaderStateType::ChangingHatches:
            return "ChangingHatches";
            break;

        case ShiploaderStateType::ChangingHatchesSyncedFail:
            return "ChangingHatchesSyncedFail";
            break;

        case ShiploaderStateType::ChangingHatchesFailed:
            return "ChangingHatchesFailed";
            break;

        case ShiploaderStateType::ChangingHatchesSyncedFailed:
            return "ChangingHatchesSyncedFailed";
            break;

        default:
            return "Invalid";
    }
}