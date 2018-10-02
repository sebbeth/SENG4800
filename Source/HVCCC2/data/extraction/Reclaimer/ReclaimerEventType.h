/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-27 20:19:00.043450
 **/
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
std::string encodeReclaimerEventType(const ReclaimerEventType& value);