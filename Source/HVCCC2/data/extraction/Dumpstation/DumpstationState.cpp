/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "DumpstationState.h"

DumpstationStateType DumpstationState::determineNextType(DumpstationStateType stateType, DumpstationEventType eventType) {
    switch(stateType) {
        case DumpstationStateType::Idle:
            switch(eventType) {
                case DumpstationEventType::MaintenanceStart:
                    return DumpstationStateType::Maintenance;
                case DumpstationEventType::DumpOperationStart:
                    return DumpstationStateType::PreDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::Maintenance:
            switch(eventType) {
                case DumpstationEventType::MaintenanceComplete:
                    return DumpstationStateType::Idle;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PreDumpReserved:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::PreDumpReservedFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::PreDumpReservedSyncedFail;
                case DumpstationEventType::DumpStart:
                    return DumpstationStateType::Working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PreDumpReservedFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::PreDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PreDumpReservedSyncedFail:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::PreDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::Working:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::WorkingFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::WorkingSyncedFail;
                case DumpstationEventType::DumpComplete:
                    return DumpstationStateType::PostDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::WorkingFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::Working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::WorkingSyncedFail:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::Working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PostDumpReserved:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::PostReservedDumpFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::PostDumpReservedSyncedFail;
                case DumpstationEventType::DumpOperationComplete:
                    return DumpstationStateType::Idle;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PostReservedDumpFail:
            return DumpstationStateType::Invalid;
        case DumpstationStateType::PostDumpReservedSyncedFail:
            return DumpstationStateType::Invalid;
        case DumpstationStateType::PostDumpReservedFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::PostDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::PostDumpReservedSyncedFix:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::PostDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        default:
            return DumpstationStateType::Invalid;
    }
}