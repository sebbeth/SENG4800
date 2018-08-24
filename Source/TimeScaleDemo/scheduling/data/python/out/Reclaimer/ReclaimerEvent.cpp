#include "ReclaimerEvent.h"

bool ReclaimerEvent::hasAmount() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationComplete:
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
        case ReclaimerEventType::WrapUp:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasMachineID() const {
    switch (type) {
        case ReclaimerEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool ReclaimerEvent::hasPosition() const {
    switch (type) {
        case ReclaimerEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool ReclaimerEvent::hasStockpileID() const {
    switch (type) {
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationComplete:
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
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
        case ReclaimerEventType::WrapUp:
        default:
            return false;
    }
}

bool ReclaimerEvent::hasTime() const {
    switch (type) {
        case ReclaimerEventType::Invalid:
            return false;
        default:
            return true;

    }
}