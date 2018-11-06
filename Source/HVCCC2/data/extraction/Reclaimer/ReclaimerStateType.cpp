/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ReclaimerStateType.h"
        
ReclaimerStateType decodeReclaimerStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return ReclaimerStateType::Idle;
    } else if (enumeratorString == "Maintenance") {
        return ReclaimerStateType::Maintenance;
    } else if (enumeratorString == "Moving") {
        return ReclaimerStateType::Moving;
    } else if (enumeratorString == "PostReclaimDoubleHandleReserved") {
        return ReclaimerStateType::PostReclaimDoubleHandleReserved;
    } else if (enumeratorString == "PostReclaimDoubleHandleReservedFail") {
        return ReclaimerStateType::PostReclaimDoubleHandleReservedFail;
    } else if (enumeratorString == "PostReclaimDoubleHandleReservedSyncFail") {
        return ReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PostReclaimReserved") {
        return ReclaimerStateType::PostReclaimReserved;
    } else if (enumeratorString == "PostReclaimReservedFail") {
        return ReclaimerStateType::PostReclaimReservedFail;
    } else if (enumeratorString == "PostReclaimReservedSyncFail") {
        return ReclaimerStateType::PostReclaimReservedSyncFail;
    } else if (enumeratorString == "PreReclaimDoubleHandleReserved") {
        return ReclaimerStateType::PreReclaimDoubleHandleReserved;
    } else if (enumeratorString == "PreReclaimDoubleHandleReservedFail") {
        return ReclaimerStateType::PreReclaimDoubleHandleReservedFail;
    } else if (enumeratorString == "PreReclaimDoubleHandleReservedSyncFail") {
        return ReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PreReclaimReserved") {
        return ReclaimerStateType::PreReclaimReserved;
    } else if (enumeratorString == "PreReclaimReservedFail") {
        return ReclaimerStateType::PreReclaimReservedFail;
    } else if (enumeratorString == "PreReclaimReservedSyncFail") {
        return ReclaimerStateType::PreReclaimReservedSyncFail;
    } else if (enumeratorString == "WorkingReclaim") {
        return ReclaimerStateType::WorkingReclaim;
    } else if (enumeratorString == "WorkingReclaimDoubleHandle") {
        return ReclaimerStateType::WorkingReclaimDoubleHandle;
    } else if (enumeratorString == "WorkingReclaimDoubleHandleFail") {
        return ReclaimerStateType::WorkingReclaimDoubleHandleFail;
    } else if (enumeratorString == "WorkingReclaimDoubleHandleSyncFail") {
        return ReclaimerStateType::WorkingReclaimDoubleHandleSyncFail;
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

        case ReclaimerStateType::PreReclaimDoubleHandleReserved:
            return "PreReclaimDoubleHandleReserved";
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

        case ReclaimerStateType::PreReclaimDoubleHandleReservedFail:
            return "PreReclaimDoubleHandleReservedFail";
            break;

        case ReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail:
            return "PreReclaimDoubleHandleReservedSyncFail";
            break;

        case ReclaimerStateType::WorkingReclaimDoubleHandle:
            return "WorkingReclaimDoubleHandle";
            break;

        case ReclaimerStateType::PostReclaimDoubleHandleReserved:
            return "PostReclaimDoubleHandleReserved";
            break;

        case ReclaimerStateType::WorkingReclaimDoubleHandleFail:
            return "WorkingReclaimDoubleHandleFail";
            break;

        case ReclaimerStateType::WorkingReclaimDoubleHandleSyncFail:
            return "WorkingReclaimDoubleHandleSyncFail";
            break;

        case ReclaimerStateType::PostReclaimDoubleHandleReservedFail:
            return "PostReclaimDoubleHandleReservedFail";
            break;

        case ReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail:
            return "PostReclaimDoubleHandleReservedSyncFail";
            break;

        default:
            return "Invalid";
    }
}