/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#pragma once
#include <string>

enum class DumpstationEventType {
    DumpComplete,
    DumpFail,
    DumpOperationComplete,
    DumpOperationStart,
    Fail,
    Fix,
    MaintenanceComplete,
    MaintenanceStart,
    SyncedFail,
    SyncedFix,
    Invalid
};

DumpstationEventType decodeDumpstationEventType(const std::string& enumeratorString);
std::string encodeDumpstationEventType(const DumpstationEventType& value);