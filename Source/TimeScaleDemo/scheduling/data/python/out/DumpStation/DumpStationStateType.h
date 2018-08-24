#pragma once
#include <string>

enum class DumpStationStateType {
    FailedPostDumpReserved,
    FailedPreDumpReserved,
    FailedWorking,
    Idle,
    Maintenanceenance,
    PostDumpReserved,
    PreDumpReserved,
    SyncedFailPostDumpReserved,
    SyncedFailPreDumpReserved,
    SyncedFailWorking,
    Working,
    Invalid
};