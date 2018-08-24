#pragma once
#include <string>

enum class ShipLoaderStateType {
    FailedPostLoadReserved,
    FailedPreLoadReserved,
    FailedWorking,
    Idle,
    Maintenanceenance,
    PostLoadReserved,
    PreLoadReserved,
    SyncedFailPostLoadReserved,
    SyncedFailPreLoadReserved,
    SyncedFailWorking,
    Working,
    WrappedUp,
    Invalid
};