/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 14:36:15.744470
 **/
#include "ReclaimerEvent.h"

bool ReclaimerEvent::hasAmount() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::OperationComplete:
            return true;
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasPosition() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            return true;
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasStockpileID() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            return true;
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasTime() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            return true;
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        default:
            return false;
    }
}