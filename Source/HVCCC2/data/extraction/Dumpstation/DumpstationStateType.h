/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
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