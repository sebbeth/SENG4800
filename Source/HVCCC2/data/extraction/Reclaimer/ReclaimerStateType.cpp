/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#include "ReclaimerStateType.h"
        
ReclaimerStateType decodeReclaimerStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return ReclaimerStateType::Idle;
    } else if (enumeratorString == "Maintenance") {
        return ReclaimerStateType::Maintenance;
    } else if (enumeratorString == "Moving") {
        return ReclaimerStateType::Moving;
    } else if (enumeratorString == "PostDoubleHandleReserved") {
        return ReclaimerStateType::PostDoubleHandleReserved;
    } else if (enumeratorString == "PostDoubleHandleReservedFail") {
        return ReclaimerStateType::PostDoubleHandleReservedFail;
    } else if (enumeratorString == "PostDoubleHandleReservedSyncFail") {
        return ReclaimerStateType::PostDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PostReclaimReserved") {
        return ReclaimerStateType::PostReclaimReserved;
    } else if (enumeratorString == "PostReclaimReservedFail") {
        return ReclaimerStateType::PostReclaimReservedFail;
    } else if (enumeratorString == "PostReclaimReservedSyncFail") {
        return ReclaimerStateType::PostReclaimReservedSyncFail;
    } else if (enumeratorString == "PreDoubleHandleReserved") {
        return ReclaimerStateType::PreDoubleHandleReserved;
    } else if (enumeratorString == "PreDoubleHandleReservedFail") {
        return ReclaimerStateType::PreDoubleHandleReservedFail;
    } else if (enumeratorString == "PreDoubleHandleReservedSyncFail") {
        return ReclaimerStateType::PreDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PreReclaimReserved") {
        return ReclaimerStateType::PreReclaimReserved;
    } else if (enumeratorString == "PreReclaimReservedFail") {
        return ReclaimerStateType::PreReclaimReservedFail;
    } else if (enumeratorString == "PreReclaimReservedSyncFail") {
        return ReclaimerStateType::PreReclaimReservedSyncFail;
    } else if (enumeratorString == "WorkingDoubleHandle") {
        return ReclaimerStateType::WorkingDoubleHandle;
    } else if (enumeratorString == "WorkingDoubleHandleFail") {
        return ReclaimerStateType::WorkingDoubleHandleFail;
    } else if (enumeratorString == "WorkingDoubleHandleSyncFail") {
        return ReclaimerStateType::WorkingDoubleHandleSyncFail;
    } else if (enumeratorString == "WorkingReclaim") {
        return ReclaimerStateType::WorkingReclaim;
    } else if (enumeratorString == "WorkingReclaimFail") {
        return ReclaimerStateType::WorkingReclaimFail;
    } else if (enumeratorString == "WorkingReclaimSyncFail") {
        return ReclaimerStateType::WorkingReclaimSyncFail;
    } else if (enumeratorString == "WrappedUp") {
        return ReclaimerStateType::WrappedUp;
    } else {
        return ReclaimerStateType::Invalid;
    }
}
std::string encodeReclaimerStateType(const ReclaimerStateType& value) {
    switch(value) {
        case ReclaimerStateType::Idle:
            return "Idle";
            break;

        case ReclaimerStateType::PreReclaimReserved:
            return "PreReclaimReserved";
            break;

        case ReclaimerStateType::PreDoubleHandleReserved:
            return "PreDoubleHandleReserved";
            break;

        case ReclaimerStateType::Moving:
            return "Moving";
            break;

        case ReclaimerStateType::Maintenance:
            return "Maintenance";
            break;

        case ReclaimerStateType::WrappedUp:
            return "WrappedUp";
            break;

        case ReclaimerStateType::WorkingReclaim:
            return "WorkingReclaim";
            break;

        case ReclaimerStateType::PreReclaimReservedFail:
            return "PreReclaimReservedFail";
            break;

        case ReclaimerStateType::PreReclaimReservedSyncFail:
            return "PreReclaimReservedSyncFail";
            break;

        case ReclaimerStateType::PostReclaimReserved:
            return "PostReclaimReserved";
            break;

        case ReclaimerStateType::WorkingReclaimFail:
            return "WorkingReclaimFail";
            break;

        case ReclaimerStateType::WorkingReclaimSyncFail:
            return "WorkingReclaimSyncFail";
            break;

        case ReclaimerStateType::PostReclaimReservedFail:
            return "PostReclaimReservedFail";
            break;

        case ReclaimerStateType::PostReclaimReservedSyncFail:
            return "PostReclaimReservedSyncFail";
            break;

        case ReclaimerStateType::PreDoubleHandleReservedFail:
            return "PreDoubleHandleReservedFail";
            break;

        case ReclaimerStateType::PreDoubleHandleReservedSyncFail:
            return "PreDoubleHandleReservedSyncFail";
            break;

        case ReclaimerStateType::WorkingDoubleHandle:
            return "WorkingDoubleHandle";
            break;

        case ReclaimerStateType::PostDoubleHandleReserved:
            return "PostDoubleHandleReserved";
            break;

        case ReclaimerStateType::WorkingDoubleHandleFail:
            return "WorkingDoubleHandleFail";
            break;

        case ReclaimerStateType::WorkingDoubleHandleSyncFail:
            return "WorkingDoubleHandleSyncFail";
            break;

        case ReclaimerStateType::PostDoubleHandleReservedFail:
            return "PostDoubleHandleReservedFail";
            break;

        case ReclaimerStateType::PostDoubleHandleReservedSyncFail:
            return "PostDoubleHandleReservedSyncFail";
            break;

        default:
            return "Invalid";
    }
}