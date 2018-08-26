#include "ShipLoaderState.h"

ShipLoaderStateType ShipLoaderState::determineNextType(ShipLoaderStateType stateType, ShipLoaderEventType eventType) {
    switch(eventType) {
        case ShipLoaderEventType::Fail:
            switch(stateType) {
                case ShipLoaderStateType::PostLoadReserved:
                    return ShipLoaderStateType::FailedPostLoadReserved;
                case ShipLoaderStateType::PreLoadReserved:
                    return ShipLoaderStateType::FailedPreLoadReserved;
                case ShipLoaderStateType::Working:
                    return ShipLoaderStateType::FailedWorking;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::Fix:
            switch(stateType) {
                case ShipLoaderStateType::FailedPostLoadReserved:
                    return ShipLoaderStateType::PostLoadReserved;
                case ShipLoaderStateType::FailedPreLoadReserved:
                    return ShipLoaderStateType::PreLoadReserved;
                case ShipLoaderStateType::FailedWorking:
                    return ShipLoaderStateType::Working;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::LoadComplete:
            switch(stateType) {
                case ShipLoaderStateType::Working:
                    return ShipLoaderStateType::PostLoadReserved;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::LoadOperationComplete:
            switch(stateType) {
                case ShipLoaderStateType::PostLoadReserved:
                    return ShipLoaderStateType::Idle;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::LoadOperationStart:
            switch(stateType) {
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::PreLoadReserved;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::LoadStart:
            switch(stateType) {
                case ShipLoaderStateType::PreLoadReserved:
                    return ShipLoaderStateType::Working;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::MaintenanceComplete:
            switch(stateType) {
                case ShipLoaderStateType::Maintenanceenance:
                    return ShipLoaderStateType::Idle;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::MaintenanceStart:
            switch(stateType) {
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::Maintenanceenance;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::OnMove:
            switch(stateType) {
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::Idle;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::OnStopMove:
            switch(stateType) {
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::Idle;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::StartVesselLoad:
            switch(stateType) {
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::Idle;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::SyncedFail:
            switch(stateType) {
                case ShipLoaderStateType::PostLoadReserved:
                    return ShipLoaderStateType::SyncedFailPostLoadReserved;
                case ShipLoaderStateType::PreLoadReserved:
                    return ShipLoaderStateType::SyncedFailPreLoadReserved;
                case ShipLoaderStateType::Working:
                    return ShipLoaderStateType::SyncedFailWorking;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::SyncedFix:
            switch(stateType) {
                case ShipLoaderStateType::SyncedFailPostLoadReserved:
                    return ShipLoaderStateType::PostLoadReserved;
                case ShipLoaderStateType::SyncedFailPreLoadReserved:
                    return ShipLoaderStateType::PreLoadReserved;
                case ShipLoaderStateType::SyncedFailWorking:
                    return ShipLoaderStateType::Working;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        case ShipLoaderEventType::WrapUp:
            switch(stateType) {
                case ShipLoaderStateType::FailedPostLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::FailedPreLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::FailedWorking:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::Idle:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::Maintenanceenance:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::PostLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::PreLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::SyncedFailPostLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::SyncedFailPreLoadReserved:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::SyncedFailWorking:
                    return ShipLoaderStateType::WrappedUp;
                case ShipLoaderStateType::Working:
                    return ShipLoaderStateType::WrappedUp;
                default:
                    return ShipLoaderStateType::Invalid;
            }
        default:
            return ShipLoaderStateType::Invalid;
    }
}