/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class DumpstationStateType {
    Idle,
    Maintenance,
    PostDumpReserved,
    PostDumpReservedFail,
    PostDumpReservedSyncedFail,
    PostDumpReservedSyncedFix,
    PostReservedDumpFail,
    PreDumpReserved,
    PreDumpReservedFail,
    PreDumpReservedSyncedFail,
    Working,
    WorkingFail,
    WorkingSyncedFail,
    Invalid
};

DumpstationStateType decodeDumpstationStateType(const std::string& enumeratorString);
std::string encodeDumpstationStateType(const DumpstationStateType& value);