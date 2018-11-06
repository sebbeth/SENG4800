/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "DumpstationStateType.h"
        
DumpstationStateType decodeDumpstationStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return DumpstationStateType::Idle;
    } else if (enumeratorString == "Maintenance") {
        return DumpstationStateType::Maintenance;
    } else if (enumeratorString == "PostDumpReserved") {
        return DumpstationStateType::PostDumpReserved;
    } else if (enumeratorString == "PostDumpReservedFail") {
        return DumpstationStateType::PostDumpReservedFail;
    } else if (enumeratorString == "PostDumpReservedSyncedFail") {
        return DumpstationStateType::PostDumpReservedSyncedFail;
    } else if (enumeratorString == "PostDumpReservedSyncedFix") {
        return DumpstationStateType::PostDumpReservedSyncedFix;
    } else if (enumeratorString == "PostReservedDumpFail") {
        return DumpstationStateType::PostReservedDumpFail;
    } else if (enumeratorString == "PreDumpReserved") {
        return DumpstationStateType::PreDumpReserved;
    } else if (enumeratorString == "PreDumpReservedFail") {
        return DumpstationStateType::PreDumpReservedFail;
    } else if (enumeratorString == "PreDumpReservedSyncedFail") {
        return DumpstationStateType::PreDumpReservedSyncedFail;
    } else if (enumeratorString == "Working") {
        return DumpstationStateType::Working;
    } else if (enumeratorString == "WorkingFail") {
        return DumpstationStateType::WorkingFail;
    } else if (enumeratorString == "WorkingSyncedFail") {
        return DumpstationStateType::WorkingSyncedFail;
    } else {
        return DumpstationStateType::Invalid;
    }
}
std::string encodeDumpstationStateType(const DumpstationStateType& value) {
    switch(value) {
        case DumpstationStateType::Idle:
            return "Idle";
            break;

        case DumpstationStateType::Maintenance:
            return "Maintenance";
            break;

        case DumpstationStateType::PreDumpReserved:
            return "PreDumpReserved";
            break;

        case DumpstationStateType::PreDumpReservedFail:
            return "PreDumpReservedFail";
            break;

        case DumpstationStateType::PreDumpReservedSyncedFail:
            return "PreDumpReservedSyncedFail";
            break;

        case DumpstationStateType::Working:
            return "Working";
            break;

        case DumpstationStateType::WorkingFail:
            return "WorkingFail";
            break;

        case DumpstationStateType::WorkingSyncedFail:
            return "WorkingSyncedFail";
            break;

        case DumpstationStateType::PostDumpReserved:
            return "PostDumpReserved";
            break;

        case DumpstationStateType::PostReservedDumpFail:
            return "PostReservedDumpFail";
            break;

        case DumpstationStateType::PostDumpReservedSyncedFail:
            return "PostDumpReservedSyncedFail";
            break;

        case DumpstationStateType::PostDumpReservedFail:
            return "PostDumpReservedFail";
            break;

        case DumpstationStateType::PostDumpReservedSyncedFix:
            return "PostDumpReservedSyncedFix";
            break;

        default:
            return "Invalid";
    }
}