/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#pragma once
#include <string>

enum class StackerEventType {
    Complete,
    DoubleHandleComplete,
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
std::string encodeStackerEventType(const StackerEventType& value);