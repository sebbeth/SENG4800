#include "LoadPointState.h"

LoadPointStateType LoadPointState::determineNextType(LoadPointStateType stateType, LoadPointEventType eventType) {
    switch(eventType) {
        case LoadPointEventType::FinishLoad:
            switch(stateType) {
                case LoadPointStateType::Loading:
                    return LoadPointStateType::Loaded;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::MaintenanceComplete:
            switch(stateType) {
                case LoadPointStateType::Maintenanceenance:
                    return LoadPointStateType::MaintenanceenanceComplete;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::MaintenanceStart:
            switch(stateType) {
                case LoadPointStateType::Idle:
                    return LoadPointStateType::Maintenanceenance;
                case LoadPointStateType::Recharging:
                    return LoadPointStateType::Maintenanceenance;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::OnFail:
            switch(stateType) {
                case LoadPointStateType::Loaded:
                    return LoadPointStateType::Failed;
                case LoadPointStateType::MaintenanceenanceComplete:
                    return LoadPointStateType::Failed;
                case LoadPointStateType::Postload:
                    return LoadPointStateType::Failed;
                case LoadPointStateType::Preload:
                    return LoadPointStateType::Failed;
                case LoadPointStateType::Recharging:
                    return LoadPointStateType::Failed;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::OnFix:
            switch(stateType) {
                case LoadPointStateType::Failed:
                    return LoadPointStateType::Fixed;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::StartIdle:
            switch(stateType) {
                case LoadPointStateType::MaintenanceenanceComplete:
                    return LoadPointStateType::Recharging;
                case LoadPointStateType::Recharging:
                    return LoadPointStateType::Recharging;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::StartLoad:
            switch(stateType) {
                case LoadPointStateType::Fixed:
                    return LoadPointStateType::Loading;
                case LoadPointStateType::Preload:
                    return LoadPointStateType::Loading;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::StartPostload:
            switch(stateType) {
                case LoadPointStateType::Fixed:
                    return LoadPointStateType::Postload;
                case LoadPointStateType::Loaded:
                    return LoadPointStateType::Postload;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::StartPreload:
            switch(stateType) {
                case LoadPointStateType::Fixed:
                    return LoadPointStateType::Preload;
                case LoadPointStateType::Idle:
                    return LoadPointStateType::Preload;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::StartRecharge:
            switch(stateType) {
                case LoadPointStateType::Fixed:
                    return LoadPointStateType::Recharging;
                case LoadPointStateType::MaintenanceenanceComplete:
                    return LoadPointStateType::Recharging;
                case LoadPointStateType::Postload:
                    return LoadPointStateType::Recharging;
                default:
                    return LoadPointStateType::Invalid;
            }
        case LoadPointEventType::WrapUp:
            switch(stateType) {
                case LoadPointStateType::Failed:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Fixed:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Idle:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Loaded:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Loading:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Maintenanceenance:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::MaintenanceenanceComplete:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Postload:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Preload:
                    return LoadPointStateType::WrappedUp;
                case LoadPointStateType::Recharging:
                    return LoadPointStateType::WrappedUp;
                default:
                    return LoadPointStateType::Invalid;
            }
        default:
            return LoadPointStateType::Invalid;
    }
}