/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Preload:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::PreloadFail;
                case LoadpointsEventType::StartLoad:
                    return LoadpointsStateType::Loading;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::IdleFix;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Maintenance:
            switch(eventType) {
                case LoadpointsEventType::MaintenanceComplete:
                    return LoadpointsStateType::Idle;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::WrappedUp:
            return LoadpointsStateType::Invalid;
        case LoadpointsStateType::IdleFix:
            switch(eventType) {
                case LoadpointsEventType::StartIdle:
                    return LoadpointsStateType::Idle;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PreloadFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::PreloadFix;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Loading:
            switch(eventType) {
                case LoadpointsEventType::FinishLoad:
                    return LoadpointsStateType::IdleLoading;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PreloadFix:
            switch(eventType) {
                case LoadpointsEventType::StartPreload:
                    return LoadpointsStateType::Preload;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
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
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleLoadingFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::IdleLoadingFix;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Postload:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::PostloadFail;
                case LoadpointsEventType::StartRecharge:
                    return LoadpointsStateType::Recharging;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::IdleLoadingFix:
            switch(eventType) {
                case LoadpointsEventType::StartLoad:
                    return LoadpointsStateType::Loading;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PostloadFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::PostloadFix;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::Recharging:
            switch(eventType) {
                case LoadpointsEventType::OnFail:
                    return LoadpointsStateType::RechargingFail;
                case LoadpointsEventType::StartIdle:
                    return LoadpointsStateType::Idle;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::PostloadFix:
            switch(eventType) {
                case LoadpointsEventType::StartPostload:
                    return LoadpointsStateType::Postload;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::RechargingFail:
            switch(eventType) {
                case LoadpointsEventType::OnFix:
                    return LoadpointsStateType::RechargingFix;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        case LoadpointsStateType::RechargingFix:
            return LoadpointsStateType::Invalid;
        case LoadpointsStateType::RecharingFix:
            switch(eventType) {
                case LoadpointsEventType::StartRecharge:
                    return LoadpointsStateType::Recharging;
                case LoadpointsEventType::WrapUp:
                    return LoadpointsStateType::WrappedUp;
                default:
                    return LoadpointsStateType::Invalid;
            }
        default:
            return LoadpointsStateType::Invalid;
    }
}