#include "DumpStationState.h"

DumpStationStateType DumpStationState::determineNextType(DumpStationStateType stateType, DumpStationEventType eventType) {
    switch(eventType) {
        case DumpStationEventType::DumpComplete:
            switch(stateType) {
                case DumpStationStateType::Working:
                    return DumpStationStateType::PostDumpReserved;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::DumpOperationComplete:
            switch(stateType) {
                case DumpStationStateType::PostDumpReserved:
                    return DumpStationStateType::Idle;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::DumpOperationStart:
            switch(stateType) {
                case DumpStationStateType::Idle:
                    return DumpStationStateType::PreDumpReserved;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::DumpStart:
            switch(stateType) {
                case DumpStationStateType::PreDumpReserved:
                    return DumpStationStateType::Working;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::Fail:
            switch(stateType) {
                case DumpStationStateType::PostDumpReserved:
                    return DumpStationStateType::FailedPostDumpReserved;
                case DumpStationStateType::PreDumpReserved:
                    return DumpStationStateType::FailedPreDumpReserved;
                case DumpStationStateType::Working:
                    return DumpStationStateType::FailedWorking;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::Fix:
            switch(stateType) {
                case DumpStationStateType::FailedPostDumpReserved:
                    return DumpStationStateType::PostDumpReserved;
                case DumpStationStateType::FailedPreDumpReserved:
                    return DumpStationStateType::PreDumpReserved;
                case DumpStationStateType::FailedWorking:
                    return DumpStationStateType::Working;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::MaintenanceComplete:
            switch(stateType) {
                case DumpStationStateType::Maintenanceenance:
                    return DumpStationStateType::Idle;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::MaintenanceStart:
            switch(stateType) {
                case DumpStationStateType::Idle:
                    return DumpStationStateType::Maintenanceenance;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::SyncedFail:
            switch(stateType) {
                case DumpStationStateType::PostDumpReserved:
                    return DumpStationStateType::SyncedFailPostDumpReserved;
                case DumpStationStateType::PreDumpReserved:
                    return DumpStationStateType::SyncedFailPreDumpReserved;
                case DumpStationStateType::Working:
                    return DumpStationStateType::SyncedFailWorking;
                default:
                    return DumpStationStateType::Invalid;
            }
        case DumpStationEventType::SyncedFix:
            switch(stateType) {
                case DumpStationStateType::SyncedFailPostDumpReserved:
                    return DumpStationStateType::PostDumpReserved;
                case DumpStationStateType::SyncedFailPreDumpReserved:
                    return DumpStationStateType::PreDumpReserved;
                case DumpStationStateType::SyncedFailWorking:
                    return DumpStationStateType::Working;
                default:
                    return DumpStationStateType::Invalid;
            }
        default:
            return DumpStationStateType::Invalid;
    }
}