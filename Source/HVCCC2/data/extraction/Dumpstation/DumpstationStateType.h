/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
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