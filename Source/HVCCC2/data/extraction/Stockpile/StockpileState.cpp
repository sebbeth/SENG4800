/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#include "StockpileState.h"

StockpileStateType StockpileState::determineNextType(StockpileStateType stateType, StockpileEventType eventType) {
    switch(stateType) {
        case StockpileStateType::Idle:
            switch(eventType) {
                case StockpileEventType::StockpileCreated:
                    return StockpileStateType::Created;
                case StockpileEventType::DedicatedStockpileCreated:
                    return StockpileStateType::DedicatedCreated;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Built:
            switch(eventType) {
                case StockpileEventType::StackStart:
                    return StockpileStateType::StackingBuilt;
                case StockpileEventType::ReclaimStart:
                    return StockpileStateType::Reclaiming;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::StackingBuilt:
            switch(eventType) {
                case StockpileEventType::StackComplete:
                    return StockpileStateType::Built;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Reclaiming:
            switch(eventType) {
                case StockpileEventType::ReclaimComplete:
                    return StockpileStateType::Reclaimed;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Created:
            switch(eventType) {
                case StockpileEventType::StackStart:
                    return StockpileStateType::Stacking;
                case StockpileEventType::StockpileBuilt:
                    return StockpileStateType::Built;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Stacking:
            switch(eventType) {
                case StockpileEventType::StackComplete:
                    return StockpileStateType::Created;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::DeciatedReclaiming:
            switch(eventType) {
                case StockpileEventType::ReclaimComplete:
                    return StockpileStateType::DedicatedCreated;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::DedicatedCreated:
            switch(eventType) {
                case StockpileEventType::ReclaimStart:
                    return StockpileStateType::DedicatedReclaiming;
                case StockpileEventType::StackTransferStart:
                    return StockpileStateType::RemnantStacking;
                case StockpileEventType::StackStart:
                    return StockpileStateType::DedicatedStacking;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::DedicatedReclaiming:
            return StockpileStateType::Invalid;
        case StockpileStateType::RemnantStacking:
            switch(eventType) {
                case StockpileEventType::StackTransferComplete:
                    return StockpileStateType::DedicatedCreated;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::DedicatedStacking:
            switch(eventType) {
                case StockpileEventType::StackComplete:
                    return StockpileStateType::DedicatedCreated;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Reclaimed:
            switch(eventType) {
                case StockpileEventType::StockpileRemnant:
                    return StockpileStateType::Remnant;
                case StockpileEventType::StockpileRemoved:
                    return StockpileStateType::Idle;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::Remnant:
            switch(eventType) {
                case StockpileEventType::ReclaimTransferStart:
                    return StockpileStateType::RemnantReclaiming;
                case StockpileEventType::RemnantRemoved:
                    return StockpileStateType::Idle;
                default:
                    return StockpileStateType::Invalid;
            }
        case StockpileStateType::RemnantReclaiming:
            switch(eventType) {
                case StockpileEventType::ReclaimTransferComplete:
                    return StockpileStateType::Remnant;
                default:
                    return StockpileStateType::Invalid;
            }
        default:
            return StockpileStateType::Invalid;
    }
}