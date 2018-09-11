/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "ShiploaderState.h"

ShiploaderStateType ShiploaderState::determineNextType(ShiploaderStateType stateType, ShiploaderEventType eventType) {
    switch(stateType) {
        case ShiploaderStateType::Idle:
            switch(eventType) {
                case ShiploaderEventType::MaintenanceStart:
                    return ShiploaderStateType::Maintenance;
                case ShiploaderEventType::OnMove:
                    return ShiploaderStateType::Moving;
                case ShiploaderEventType::StartVesselLoad:
                    return ShiploaderStateType::Idle;
                case ShiploaderEventType::LoadOperationStart:
                    return ShiploaderStateType::PreLoadReserved;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::Maintenance:
            switch(eventType) {
                case ShiploaderEventType::MaintenanceComplete:
                    return ShiploaderStateType::Idle;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::Moving:
            switch(eventType) {
                case ShiploaderEventType::OnStopMove:
                    return ShiploaderStateType::Idle;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::PreLoadReserved:
            switch(eventType) {
                case ShiploaderEventType::LoadStart:
                    return ShiploaderStateType::Working;
                case ShiploaderEventType::Fail:
                    return ShiploaderStateType::PreLoadFailed;
                case ShiploaderEventType::SyncedFail:
                    return ShiploaderStateType::PreLoadSyncedFail;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::Working:
            switch(eventType) {
                case ShiploaderEventType::Fail:
                    return ShiploaderStateType::WorkingFailed;
                case ShiploaderEventType::LoadComplete:
                    return ShiploaderStateType::PostLoadReserved;
                case ShiploaderEventType::StartVesselDraftSurvey:
                    return ShiploaderStateType::InterimDraftSurvey;
                case ShiploaderEventType::SyncedFail:
                    return ShiploaderStateType::WorkingSyncedFail;
                case ShiploaderEventType::HatchChangeStart:
                    return ShiploaderStateType::ChaningHatches;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::PreLoadFailed:
            switch(eventType) {
                case ShiploaderEventType::Fix:
                    return ShiploaderStateType::PreLoadReserved;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::PreLoadSyncedFail:
            switch(eventType) {
                case ShiploaderEventType::SyncedFix:
                    return ShiploaderStateType::PreLoadReserved;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::WorkingFailed:
            switch(eventType) {
                case ShiploaderEventType::Fix:
                    return ShiploaderStateType::Working;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::PostLoadReserved:
            switch(eventType) {
                case ShiploaderEventType::SyncedFail:
                    return ShiploaderStateType::PostLoadSyncedFail;
                case ShiploaderEventType::Fail:
                    return ShiploaderStateType::PostLoadFailed;
                case ShiploaderEventType::LoadOperationComplete:
                    return ShiploaderStateType::Idle;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::InterimDraftSurvey:
            switch(eventType) {
                case ShiploaderEventType::SyncedFail:
                    return ShiploaderStateType::InterimDraftSyncFail;
                case ShiploaderEventType::FinishVesselDraftSurvey:
                    return ShiploaderStateType::Working;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::WorkingSyncedFail:
            switch(eventType) {
                case ShiploaderEventType::SyncedFix:
                    return ShiploaderStateType::Working;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::ChaningHatches:
            return ShiploaderStateType::Invalid;
        case ShiploaderStateType::PostLoadSyncedFail:
            switch(eventType) {
                case ShiploaderEventType::SyncedFix:
                    return ShiploaderStateType::PostLoadReserved;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::PostLoadFailed:
            switch(eventType) {
                case ShiploaderEventType::Fix:
                    return ShiploaderStateType::PostLoadReserved;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::InterimDraftSyncFail:
            switch(eventType) {
                case ShiploaderEventType::SyncedFix:
                    return ShiploaderStateType::InterimDraftSurvey;
                case ShiploaderEventType::FinishVesselDraftSurvey:
                    return ShiploaderStateType::WorkingSyncedFail;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::ChangingHatches:
            switch(eventType) {
                case ShiploaderEventType::OnHatchChangeComplete:
                    return ShiploaderStateType::Working;
                case ShiploaderEventType::SyncedFail:
                    return ShiploaderStateType::ChangingHatchesSyncedFail;
                case ShiploaderEventType::Fail:
                    return ShiploaderStateType::ChangingHatchesFailed;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::ChangingHatchesSyncedFail:
            return ShiploaderStateType::Invalid;
        case ShiploaderStateType::ChangingHatchesFailed:
            switch(eventType) {
                case ShiploaderEventType::Fix:
                    return ShiploaderStateType::ChangingHatches;
                default:
                    return ShiploaderStateType::Invalid;
            }
        case ShiploaderStateType::ChangingHatchesSyncedFailed:
            switch(eventType) {
                case ShiploaderEventType::OnHatchChangeComplete:
                    return ShiploaderStateType::WorkingSyncedFail;
                case ShiploaderEventType::SyncedFix:
                    return ShiploaderStateType::ChangingHatches;
                default:
                    return ShiploaderStateType::Invalid;
            }
        default:
            return ShiploaderStateType::Invalid;
    }
}