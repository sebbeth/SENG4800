/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "StackerEvent.h"

bool StackerEvent::hasAmount() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationComplete:
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
        case StackerEventType::WrapUp:
        default:
            return false;
    }
}

bool StackerEvent::hasPosition() const {
    switch (type) {
        case StackerEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool StackerEvent::hasStockpileID() const {
    switch (type) {
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationComplete:
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OperationComplete:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
            return true;
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::WrapUp:
        default:
            return false;
    }
}

bool StackerEvent::hasTime() const {
    switch (type) {
        case StackerEventType::Invalid:
            return false;
        default:
            return true;

    }
}