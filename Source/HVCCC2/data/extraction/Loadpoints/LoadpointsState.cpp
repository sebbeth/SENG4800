/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "LoadpointsState.h"

LoadpointsStateType LoadpointsState::determineNextType(LoadpointsStateType stateType, LoadpointsEventType eventType) {
    switch(stateType) {
        case LoadpointsStateType::Idle:
            switch(eventType) {
                case LoadpointsEventType::StartPreload:
                    return LoadpointsStateType::Preload;
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::IdleFail;
                case LoadpointsEventType::MaintenanceStart:
                    return LoadpointsStateType::Maintenance;
                case LoadpointsEventType::StartIdle:
                    return LoadpointsStateType::Idle;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Preload:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::PreloadFail;
                case LoadpointsEventType::StartLoad:
                    return LoadpointsStateType::Loading;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::IdleFix;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Maintenance:
            switch(eventType) {
                case LoadpointsEventType::MaintenanceComplete:
                    return LoadpointsStateType::Idle;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleFix:
            switch(eventType) {
                case LoadpointsEventType::StartIdle:
                    return LoadpointsStateType::Idle;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PreloadFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::PreloadFix;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Loading:
            switch(eventType) {
                case LoadpointsEventType::FinishLoad:
                    return LoadpointsStateType::IdleLoading;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PreloadFix:
            switch(eventType) {
                case LoadpointsEventType::StartPreload:
                    return LoadpointsStateType::Preload;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleLoading:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::IdleLoadingFail;
                case LoadpointsEventType::StartLoad:
                    return LoadpointsStateType::Loading;
                case LoadpointsEventType::StartPostLoad:
                    return LoadpointsStateType::Postload;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleLoadingFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::IdleLoadingFix;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Postload:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::PostloadFail;
                case LoadpointsEventType::StartRecharge:
                    return LoadpointsStateType::Recharging;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleLoadingFix:
            switch(eventType) {
                case LoadpointsEventType::StartLoad:
                    return LoadpointsStateType::Loading;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PostloadFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::PostloadFix;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Recharging:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::RechargingFail;
                case LoadpointsEventType::StartIdle:
                    return LoadpointsStateType::Idle;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PostloadFix:
            switch(eventType) {
                case LoadpointsEventType::StartPostload:
                    return LoadpointsStateType::Postload;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::RechargingFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::RechargingFix;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::RechargingFix:
            return LoadpointsStateType::Invalid;
        case LoadpointsStateType::RecharingFix:
            switch(eventType) {
                case LoadpointsEventType::StartRecharge:
                    return LoadpointsStateType::Recharging;
                default:
                    return LoadpointsStateType::Invalid;
            }
        default:
            return LoadpointsStateType::Invalid;
    }
}