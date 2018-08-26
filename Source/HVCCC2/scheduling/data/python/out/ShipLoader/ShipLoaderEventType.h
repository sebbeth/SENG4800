#pragma once
#include <string>

enum class ShipLoaderEventType {
    Fail,
    Fix,
    LoadComplete,
    LoadOperationComplete,
    LoadOperationStart,
    LoadStart,
    MaintenanceComplete,
    MaintenanceStart,
    OnMove,
    OnStopMove,
    StartVesselLoad,
    SyncedFail,
    SyncedFix,
    WrapUp,
    Invalid
};

ShipLoaderEventType decodeShipLoaderEventType(const std::string& enumeratorString);