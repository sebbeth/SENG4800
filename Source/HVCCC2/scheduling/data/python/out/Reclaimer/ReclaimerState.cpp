#include "ReclaimerState.h"

ReclaimerStateType ReclaimerState::determineNextType(ReclaimerStateType stateType, ReclaimerEventType eventType) {
    switch(eventType) {
        case ReclaimerEventType::Complete:
            switch(stateType) {
                case ReclaimerStateType::Working:
                    return ReclaimerStateType::PostReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::DoubleHandleComplete:
            switch(stateType) {
                case ReclaimerStateType::Working:
                    return ReclaimerStateType::PostStackReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::DoubleHandleOperationComplete:
            switch(stateType) {
                case ReclaimerStateType::PostStackReserved:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::DoubleHandleOperationStart:
            switch(stateType) {
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::PreReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::DoubleHandleStart:
            switch(stateType) {
                case ReclaimerStateType::PreReclaimReserved:
                    return ReclaimerStateType::Working;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::Fail:
            switch(stateType) {
                case ReclaimerStateType::PostReclaimReserved:
                    return ReclaimerStateType::FailedPostReclaimReserved;
                case ReclaimerStateType::PreReclaimReserved:
                    return ReclaimerStateType::FailedPreReclaimReserved;
                case ReclaimerStateType::Working:
                    return ReclaimerStateType::FailedWorking;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::Fix:
            switch(stateType) {
                case ReclaimerStateType::FailedPostReclaimReserved:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerStateType::FailedPreReclaimReserved:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerStateType::FailedWorking:
                    return ReclaimerStateType::Working;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::MaintenanceComplete:
            switch(stateType) {
                case ReclaimerStateType::Maintenanceenance:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::MaintenanceStart:
            switch(stateType) {
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::Maintenanceenance;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::OnMove:
            switch(stateType) {
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::OnStopMove:
            switch(stateType) {
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::OperationComplete:
            switch(stateType) {
                case ReclaimerStateType::PostReclaimReserved:
                    return ReclaimerStateType::Idle;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::OperationStart:
            switch(stateType) {
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::PreReclaimReserved;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::Start:
            switch(stateType) {
                case ReclaimerStateType::PreReclaimReserved:
                    return ReclaimerStateType::Working;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::SyncedFail:
            switch(stateType) {
                case ReclaimerStateType::PostReclaimReserved:
                    return ReclaimerStateType::SyncedFailPostReclaimReserved;
                case ReclaimerStateType::PreReclaimReserved:
                    return ReclaimerStateType::SyncedFailPreReclaimReserved;
                case ReclaimerStateType::Working:
                    return ReclaimerStateType::SyncedFailWorking;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::SyncedFix:
            switch(stateType) {
                case ReclaimerStateType::SyncedFailPostReclaimReserved:
                    return ReclaimerStateType::PostReclaimReserved;
                case ReclaimerStateType::SyncedFailPreReclaimReserved:
                    return ReclaimerStateType::PreReclaimReserved;
                case ReclaimerStateType::SyncedFailWorking:
                    return ReclaimerStateType::Working;
                default:
                    return ReclaimerStateType::Invalid;
            }
        case ReclaimerEventType::WrapUp:
            switch(stateType) {
                case ReclaimerStateType::FailedPostReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::FailedPreReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::FailedWorking:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::Idle:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::Maintenanceenance:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::PostReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::PostStackReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::PreReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::SyncedFailPostReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::SyncedFailPreReclaimReserved:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::SyncedFailWorking:
                    return ReclaimerStateType::WrappedUp;
                case ReclaimerStateType::Working:
                    return ReclaimerStateType::WrappedUp;
                default:
                    return ReclaimerStateType::Invalid;
            }
        default:
            return ReclaimerStateType::Invalid;
    }
}