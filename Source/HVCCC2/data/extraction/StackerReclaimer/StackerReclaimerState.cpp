/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "StackerReclaimerState.h"
StackerReclaimerState::StackerReclaimerState(const StackerState& src): type(StackerReclaimerStateType::Invalid), id({src.id.terminal, src.id.name}), position(src.position), time(src.time), stockpileID(src.stockpileID), amount(src.amount){
    switch(src.type) {
        case StackerStateType::Idle:
            type = StackerReclaimerStateType::Idle;
            break;
        case StackerStateType::PreStackReserved:
            type = StackerReclaimerStateType::PreStackReserved;
            break;
        case StackerStateType::PreDoubleHandleReserved:
            type = StackerReclaimerStateType::PreDoubleHandleReserved;
            break;
        case StackerStateType::Moving:
            type = StackerReclaimerStateType::Moving;
            break;
        case StackerStateType::Maintenance:
            type = StackerReclaimerStateType::Maintenance;
            break;
        case StackerStateType::WrappedUp:
            type = StackerReclaimerStateType::WrappedUp;
            break;
        case StackerStateType::WorkingStack:
            type = StackerReclaimerStateType::WorkingStack;
            break;
        case StackerStateType::PreStackReservedFail:
            type = StackerReclaimerStateType::PreStackReservedFail;
            break;
        case StackerStateType::PreStackReservedSyncFail:
            type = StackerReclaimerStateType::PreStackReservedSyncFail;
            break;
        case StackerStateType::PostStackReserved:
            type = StackerReclaimerStateType::PostStackReserved;
            break;
        case StackerStateType::WorkingStackFail:
            type = StackerReclaimerStateType::WorkingStackFail;
            break;
        case StackerStateType::WorkingStackSyncFail:
            type = StackerReclaimerStateType::WorkingStackSyncFail;
            break;
        case StackerStateType::PostStackReservedFail:
            type = StackerReclaimerStateType::PostStackReservedFail;
            break;
        case StackerStateType::PostStackReservedSyncFail:
            type = StackerReclaimerStateType::PostStackReservedSyncFail;
            break;
        case StackerStateType::PreDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PreDoubleHandleReservedFail;
            break;
        case StackerStateType::PreDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PreDoubleHandleReservedSyncFail;
            break;
        case StackerStateType::WorkingDoubleHandle:
            type = StackerReclaimerStateType::WorkingDoubleHandle;
            break;
        case StackerStateType::PostDoubleHandleReserved:
            type = StackerReclaimerStateType::PostDoubleHandleReserved;
            break;
        case StackerStateType::WorkingDoubleHandleFail:
            type = StackerReclaimerStateType::WorkingDoubleHandleFail;
            break;
        case StackerStateType::WorkingDoubleHandleSyncFail:
            type = StackerReclaimerStateType::WorkingDoubleHandleSyncFail;
            break;
        case StackerStateType::PostDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PostDoubleHandleReservedFail;
            break;
        case StackerStateType::PostDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PostDoubleHandleReservedSyncFail;
            break;
        default:
            type = StackerReclaimerStateType::Invalid;
    }
}
StackerReclaimerState::StackerReclaimerState(const ReclaimerState& src): type(StackerReclaimerStateType::Invalid), id({src.id.terminal, src.id.name}), position(src.position), time(src.time), stockpileID(src.stockpileID), amount(src.amount){
    switch(src.type) {
        case ReclaimerStateType::Idle:
            type = StackerReclaimerStateType::Idle;
            break;
        case ReclaimerStateType::PreReclaimReserved:
            type = StackerReclaimerStateType::PreReclaimReserved;
            break;
        case ReclaimerStateType::PreDoubleHandleReserved:
            type = StackerReclaimerStateType::PreDoubleHandleReserved;
            break;
        case ReclaimerStateType::Moving:
            type = StackerReclaimerStateType::Moving;
            break;
        case ReclaimerStateType::Maintenance:
            type = StackerReclaimerStateType::Maintenance;
            break;
        case ReclaimerStateType::WrappedUp:
            type = StackerReclaimerStateType::WrappedUp;
            break;
        case ReclaimerStateType::WorkingReclaim:
            type = StackerReclaimerStateType::WorkingReclaim;
            break;
        case ReclaimerStateType::PreReclaimReservedFail:
            type = StackerReclaimerStateType::PreReclaimReservedFail;
            break;
        case ReclaimerStateType::PreReclaimReservedSyncFail:
            type = StackerReclaimerStateType::PreReclaimReservedSyncFail;
            break;
        case ReclaimerStateType::PostReclaimReserved:
            type = StackerReclaimerStateType::PostReclaimReserved;
            break;
        case ReclaimerStateType::WorkingReclaimFail:
            type = StackerReclaimerStateType::WorkingReclaimFail;
            break;
        case ReclaimerStateType::WorkingReclaimSyncFail:
            type = StackerReclaimerStateType::WorkingReclaimSyncFail;
            break;
        case ReclaimerStateType::PostReclaimReservedFail:
            type = StackerReclaimerStateType::PostReclaimReservedFail;
            break;
        case ReclaimerStateType::PostReclaimReservedSyncFail:
            type = StackerReclaimerStateType::PostReclaimReservedSyncFail;
            break;
        case ReclaimerStateType::PreDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PreDoubleHandleReservedFail;
            break;
        case ReclaimerStateType::PreDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PreDoubleHandleReservedSyncFail;
            break;
        case ReclaimerStateType::WorkingDoubleHandle:
            type = StackerReclaimerStateType::WorkingDoubleHandle;
            break;
        case ReclaimerStateType::PostDoubleHandleReserved:
            type = StackerReclaimerStateType::PostDoubleHandleReserved;
            break;
        case ReclaimerStateType::WorkingDoubleHandleFail:
            type = StackerReclaimerStateType::WorkingDoubleHandleFail;
            break;
        case ReclaimerStateType::WorkingDoubleHandleSyncFail:
            type = StackerReclaimerStateType::WorkingDoubleHandleSyncFail;
            break;
        case ReclaimerStateType::PostDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PostDoubleHandleReservedFail;
            break;
        case ReclaimerStateType::PostDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PostDoubleHandleReservedSyncFail;
            break;
        default:
            type = StackerReclaimerStateType::Invalid;
    }
}