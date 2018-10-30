/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
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