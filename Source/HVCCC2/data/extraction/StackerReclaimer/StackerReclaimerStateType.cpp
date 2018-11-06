/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StackerReclaimerStateType.h"
        
std::string encodeStackerReclaimerStateType(const StackerReclaimerStateType& value) {
    switch(value) {
        case StackerReclaimerStateType::Idle:
            return "Idle";
            break;

        case StackerReclaimerStateType::PreStackReserved:
            return "PreStackReserved";
            break;

        case StackerReclaimerStateType::PreStackDoubleHandleReserved:
            return "PreStackDoubleHandleReserved";
            break;

        case StackerReclaimerStateType::Moving:
            return "Moving";
            break;

        case StackerReclaimerStateType::Maintenance:
            return "Maintenance";
            break;

        case StackerReclaimerStateType::WrappedUp:
            return "WrappedUp";
            break;

        case StackerReclaimerStateType::WorkingStack:
            return "WorkingStack";
            break;

        case StackerReclaimerStateType::PreStackReservedFail:
            return "PreStackReservedFail";
            break;

        case StackerReclaimerStateType::PreStackReservedSyncFail:
            return "PreStackReservedSyncFail";
            break;

        case StackerReclaimerStateType::PostStackReserved:
            return "PostStackReserved";
            break;

        case StackerReclaimerStateType::WorkingStackFail:
            return "WorkingStackFail";
            break;

        case StackerReclaimerStateType::WorkingStackSyncFail:
            return "WorkingStackSyncFail";
            break;

        case StackerReclaimerStateType::PostStackReservedFail:
            return "PostStackReservedFail";
            break;

        case StackerReclaimerStateType::PostStackReservedSyncFail:
            return "PostStackReservedSyncFail";
            break;

        case StackerReclaimerStateType::PreStackDoubleHandleReservedFail:
            return "PreStackDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PreStackDoubleHandleReservedSyncFail:
            return "PreStackDoubleHandleReservedSyncFail";
            break;

        case StackerReclaimerStateType::WorkingStackDoubleHandle:
            return "WorkingStackDoubleHandle";
            break;

        case StackerReclaimerStateType::PostStackDoubleHandleReserved:
            return "PostStackDoubleHandleReserved";
            break;

        case StackerReclaimerStateType::WorkingStackDoubleHandleFail:
            return "WorkingStackDoubleHandleFail";
            break;

        case StackerReclaimerStateType::WorkingStackDoubleHandleSyncFail:
            return "WorkingStackDoubleHandleSyncFail";
            break;

        case StackerReclaimerStateType::PostStackDoubleHandleReservedFail:
            return "PostStackDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PostStackDoubleHandleReservedSyncFail:
            return "PostStackDoubleHandleReservedSyncFail";
            break;

        case StackerReclaimerStateType::PreReclaimReserved:
            return "PreReclaimReserved";
            break;

        case StackerReclaimerStateType::PreReclaimDoubleHandleReserved:
            return "PreReclaimDoubleHandleReserved";
            break;

        case StackerReclaimerStateType::WorkingReclaim:
            return "WorkingReclaim";
            break;

        case StackerReclaimerStateType::PreReclaimReservedFail:
            return "PreReclaimReservedFail";
            break;

        case StackerReclaimerStateType::PreReclaimReservedSyncFail:
            return "PreReclaimReservedSyncFail";
            break;

        case StackerReclaimerStateType::PostReclaimReserved:
            return "PostReclaimReserved";
            break;

        case StackerReclaimerStateType::WorkingReclaimFail:
            return "WorkingReclaimFail";
            break;

        case StackerReclaimerStateType::WorkingReclaimSyncFail:
            return "WorkingReclaimSyncFail";
            break;

        case StackerReclaimerStateType::PostReclaimReservedFail:
            return "PostReclaimReservedFail";
            break;

        case StackerReclaimerStateType::PostReclaimReservedSyncFail:
            return "PostReclaimReservedSyncFail";
            break;

        case StackerReclaimerStateType::PreReclaimDoubleHandleReservedFail:
            return "PreReclaimDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail:
            return "PreReclaimDoubleHandleReservedSyncFail";
            break;

        case StackerReclaimerStateType::WorkingReclaimDoubleHandle:
            return "WorkingReclaimDoubleHandle";
            break;

        case StackerReclaimerStateType::PostReclaimDoubleHandleReserved:
            return "PostReclaimDoubleHandleReserved";
            break;

        case StackerReclaimerStateType::WorkingReclaimDoubleHandleFail:
            return "WorkingReclaimDoubleHandleFail";
            break;

        case StackerReclaimerStateType::WorkingReclaimDoubleHandleSyncFail:
            return "WorkingReclaimDoubleHandleSyncFail";
            break;

        case StackerReclaimerStateType::PostReclaimDoubleHandleReservedFail:
            return "PostReclaimDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail:
            return "PostReclaimDoubleHandleReservedSyncFail";
            break;

        default:
            return "Invalid";
    }
}