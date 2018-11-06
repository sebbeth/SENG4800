/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "TrainMovementStateType.h"
        
TrainMovementStateType decodeTrainMovementStateType(const std::string& enumeratorString) {
    if (enumeratorString == "EnteringTrack") {
        return TrainMovementStateType::EnteringTrack;
    } else if (enumeratorString == "Idle") {
        return TrainMovementStateType::Idle;
    } else if (enumeratorString == "LeavingTrack") {
        return TrainMovementStateType::LeavingTrack;
    } else {
        return TrainMovementStateType::Invalid;
    }
}
std::string encodeTrainMovementStateType(const TrainMovementStateType& value) {
    switch(value) {
        case TrainMovementStateType::Idle:
            return "Idle";
            break;

        case TrainMovementStateType::LeavingTrack:
            return "LeavingTrack";
            break;

        case TrainMovementStateType::EnteringTrack:
            return "EnteringTrack";
            break;

        default:
            return "Invalid";
    }
}