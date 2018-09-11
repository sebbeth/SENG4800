/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "StackerEvent.h"

bool StackerEvent::hasAmount() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::OperationComplete:
            return true;
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}

bool StackerEvent::hasPosition() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
            return true;
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}

bool StackerEvent::hasStockpileID() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
            return true;
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}

bool StackerEvent::hasTime() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
            return true;
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}