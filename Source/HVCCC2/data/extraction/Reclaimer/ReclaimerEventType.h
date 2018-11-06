/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class ReclaimerEventType {
    Complete,
    Fail,
    Fix,
    MaintenanceComplete,
    MaintenanceStart,
    OnMove,
    OnStopMove,
    OperationComplete,
    OperationStart,
    ReclaimDoubleHandleComplete,
    ReclaimDoubleHandleOperationComplete,
    ReclaimDoubleHandleOperationStart,
    ReclaimDoubleHandleStart,
    Start,
    SyncedFail,
    SyncedFix,
    WrapUp,
    Invalid
};

ReclaimerEventType decodeReclaimerEventType(const std::string& enumeratorString);
std::string encodeReclaimerEventType(const ReclaimerEventType& value);