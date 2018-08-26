#pragma once
#include <string>

enum class ReclaimerEventType {
    Complete,
    DoubleHandleComplete,
    DoubleHandleOperationComplete,
    DoubleHandleOperationStart,
    DoubleHandleStart,
    Fail,
    Fix,
    MaintenanceComplete,
    MaintenanceStart,
    OnMove,
    OnStopMove,
    OperationComplete,
    OperationStart,
    Start,
    SyncedFail,
    SyncedFix,
    WrapUp,
    Invalid
};

ReclaimerEventType decodeReclaimerEventType(const std::string& enumeratorString);