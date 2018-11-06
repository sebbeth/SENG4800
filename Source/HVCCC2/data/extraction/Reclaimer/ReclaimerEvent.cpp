/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ReclaimerEvent.h"

bool ReclaimerEvent::hasAmount() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::OperationComplete:
            return true;
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::ReclaimDoubleHandleComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
        case ReclaimerEventType::ReclaimDoubleHandleStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
        case ReclaimerEventType::WrapUp:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasPosition() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
        case ReclaimerEventType::WrapUp:
            return true;
        case ReclaimerEventType::ReclaimDoubleHandleComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
        case ReclaimerEventType::ReclaimDoubleHandleStart:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasStockpileID() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            return true;
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::ReclaimDoubleHandleComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
        case ReclaimerEventType::ReclaimDoubleHandleStart:
        case ReclaimerEventType::WrapUp:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasTime() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::OperationComplete:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
        case ReclaimerEventType::WrapUp:
            return true;
        case ReclaimerEventType::ReclaimDoubleHandleComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
        case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
        case ReclaimerEventType::ReclaimDoubleHandleStart:
        default:
            return false;
    }
}