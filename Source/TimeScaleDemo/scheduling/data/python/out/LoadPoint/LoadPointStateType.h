#pragma once
#include <string>

enum class LoadPointStateType {
    Failed,
    Fixed,
    Idle,
    Loaded,
    Loading,
    Maintenanceenance,
    MaintenanceenanceComplete,
    Postload,
    Preload,
    Recharging,
    WrappedUp,
    Invalid
};