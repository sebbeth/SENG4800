#include "DumpStationEventType.h"

DumpStationEventType decodeDumpStationEventType(const std::string& enumeratorString) {
    if (enumeratorString == "DumpComp") {
        return DumpStationEventType::DumpComplete;
    } else if (enumeratorString == "DumpOpComp") {
        return DumpStationEventType::DumpOperationComplete;
    } else if (enumeratorString == "DumpOpStart") {
        return DumpStationEventType::DumpOperationStart;
    } else if (enumeratorString == "DumpStart") {
        return DumpStationEventType::DumpStart;
    } else if (enumeratorString == "Fail") {
        return DumpStationEventType::Fail;
    } else if (enumeratorString == "Fix") {
        return DumpStationEventType::Fix;
    } else if (enumeratorString == "MaintComp") {
        return DumpStationEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return DumpStationEventType::MaintenanceStart;
    } else if (enumeratorString == "SyncedFail") {
        return DumpStationEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return DumpStationEventType::SyncedFix;
    } else {
        return DumpStationEventType::Invalid;
    }
}