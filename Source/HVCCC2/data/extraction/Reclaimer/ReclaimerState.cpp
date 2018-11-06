/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ReclaimerState.h"

ReclaimerStateType ReclaimerState::determineNextType(ReclaimerStateType stateType, ReclaimerEventType eventType) {
    switch(stateType) {
        case ReclaimerStateType::Idle:
            switch(eventType) {
                case ReclaimerEventType::OperationStart:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
                    return ReclaimerStateType::PreReclaimDoubleHandleReserved;
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
        case ReclaimerStateType::PreReclaimDoubleHandleReserved:
            switch(eventType) {
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PreReclaimDoubleHandleReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail;
                case ReclaimerEventType::ReclaimDoubleHandleStart:
                    return ReclaimerStateType::WorkingReclaimDoubleHandle;
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
        case ReclaimerStateType::PreReclaimDoubleHandleReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PreReclaimDoubleHandleReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimDoubleHandleReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PreReclaimDoubleHandleReserved;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimDoubleHandle:
            switch(eventType) {
                case ReclaimerEventType::ReclaimDoubleHandleComplete:
                    return ReclaimerStateType::PostReclaimDoubleHandleReserved;
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::WorkingReclaimDoubleHandleFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::WorkingReclaimDoubleHandleSyncFail;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimDoubleHandleReserved:
            switch(eventType) {
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::PostReclaimDoubleHandleReservedFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail;
                case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimDoubleHandleFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::WorkingReclaimDoubleHandle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimDoubleHandleSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::WorkingReclaimDoubleHandle;
                case ReclaimerEventType::WrapUp:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimDoubleHandleReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PostReclaimDoubleHandleReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimDoubleHandleReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PostReclaimDoubleHandleReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        default:
            return ReclaimerStateType::Invalid;
    }
}