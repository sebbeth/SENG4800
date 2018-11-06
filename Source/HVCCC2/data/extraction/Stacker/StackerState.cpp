/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StackerState.h"

StackerStateType StackerState::determineNextType(StackerStateType stateType, StackerEventType eventType) {
    switch(stateType) {
        case StackerStateType::Idle:
            switch(eventType) {
                case StackerEventType::OperationStart:
                    return StackerStateType::PreStackReserved;
                case StackerEventType::StackDoubleHandleOperationStart:
                    return StackerStateType::PreStackDoubleHandleReserved;
                case StackerEventType::OnMove:
                    return StackerStateType::Moving;
                case StackerEventType::MaintenanceStart:
                    return StackerStateType::Maintenance;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackReserved:
            switch(eventType) {
                case StackerEventType::Start:
                    return StackerStateType::WorkingStack;
                case StackerEventType::Fail:
                    return StackerStateType::PreStackReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PreStackReservedSyncFail;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackDoubleHandleReserved:
            switch(eventType) {
                case StackerEventType::Fail:
                    return StackerStateType::PreStackDoubleHandleReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PreStackDoubleHandleReservedSyncFail;
                case StackerEventType::StackDoubleHandleStart:
                    return StackerStateType::WorkingStackDoubleHandle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::Moving:
            switch(eventType) {
                case StackerEventType::OnStopMove:
                    return StackerStateType::Idle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::Maintenance:
            switch(eventType) {
                case StackerEventType::MaintenanceComplete:
                    return StackerStateType::Idle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WrappedUp:
            return StackerStateType::Invalid;
        case StackerStateType::WorkingStack:
            switch(eventType) {
                case StackerEventType::Complete:
                    return StackerStateType::PostStackReserved;
                case StackerEventType::Fail:
                    return StackerStateType::WorkingStackFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::WorkingStackSyncFail;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PreStackReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PreStackReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackReserved:
            switch(eventType) {
                case StackerEventType::Fail:
                    return StackerStateType::PostStackReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PostStackReservedSyncFail;
                case StackerEventType::OperationComplete:
                    return StackerStateType::Idle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingStackFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::WorkingStack;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingStackSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::WorkingStack;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PostStackReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PostStackReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackDoubleHandleReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PreStackDoubleHandleReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreStackDoubleHandleReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PreStackDoubleHandleReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingStackDoubleHandle:
            switch(eventType) {
                case StackerEventType::StackDoubleHandleComplete:
                    return StackerStateType::PostStackDoubleHandleReserved;
                case StackerEventType::Fail:
                    return StackerStateType::WorkingStackDoubleHandleFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::WorkingStackDoubleHandleSyncFail;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackDoubleHandleReserved:
            switch(eventType) {
                case StackerEventType::Fail:
                    return StackerStateType::PostStackDoubleHandleReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PostStackDoubleHandleReservedSyncFail;
                case StackerEventType::StackDoubleHandleOperationComplete:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingStackDoubleHandleFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::WorkingStackDoubleHandle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingStackDoubleHandleSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::WorkingStackDoubleHandle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackDoubleHandleReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PostStackDoubleHandleReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostStackDoubleHandleReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PostStackDoubleHandleReserved;
                default:
                    return StackerStateType::Invalid;
            }
        default:
            return StackerStateType::Invalid;
    }
}