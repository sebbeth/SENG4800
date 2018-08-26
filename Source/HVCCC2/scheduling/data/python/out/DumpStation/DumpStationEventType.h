#pragma once
#include <string>

enum class DumpStationEventType {
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

DumpStationEventType decodeDumpStationEventType(const std::string& enumeratorString);