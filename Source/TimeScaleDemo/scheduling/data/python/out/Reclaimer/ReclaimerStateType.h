#pragma once
#include <string>

enum class ReclaimerStateType {
    FailedPostReclaimReserved,
    FailedPreReclaimReserved,
    FailedWorking,
    Idle,
    Maintenanceenance,
    PostReclaimReserved,
    PostStackReserved,
    PreReclaimReserved,
    SyncedFailPostReclaimReserved,
    SyncedFailPreReclaimReserved,
    SyncedFailWorking,
    Working,
    WrappedUp,
    Invalid
};