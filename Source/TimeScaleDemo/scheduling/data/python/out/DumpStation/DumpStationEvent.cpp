#include "DumpStationEvent.h"

bool DumpStationEvent::hasAmountDumped() const {
    switch (type) {
        case DumpStationEventType::DumpComplete:
            return true;
        case DumpStationEventType::DumpOperationComplete:
        case DumpStationEventType::DumpOperationStart:
        case DumpStationEventType::DumpStart:
        case DumpStationEventType::Fail:
        case DumpStationEventType::Fix:
        case DumpStationEventType::MaintenanceComplete:
        case DumpStationEventType::MaintenanceStart:
        case DumpStationEventType::SyncedFail:
        case DumpStationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpStationEvent::hasCycleID() const {
    switch (type) {
        case DumpStationEventType::DumpComplete:
        case DumpStationEventType::DumpOperationComplete:
        case DumpStationEventType::DumpOperationStart:
        case DumpStationEventType::DumpStart:
            return true;
        case DumpStationEventType::Fail:
        case DumpStationEventType::Fix:
        case DumpStationEventType::MaintenanceComplete:
        case DumpStationEventType::MaintenanceStart:
        case DumpStationEventType::SyncedFail:
        case DumpStationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpStationEvent::hasDumpStationID() const {
    switch (type) {
        case DumpStationEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool DumpStationEvent::hasStockpileID() const {
    switch (type) {
        case DumpStationEventType::DumpOperationComplete:
        case DumpStationEventType::DumpOperationStart:
        case DumpStationEventType::DumpStart:
            return true;
        case DumpStationEventType::DumpComplete:
        case DumpStationEventType::Fail:
        case DumpStationEventType::Fix:
        case DumpStationEventType::MaintenanceComplete:
        case DumpStationEventType::MaintenanceStart:
        case DumpStationEventType::SyncedFail:
        case DumpStationEventType::SyncedFix:
        default:
            return false;
    }
}

bool DumpStationEvent::hasTime() const {
    switch (type) {
        case DumpStationEventType::Invalid:
            return false;
        default:
            return true;

    }
}