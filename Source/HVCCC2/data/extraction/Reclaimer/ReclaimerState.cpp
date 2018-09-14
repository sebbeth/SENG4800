/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
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
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::Moving:
            switch(eventType) {
                case ReclaimerEventType::OnStopMove:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::Maintenance:
            switch(eventType) {
                case ReclaimerEventType::MaintenanceComplete:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaim:
            switch(eventType) {
                case ReclaimerEventType::Complete:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerEventType::Fail:
                    return ReclaimerStateType::WorkingReclaimFail;
                case ReclaimerEventType::SyncedFail:
                    return ReclaimerStateType::WorkingReclaimSyncFail;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PreReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreReclaimReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PreReclaimReserved;
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
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::WorkingReclaim;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingReclaimSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::WorkingReclaim;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PostReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostReclaimReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PostReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreDoubleHandleReservedFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::PreDoubleHandleReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PreDoubleHandleReservedSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::PreDoubleHandleReserved;
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
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::PostDoubleHandleReserved:
            return ReclaimerStateType::Invalid;
        case ReclaimerStateType::WorkingDoubleHandleFail:
            switch(eventType) {
                case ReclaimerEventType::Fix:
                    return ReclaimerStateType::WorkingDoubleHandle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerStateType::WorkingDoubleHandleSyncFail:
            switch(eventType) {
                case ReclaimerEventType::SyncedFix:
                    return ReclaimerStateType::WorkingDoubleHandle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        default:
            return ReclaimerStateType::Invalid;
    }
}