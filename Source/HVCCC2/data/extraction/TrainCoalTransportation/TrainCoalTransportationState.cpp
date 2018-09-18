/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "TrainCoalTransportationState.h"

TrainCoalTransportationStateType TrainCoalTransportationState::determineNextType(TrainCoalTransportationStateType stateType, TrainCoalTransportationEventType eventType) {
    switch(stateType) {
        case TrainCoalTransportationStateType::Nonexistent:
            switch(eventType) {
                case TrainCoalTransportationEventType::Created:
                    return TrainCoalTransportationStateType::Idle;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::Idle:
            switch(eventType) {
                case TrainCoalTransportationEventType::DepartTerminal:
                    return TrainCoalTransportationStateType::DepartedTerminal;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::DepartedTerminal:
            switch(eventType) {
                case TrainCoalTransportationEventType::ArrivedLoadpoint:
                    return TrainCoalTransportationStateType::ArrivedLoadpoint;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::ArrivedLoadpoint:
            switch(eventType) {
                case TrainCoalTransportationEventType::LoadStart:
                    return TrainCoalTransportationStateType::Loading;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::Loading:
            switch(eventType) {
                case TrainCoalTransportationEventType::LoadComplete:
                    return TrainCoalTransportationStateType::Loaded;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::Loaded:
            switch(eventType) {
                case TrainCoalTransportationEventType::LoadStart:
                    return TrainCoalTransportationStateType::Loading;
                case TrainCoalTransportationEventType::DepartLoadpoint:
                    return TrainCoalTransportationStateType::DepartedLoadpoint;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::DepartedLoadpoint:
            switch(eventType) {
                case TrainCoalTransportationEventType::ArrivedDumpstation:
                    return TrainCoalTransportationStateType::ArrivedDumpstation;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::ArrivedDumpstation:
            switch(eventType) {
                case TrainCoalTransportationEventType::DumpStart:
                    return TrainCoalTransportationStateType::Dumping;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::Dumping:
            switch(eventType) {
                case TrainCoalTransportationEventType::DumpComplete:
                    return TrainCoalTransportationStateType::Dumped;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        case TrainCoalTransportationStateType::Dumped:
            switch(eventType) {
                case TrainCoalTransportationEventType::DumpStart:
                    return TrainCoalTransportationStateType::Dumping;
                case TrainCoalTransportationEventType::DepartTerminal:
                    return TrainCoalTransportationStateType::DepartedTerminal;
                default:
                    return TrainCoalTransportationStateType::Invalid;
            }
        default:
            return TrainCoalTransportationStateType::Invalid;
    }
}