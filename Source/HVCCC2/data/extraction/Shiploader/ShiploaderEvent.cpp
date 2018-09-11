/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#include "ShiploaderEvent.h"

bool ShiploaderEvent::hasAmount() const {
    switch (type) {
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
            return true;
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::StartVesselDraftSurvey:
        case ShiploaderEventType::StartVesselLoad:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
        default:
            return false;
    }
}

bool ShiploaderEvent::hasPosition() const {
    switch (type) {
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::StartVesselLoad:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
            return true;
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::StartVesselDraftSurvey:
        default:
            return false;
    }
}

bool ShiploaderEvent::hasStockpileID() const {
    switch (type) {
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
            return true;
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::StartVesselDraftSurvey:
        case ShiploaderEventType::StartVesselLoad:
        default:
            return false;
    }
}

bool ShiploaderEvent::hasTime() const {
    switch (type) {
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::StartVesselLoad:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
            return true;
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::StartVesselDraftSurvey:
        default:
            return false;
    }
}

bool ShiploaderEvent::hasVesselID() const {
    switch (type) {
        case ShiploaderEventType::StartVesselLoad:
            return true;
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::StartVesselDraftSurvey:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
        default:
            return false;
    }
}