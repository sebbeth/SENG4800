#include "ShipLoaderEvent.h"

bool ShipLoaderEvent::hasAmount() const {
    switch (type) {
        case ShipLoaderEventType::LoadComplete:
        case ShipLoaderEventType::LoadOperationComplete:
            return true;
        case ShipLoaderEventType::Fail:
        case ShipLoaderEventType::Fix:
        case ShipLoaderEventType::LoadOperationStart:
        case ShipLoaderEventType::LoadStart:
        case ShipLoaderEventType::MaintenanceComplete:
        case ShipLoaderEventType::MaintenanceStart:
        case ShipLoaderEventType::OnMove:
        case ShipLoaderEventType::OnStopMove:
        case ShipLoaderEventType::StartVesselLoad:
        case ShipLoaderEventType::SyncedFail:
        case ShipLoaderEventType::SyncedFix:
        case ShipLoaderEventType::WrapUp:
        default:
            return false;
    }
}

bool ShipLoaderEvent::hasPosition() const {
    switch (type) {
        case ShipLoaderEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool ShipLoaderEvent::hasShipLoaderID() const {
    switch (type) {
        case ShipLoaderEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool ShipLoaderEvent::hasStockpileID() const {
    switch (type) {
        case ShipLoaderEventType::Fail:
        case ShipLoaderEventType::Fix:
        case ShipLoaderEventType::LoadComplete:
        case ShipLoaderEventType::LoadOperationComplete:
        case ShipLoaderEventType::LoadOperationStart:
        case ShipLoaderEventType::LoadStart:
        case ShipLoaderEventType::SyncedFail:
        case ShipLoaderEventType::SyncedFix:
            return true;
        case ShipLoaderEventType::MaintenanceComplete:
        case ShipLoaderEventType::MaintenanceStart:
        case ShipLoaderEventType::OnMove:
        case ShipLoaderEventType::OnStopMove:
        case ShipLoaderEventType::StartVesselLoad:
        case ShipLoaderEventType::WrapUp:
        default:
            return false;
    }
}

bool ShipLoaderEvent::hasTime() const {
    switch (type) {
        case ShipLoaderEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool ShipLoaderEvent::hasVesselID() const {
    switch (type) {
        case ShipLoaderEventType::StartVesselLoad:
            return true;
        case ShipLoaderEventType::Fail:
        case ShipLoaderEventType::Fix:
        case ShipLoaderEventType::LoadComplete:
        case ShipLoaderEventType::LoadOperationComplete:
        case ShipLoaderEventType::LoadOperationStart:
        case ShipLoaderEventType::LoadStart:
        case ShipLoaderEventType::MaintenanceComplete:
        case ShipLoaderEventType::MaintenanceStart:
        case ShipLoaderEventType::OnMove:
        case ShipLoaderEventType::OnStopMove:
        case ShipLoaderEventType::SyncedFail:
        case ShipLoaderEventType::SyncedFix:
        case ShipLoaderEventType::WrapUp:
        default:
            return false;
    }
}