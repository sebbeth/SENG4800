/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#include "DumpstationEvent.h"

bool DumpstationEvent::hasAmount() const {
    switch (type) {
        case DumpstationEventType::DumpComplete:
            return true;
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
        case DumpstationEventType::DumpStart:
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
        case DumpstationEventType::DumpStart:
            return true;
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
        case DumpstationEventType::DumpStart:
            return true;
        case DumpstationEventType::DumpComplete:
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
        case DumpstationEventType::DumpStart:
            return true;
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