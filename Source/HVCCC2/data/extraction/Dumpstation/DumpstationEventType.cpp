/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "DumpstationEventType.h"
        
DumpstationEventType decodeDumpstationEventType(const std::string& enumeratorString) {
    if (enumeratorString == "DumpComp") {
        return DumpstationEventType::DumpComplete;
    } else if (enumeratorString == "DumpOpComp") {
        return DumpstationEventType::DumpOperationComplete;
    } else if (enumeratorString == "DumpOpStart") {
        return DumpstationEventType::DumpOperationStart;
    } else if (enumeratorString == "DumpStart") {
        return DumpstationEventType::DumpStart;
    } else if (enumeratorString == "Fail") {
        return DumpstationEventType::Fail;
    } else if (enumeratorString == "Fix") {
        return DumpstationEventType::Fix;
    } else if (enumeratorString == "MaintComp") {
        return DumpstationEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return DumpstationEventType::MaintenanceStart;
    } else if (enumeratorString == "SyncedFail") {
        return DumpstationEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return DumpstationEventType::SyncedFix;
    } else {
        return DumpstationEventType::Invalid;
    }
}
std::string encodeDumpstationEventType(const DumpstationEventType& value) {
    switch(value) {
        case DumpstationEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case DumpstationEventType::DumpOperationStart:
            return "DumpOpStart";
            break;

        case DumpstationEventType::MaintenanceComplete:
            return "MaintComp";
            break;

        case DumpstationEventType::Fail:
            return "Fail";
            break;

        case DumpstationEventType::SyncedFail:
            return "SyncedFail";
            break;

        case DumpstationEventType::DumpStart:
            return "DumpStart";
            break;

        case DumpstationEventType::Fix:
            return "Fix";
            break;

        case DumpstationEventType::SyncedFix:
            return "SyncedFix";
            break;

        case DumpstationEventType::DumpComplete:
            return "DumpComp";
            break;

        case DumpstationEventType::DumpOperationComplete:
            return "DumpOpComp";
            break;

        default:
            return "Invalid";
    }
}