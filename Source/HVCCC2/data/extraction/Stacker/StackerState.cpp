/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "StackerState.h"

StackerStateType StackerState::determineNextType(StackerStateType stateType, StackerEventType eventType) {
    switch(stateType) {
        case StackerStateType::Idle:
            switch(eventType) {
                case StackerEventType::OperationStart:
                    return StackerStateType::PreStackReserved;
                case StackerEventType::DoubleHandleOperationStart:
                    return StackerStateType::PreDoubleHandleReserved;
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
        case StackerStateType::PreDoubleHandleReserved:
            switch(eventType) {
                case StackerEventType::Fail:
                    return StackerStateType::PreDoubleHandleReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PreDoubleHandleReservedSyncFail;
                case StackerEventType::DoubleHandleStart:
                    return StackerStateType::WorkingDoubleHandle;
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
        case StackerStateType::PreDoubleHandleReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PreDoubleHandleReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PreDoubleHandleReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PreDoubleHandleReserved;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingDoubleHandle:
            switch(eventType) {
                case StackerEventType::DoubleHandleComplete:
                    return StackerStateType::PostDoubleHandleReserved;
                case StackerEventType::Fail:
                    return StackerStateType::WorkingDoubleHandleFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::WorkingDoubleHandleSyncFail;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostDoubleHandleReserved:
            switch(eventType) {
                case StackerEventType::Fail:
                    return StackerStateType::PostDoubleHandleReservedFail;
                case StackerEventType::SyncedFail:
                    return StackerStateType::PostDoubleHandleReservedSyncFail;
                case StackerEventType::DoubleHandleOperationComplete:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingDoubleHandleFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::WorkingDoubleHandle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::WorkingDoubleHandleSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::WorkingDoubleHandle;
                case StackerEventType::WrapUp:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostDoubleHandleReservedFail:
            switch(eventType) {
                case StackerEventType::Fix:
                    return StackerStateType::PostDoubleHandleReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerStateType::PostDoubleHandleReservedSyncFail:
            switch(eventType) {
                case StackerEventType::SyncedFix:
                    return StackerStateType::PostDoubleHandleReserved;
                default:
                    return StackerStateType::Invalid;
            }
        default:
            return StackerStateType::Invalid;
    }
}