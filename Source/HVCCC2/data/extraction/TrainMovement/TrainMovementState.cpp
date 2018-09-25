/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "TrainMovementState.h"

TrainMovementStateType TrainMovementState::determineNextType(TrainMovementStateType stateType, TrainMovementEventType eventType) {
    switch(stateType) {
        case TrainMovementStateType::Idle:
            switch(eventType) {
                case TrainMovementEventType::HeadLeaveTrack:
                    return TrainMovementStateType::InJunction;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::InJunction:
            switch(eventType) {
                case TrainMovementEventType::EnterTrack:
                    return TrainMovementStateType::EnteringTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::EnteringTrack:
            switch(eventType) {
                case TrainMovementEventType::ReachedSignal:
                    return TrainMovementStateType::InTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::InTrack:
            switch(eventType) {
                case TrainMovementEventType::HeadLeaveTrack:
                    return TrainMovementStateType::InJunction;
                case TrainMovementEventType::ReachedSignal:
                    return TrainMovementStateType::InTrack;
                case TrainMovementEventType::WaitingStart:
                    return TrainMovementStateType::Waiting;
                case TrainMovementEventType::MaintenanceAttempted:
                    return TrainMovementStateType::RequestedMaintenance;
                case TrainMovementEventType::WaitForTracks:
                    return TrainMovementStateType::InTrack;
                case TrainMovementEventType::TailLeaveTrack:
                    return TrainMovementStateType::InTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::Waiting:
            switch(eventType) {
                case TrainMovementEventType::WaitingComplete:
                    return TrainMovementStateType::InTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::RequestedMaintenance:
            switch(eventType) {
                case TrainMovementEventType::MaintenanceStart:
                    return TrainMovementStateType::Maintenance;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::Maintenance:
            switch(eventType) {
                case TrainMovementEventType::MaintenanceCompleted:
                    return TrainMovementStateType::InTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        default:
            return TrainMovementStateType::Invalid;
    }
}