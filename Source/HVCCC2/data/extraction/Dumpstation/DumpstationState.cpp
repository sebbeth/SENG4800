/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#include "DumpstationState.h"

DumpstationStateType DumpstationState::determineNextType(DumpstationStateType stateType, DumpstationEventType eventType) {
    switch(stateType) {
        case DumpstationStateType::idle:
            switch(eventType) {
                case DumpstationEventType::MaintenanceStart:
                    return DumpstationStateType::maintenance;
                case DumpstationEventType::DumpOperationStart:
                    return DumpstationStateType::preDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::maintenance:
            switch(eventType) {
                case DumpstationEventType::MaintenanceComplete:
                    return DumpstationStateType::idle;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::preDumpReserved:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::preDumpReservedFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::preDumpReservedSyncedFail;
                case DumpstationEventType::DumpStart:
                    return DumpstationStateType::working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::preDumpReservedFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::preDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::preDumpReservedSyncedFail:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::preDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::working:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::workingFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::workingSyncedFail;
                case DumpstationEventType::DumpComplete:
                    return DumpstationStateType::postDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::workingFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::workingSyncedFail:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::working;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::postDumpReserved:
            switch(eventType) {
                case DumpstationEventType::Fail:
                    return DumpstationStateType::postReservedDumpFail;
                case DumpstationEventType::SyncedFail:
                    return DumpstationStateType::postDumpReservedSyncedFail;
                case DumpstationEventType::DumpOperationComplete:
                    return DumpstationStateType::idle;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::postReservedDumpFail:
            return DumpstationStateType::Invalid;
        case DumpstationStateType::postDumpReservedSyncedFail:
            return DumpstationStateType::Invalid;
        case DumpstationStateType::postDumpReservedFail:
            switch(eventType) {
                case DumpstationEventType::Fix:
                    return DumpstationStateType::postDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        case DumpstationStateType::postDumpReservedSyncedFix:
            switch(eventType) {
                case DumpstationEventType::SyncedFix:
                    return DumpstationStateType::postDumpReserved;
                default:
                    return DumpstationStateType::Invalid;
            }
        default:
            return DumpstationStateType::Invalid;
    }
}