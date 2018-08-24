#include "ShipLoaderEventType.h"

ShipLoaderEventType decodeShipLoaderEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Fail") {
        return ShipLoaderEventType::Fail;
    } else if (enumeratorString == "Fix") {
        return ShipLoaderEventType::Fix;
    } else if (enumeratorString == "LoadComp") {
        return ShipLoaderEventType::LoadComplete;
    } else if (enumeratorString == "LoadOpComp") {
        return ShipLoaderEventType::LoadOperationComplete;
    } else if (enumeratorString == "LoadOpStart") {
        return ShipLoaderEventType::LoadOperationStart;
    } else if (enumeratorString == "LoadStart") {
        return ShipLoaderEventType::LoadStart;
    } else if (enumeratorString == "MaintComp") {
        return ShipLoaderEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return ShipLoaderEventType::MaintenanceStart;
    } else if (enumeratorString == "OnMove") {
        return ShipLoaderEventType::OnMove;
    } else if (enumeratorString == "OnStopMove") {
        return ShipLoaderEventType::OnStopMove;
    } else if (enumeratorString == "StartVesselLoad") {
        return ShipLoaderEventType::StartVesselLoad;
    } else if (enumeratorString == "SyncedFail") {
        return ShipLoaderEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return ShipLoaderEventType::SyncedFix;
    } else if (enumeratorString == "WrapUp") {
        return ShipLoaderEventType::WrapUp;
    } else {
        return ShipLoaderEventType::Invalid;
    }
}