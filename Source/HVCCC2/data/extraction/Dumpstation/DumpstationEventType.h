/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#pragma once
#include <string>

enum class DumpstationEventType {
    DumpComplete,
    DumpOperationComplete,
    DumpOperationStart,
    DumpStart,
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