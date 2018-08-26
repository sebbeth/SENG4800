#include "StockpileState.h"

StockpileStateType StockpileState::determineNextType(StockpileStateType stateType, StockpileEventType eventType) {
    switch(eventType) {
        case StockpileEventType::ReclaimComplete:
            switch(stateType) {
                case StockpileStateType::Reclaiming:
                    return StockpileStateType::Built;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::ReclaimStart:
            switch(stateType) {
                case StockpileStateType::Built:
                    return StockpileStateType::Reclaiming;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::ReclaimTransferComplete:
            switch(stateType) {
                case StockpileStateType::RemnantReclaiming:
                    return StockpileStateType::Remnant;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::ReclaimTransferStart:
            switch(stateType) {
                case StockpileStateType::Remnant:
                    return StockpileStateType::RemnantReclaiming;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::RemnantRemoved:
            switch(stateType) {
                case StockpileStateType::Remnant:
                    return StockpileStateType::Idle;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StackComplete:
            switch(stateType) {
                case StockpileStateType::Stacking:
                    return StockpileStateType::Created;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StackStart:
            switch(stateType) {
                case StockpileStateType::Created:
                    return StockpileStateType::Stacking;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StackTransferComplete:
            switch(stateType) {
                case StockpileStateType::RemnantStacking:
                    return StockpileStateType::Idle;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StackTransferStart:
            switch(stateType) {
                case StockpileStateType::Idle:
                    return StockpileStateType::RemnantStacking;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StockpileBuilt:
            switch(stateType) {
                case StockpileStateType::Created:
                    return StockpileStateType::Built;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StockpileCreated:
            switch(stateType) {
                case StockpileStateType::Idle:
                    return StockpileStateType::Created;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StockpileRemnant:
            switch(stateType) {
                case StockpileStateType::Built:
                    return StockpileStateType::Remnant;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileEventType::StockpileRemoved:
            switch(stateType) {
                case StockpileStateType::Built:
                    return StockpileStateType::Idle;
                default:
                    return StockpileStateType::Invalid;
            }
        default:
            return StockpileStateType::Invalid;
    }
}