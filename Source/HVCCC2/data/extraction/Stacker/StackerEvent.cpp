/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StackerEvent.h"

bool StackerEvent::hasAmount() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::OperationComplete:
            return true;
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationStart:
        case StackerEventType::StackDoubleHandleComplete:
        case StackerEventType::StackDoubleHandleOperationComplete:
        case StackerEventType::StackDoubleHandleOperationStart:
        case StackerEventType::StackDoubleHandleStart:
        case StackerEventType::Start:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        case StackerEventType::WrapUp:
        default:
            return false;
    }
}

bool StackerEvent::hasPosition() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
        case StackerEventType::WrapUp:
            return true;
        case StackerEventType::StackDoubleHandleComplete:
        case StackerEventType::StackDoubleHandleOperationComplete:
        case StackerEventType::StackDoubleHandleOperationStart:
        case StackerEventType::StackDoubleHandleStart:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}

bool StackerEvent::hasStockpileID() const {
    switch (type) {
        case StackerEventType::Complete:
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
        case StackerEventType::StackDoubleHandleComplete:
        case StackerEventType::StackDoubleHandleOperationComplete:
        case StackerEventType::StackDoubleHandleOperationStart:
        case StackerEventType::StackDoubleHandleStart:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        case StackerEventType::WrapUp:
        default:
            return false;
    }
}

bool StackerEvent::hasTime() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
        case StackerEventType::WrapUp:
            return true;
        case StackerEventType::StackDoubleHandleComplete:
        case StackerEventType::StackDoubleHandleOperationComplete:
        case StackerEventType::StackDoubleHandleOperationStart:
        case StackerEventType::StackDoubleHandleStart:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
        default:
            return false;
    }
}