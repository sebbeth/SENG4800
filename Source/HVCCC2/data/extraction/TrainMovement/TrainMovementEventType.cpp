/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "TrainMovementEventType.h"
        
TrainMovementEventType decodeTrainMovementEventType(const std::string& enumeratorString) {
    if (enumeratorString == "EnterTrack") {
        return TrainMovementEventType::EnterTrack;
    } else if (enumeratorString == "HeadLeaveTrack") {
        return TrainMovementEventType::HeadLeaveTrack;
    } else {
        return TrainMovementEventType::Invalid;
    }
}
std::string encodeTrainMovementEventType(const TrainMovementEventType& value) {
    switch(value) {
        case TrainMovementEventType::HeadLeaveTrack:
            return "HeadLeaveTrack";
            break;

        case TrainMovementEventType::EnterTrack:
            return "EnterTrack";
            break;

        default:
            return "Invalid";
    }
}