/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
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