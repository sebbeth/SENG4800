/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
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