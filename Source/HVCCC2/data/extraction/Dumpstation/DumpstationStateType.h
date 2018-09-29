/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#pragma once
#include <string>

enum class DumpstationStateType {
    idle,
    maintenance,
    postDumpReserved,
    postDumpReservedFail,
    postDumpReservedSyncedFail,
    postDumpReservedSyncedFix,
    postReservedDumpFail,
    preDumpReserved,
    preDumpReservedFail,
    preDumpReservedSyncedFail,
    working,
    workingFail,
    workingSyncedFail,
    Invalid
};