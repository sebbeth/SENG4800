/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:05:50.446537
 **/
#pragma once
#include <string>

enum class ReclaimerEventType {
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

ReclaimerEventType decodeReclaimerEventType(const std::string& enumeratorString);
std::string encodeReclaimerEventType(const ReclaimerEventType& value);