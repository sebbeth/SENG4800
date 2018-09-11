/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "DumpstationEvent.h"

bool DumpstationEvent::hasAmount() const {
    switch (type) {
        case DumpstationEventType::DumpComplete:
            return true;
        case DumpstationEventType::DumpFail:
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
        case DumpstationEventType::Fail:
        case DumpstationEventType::Fix:
        case DumpstationEventType::MaintenanceComplete:
        case DumpstationEventType::MaintenanceStart:
        case DumpstationEventType::SyncedFail:
        case DumpstationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpstationEvent::hasCycleID() const {
    switch (type) {
        case DumpstationEventType::DumpComplete:
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
            return true;
        case DumpstationEventType::DumpFail:
        case DumpstationEventType::Fail:
        case DumpstationEventType::Fix:
        case DumpstationEventType::MaintenanceComplete:
        case DumpstationEventType::MaintenanceStart:
        case DumpstationEventType::SyncedFail:
        case DumpstationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpstationEvent::hasStockpileID() const {
    switch (type) {
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
            return true;
        case DumpstationEventType::DumpComplete:
        case DumpstationEventType::DumpFail:
        case DumpstationEventType::Fail:
        case DumpstationEventType::Fix:
        case DumpstationEventType::MaintenanceComplete:
        case DumpstationEventType::MaintenanceStart:
        case DumpstationEventType::SyncedFail:
        case DumpstationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpstationEvent::hasTime() const {
    switch (type) {
        case DumpstationEventType::DumpComplete:
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
            return true;
        case DumpstationEventType::DumpFail:
        case DumpstationEventType::Fail:
        case DumpstationEventType::Fix:
        case DumpstationEventType::MaintenanceComplete:
        case DumpstationEventType::MaintenanceStart:
        case DumpstationEventType::SyncedFail:
        case DumpstationEventType::SyncedFix:
        default:
            return false;
    }
}