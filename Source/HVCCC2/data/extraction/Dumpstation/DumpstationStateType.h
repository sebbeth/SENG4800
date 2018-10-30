/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
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