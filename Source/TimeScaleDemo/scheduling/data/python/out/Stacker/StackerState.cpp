#include "StackerState.h"

StackerStateType StackerState::determineNextType(StackerStateType stateType, StackerEventType eventType) {
    switch(eventType) {
        case StackerEventType::Complete:
            switch(stateType) {
                case StackerStateType::Working:
                    return StackerStateType::PostStackReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::DoubleHandleComplete:
            switch(stateType) {
                case StackerStateType::Working:
                    return StackerStateType::PostStackReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::DoubleHandleOperationComplete:
            switch(stateType) {
                case StackerStateType::PostStackReserved:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::DoubleHandleOperationStart:
            switch(stateType) {
                case StackerStateType::Idle:
                    return StackerStateType::PreStackReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::DoubleHandleStart:
            switch(stateType) {
                case StackerStateType::PreStackReserved:
                    return StackerStateType::Working;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::Fail:
            switch(stateType) {
                case StackerStateType::PostStackReserved:
                    return StackerStateType::FailedPostStackReserved;
                case StackerStateType::PreStackReserved:
                    return StackerStateType::FailedPreStackReserved;
                case StackerStateType::Working:
                    return StackerStateType::FailedWorking;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::Fix:
            switch(stateType) {
                case StackerStateType::FailedPostStackReserved:
                    return StackerStateType::PostStackReserved;
                case StackerStateType::FailedPreStackReserved:
                    return StackerStateType::PreStackReserved;
                case StackerStateType::FailedWorking:
                    return StackerStateType::Working;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::MaintenanceComplete:
            switch(stateType) {
                case StackerStateType::Maintenanceenance:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::MaintenanceStart:
            switch(stateType) {
                case StackerStateType::Idle:
                    return StackerStateType::Maintenanceenance;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::OnMove:
            switch(stateType) {
                case StackerStateType::Idle:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::OnStopMove:
            switch(stateType) {
                case StackerStateType::Idle:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::OperationComplete:
            switch(stateType) {
                case StackerStateType::PostStackReserved:
                    return StackerStateType::Idle;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::OperationStart:
            switch(stateType) {
                case StackerStateType::Idle:
                    return StackerStateType::PreStackReserved;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::Start:
            switch(stateType) {
                case StackerStateType::PreStackReserved:
                    return StackerStateType::Working;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::SyncedFail:
            switch(stateType) {
                case StackerStateType::PostStackReserved:
                    return StackerStateType::SyncedFailPostStackReserved;
                case StackerStateType::PreStackReserved:
                    return StackerStateType::SyncedFailPreStackReserved;
                case StackerStateType::Working:
                    return StackerStateType::SyncedFailWorking;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::SyncedFix:
            switch(stateType) {
                case StackerStateType::SyncedFailPostStackReserved:
                    return StackerStateType::PostStackReserved;
                case StackerStateType::SyncedFailPreStackReserved:
                    return StackerStateType::PreStackReserved;
                case StackerStateType::SyncedFailWorking:
                    return StackerStateType::Working;
                default:
                    return StackerStateType::Invalid;
            }
        case StackerEventType::WrapUp:
            switch(stateType) {
                case StackerStateType::FailedPostStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::FailedPreStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::FailedWorking:
                    return StackerStateType::WrappedUp;
                case StackerStateType::Idle:
                    return StackerStateType::WrappedUp;
                case StackerStateType::Maintenanceenance:
                    return StackerStateType::WrappedUp;
                case StackerStateType::PostStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::PreStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::SyncedFailPostStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::SyncedFailPreStackReserved:
                    return StackerStateType::WrappedUp;
                case StackerStateType::SyncedFailWorking:
                    return StackerStateType::WrappedUp;
                case StackerStateType::Working:
                    return StackerStateType::WrappedUp;
                default:
                    return StackerStateType::Invalid;
            }
        default:
            return StackerStateType::Invalid;
    }
}