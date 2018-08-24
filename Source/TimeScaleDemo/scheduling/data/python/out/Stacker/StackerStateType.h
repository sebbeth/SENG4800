#pragma once
#include <string>

enum class StackerStateType {
    FailedPostStackReserved,
    FailedPreStackReserved,
    FailedWorking,
    Idle,
    Maintenanceenance,
    PostStackReserved,
    PreStackReserved,
    SyncedFailPostStackReserved,
    SyncedFailPreStackReserved,
    SyncedFailWorking,
    Working,
    WrappedUp,
    Invalid
};