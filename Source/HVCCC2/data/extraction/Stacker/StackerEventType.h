/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
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
    Invalid
};

StackerEventType decodeStackerEventType(const std::string& enumeratorString);
std::string encodeStackerEventType(const StackerEventType& value);