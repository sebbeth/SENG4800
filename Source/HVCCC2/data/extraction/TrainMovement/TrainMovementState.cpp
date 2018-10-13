/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "TrainMovementState.h"

TrainMovementStateType TrainMovementState::determineNextType(TrainMovementStateType stateType, TrainMovementEventType eventType) {
    switch(stateType) {
        case TrainMovementStateType::Idle:
            switch(eventType) {
                case TrainMovementEventType::HeadLeaveTrack:
                    return TrainMovementStateType::LeavingTrack;
                case TrainMovementEventType::EnterTrack:
                    return TrainMovementStateType::EnteringTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::LeavingTrack:
            switch(eventType) {
                case TrainMovementEventType::EnterTrack:
                    return TrainMovementStateType::EnteringTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        case TrainMovementStateType::EnteringTrack:
            switch(eventType) {
                case TrainMovementEventType::HeadLeaveTrack:
                    return TrainMovementStateType::LeavingTrack;
                default:
                    return TrainMovementStateType::Invalid;
            }
        default:
            return TrainMovementStateType::Invalid;
    }
}