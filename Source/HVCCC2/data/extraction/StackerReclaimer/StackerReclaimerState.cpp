/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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
        case StackerStateType::PreStackDoubleHandleReserved:
            type = StackerReclaimerStateType::PreStackDoubleHandleReserved;
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
        case StackerStateType::PreStackDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PreStackDoubleHandleReservedFail;
            break;
        case StackerStateType::PreStackDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PreStackDoubleHandleReservedSyncFail;
            break;
        case StackerStateType::WorkingStackDoubleHandle:
            type = StackerReclaimerStateType::WorkingStackDoubleHandle;
            break;
        case StackerStateType::PostStackDoubleHandleReserved:
            type = StackerReclaimerStateType::PostStackDoubleHandleReserved;
            break;
        case StackerStateType::WorkingStackDoubleHandleFail:
            type = StackerReclaimerStateType::WorkingStackDoubleHandleFail;
            break;
        case StackerStateType::WorkingStackDoubleHandleSyncFail:
            type = StackerReclaimerStateType::WorkingStackDoubleHandleSyncFail;
            break;
        case StackerStateType::PostStackDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PostStackDoubleHandleReservedFail;
            break;
        case StackerStateType::PostStackDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PostStackDoubleHandleReservedSyncFail;
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
        case ReclaimerStateType::PreReclaimDoubleHandleReserved:
            type = StackerReclaimerStateType::PreReclaimDoubleHandleReserved;
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
        case ReclaimerStateType::PreReclaimDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PreReclaimDoubleHandleReservedFail;
            break;
        case ReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail;
            break;
        case ReclaimerStateType::WorkingReclaimDoubleHandle:
            type = StackerReclaimerStateType::WorkingReclaimDoubleHandle;
            break;
        case ReclaimerStateType::PostReclaimDoubleHandleReserved:
            type = StackerReclaimerStateType::PostReclaimDoubleHandleReserved;
            break;
        case ReclaimerStateType::WorkingReclaimDoubleHandleFail:
            type = StackerReclaimerStateType::WorkingReclaimDoubleHandleFail;
            break;
        case ReclaimerStateType::WorkingReclaimDoubleHandleSyncFail:
            type = StackerReclaimerStateType::WorkingReclaimDoubleHandleSyncFail;
            break;
        case ReclaimerStateType::PostReclaimDoubleHandleReservedFail:
            type = StackerReclaimerStateType::PostReclaimDoubleHandleReservedFail;
            break;
        case ReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail:
            type = StackerReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail;
            break;
        default:
            type = StackerReclaimerStateType::Invalid;
    }
}