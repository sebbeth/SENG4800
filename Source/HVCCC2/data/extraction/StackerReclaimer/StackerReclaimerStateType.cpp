/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
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

        case StackerReclaimerStateType::PreDoubleHandleReserved:
            return "PreDoubleHandleReserved";
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

        case StackerReclaimerStateType::PreDoubleHandleReservedFail:
            return "PreDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PreDoubleHandleReservedSyncFail:
            return "PreDoubleHandleReservedSyncFail";
            break;

        case StackerReclaimerStateType::WorkingDoubleHandle:
            return "WorkingDoubleHandle";
            break;

        case StackerReclaimerStateType::PostDoubleHandleReserved:
            return "PostDoubleHandleReserved";
            break;

        case StackerReclaimerStateType::WorkingDoubleHandleFail:
            return "WorkingDoubleHandleFail";
            break;

        case StackerReclaimerStateType::WorkingDoubleHandleSyncFail:
            return "WorkingDoubleHandleSyncFail";
            break;

        case StackerReclaimerStateType::PostDoubleHandleReservedFail:
            return "PostDoubleHandleReservedFail";
            break;

        case StackerReclaimerStateType::PostDoubleHandleReservedSyncFail:
            return "PostDoubleHandleReservedSyncFail";
            break;

        case StackerReclaimerStateType::PreReclaimReserved:
            return "PreReclaimReserved";
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

        default:
            return "Invalid";
    }
}