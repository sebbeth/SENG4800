#pragma once
#include <string>

enum class StackerEventType {
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

StackerEventType decodeStackerEventType(const std::string& enumeratorString);