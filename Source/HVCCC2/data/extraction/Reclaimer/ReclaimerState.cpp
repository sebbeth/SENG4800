/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "ReclaimerState.h"

ReclaimerStateType ReclaimerState::determineNextType(ReclaimerStateType stateType, ReclaimerEventType eventType) {
    switch(stateType) {
        case ReclaimerStateType::Idle:
            switch(eventType) {
                case ReclaimerEventType::OperationStart:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerEventType::DoubleHandleOperationStart:
                    return ReclaimerStateType::PreDoubleHandleReserved;
                case ReclaimerEventType::OnMove:
                    return ReclaimerStateType::Moving;
                case ReclaimerEventType::MaintenanceStart:
                    return ReclaimerStateType::Maintenance;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimReserved:
            switch(eventType) {
                case ReclaimerEventType::Start:
                    return ReclaimerStateType::WorkingReclaim;
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PreReclaimReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PreReclaimReservedSyncFail;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreDoubleHandleReserved:
            switch(eventType) {
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PreDoubleHandleReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PreDoubleHandleReservedSyncFail;
                case ReclaimerEventType::DoubleHandleStart:
                    return ReclaimerStateType::WorkingDoubleHandle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::Moving:
            switch(eventType) {
                case ReclaimerEventType::OnStopMove:
                    return ReclaimerStateType::Idle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::Maintenance:
            switch(eventType) {
                case ReclaimerEventType::MaintenanceComplete:
                    return ReclaimerStateType::Idle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WrappedUp:
            return ReclaimerStateType::Invalid;
        case ReclaimerStateType::WorkingReclaim:
            switch(eventType) {
                case ReclaimerEventType::Complete:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::WorkingReclaimFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::WorkingReclaimSyncFail;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimReserved:
            switch(eventType) {
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PostReclaimReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PostReclaimReservedSyncFail;
                case ReclaimerEventType::OperationComplete:
                    return ReclaimerStateType::Idle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::WorkingReclaim;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::WorkingReclaim;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreDoubleHandleReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PreDoubleHandleReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreDoubleHandleReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PreDoubleHandleReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingDoubleHandle:
            switch(eventType) {
                case ReclaimerEventType::DoubleHandleComplete:
                    return ReclaimerStateType::PostDoubleHandleReserved;
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::WorkingDoubleHandleFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::WorkingDoubleHandleSyncFail;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostDoubleHandleReserved:
            switch(eventType) {
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PostDoubleHandleReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PostDoubleHandleReservedSyncFail;
                case ReclaimerEventType::DoubleHandleOperationComplete:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingDoubleHandleFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::WorkingDoubleHandle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingDoubleHandleSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::WorkingDoubleHandle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostDoubleHandleReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PostDoubleHandleReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostDoubleHandleReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PostDoubleHandleReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        default:
            return ReclaimerStateType::Invalid;
    }
}