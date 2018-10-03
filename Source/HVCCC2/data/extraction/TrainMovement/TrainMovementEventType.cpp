/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "TrainMovementEventType.h"
        
TrainMovementEventType decodeTrainMovementEventType(const std::string& enumeratorString) {
    if (enumeratorString == "EnterTrack") {
        return TrainMovementEventType::EnterTrack;
    } else if (enumeratorString == "HeadLeaveTrack") {
        return TrainMovementEventType::HeadLeaveTrack;
    } else if (enumeratorString == "MaintAttempted") {
        return TrainMovementEventType::MaintenanceAttempted;
    } else if (enumeratorString == "MaintCompleted") {
        return TrainMovementEventType::MaintenanceCompleted;
    } else if (enumeratorString == "MaintStart") {
        return TrainMovementEventType::MaintenanceStart;
    } else if (enumeratorString == "ReachedSignal") {
        return TrainMovementEventType::ReachedSignal;
    } else if (enumeratorString == "TailLeaveTrack") {
        return TrainMovementEventType::TailLeaveTrack;
    } else if (enumeratorString == "WaitForTracks") {
        return TrainMovementEventType::WaitForTracks;
    } else if (enumeratorString == "WaitingComp") {
        return TrainMovementEventType::WaitingComplete;
    } else if (enumeratorString == "WaitingStart") {
        return TrainMovementEventType::WaitingStart;
    } else {
        return TrainMovementEventType::Invalid;
    }
}
std::string encodeTrainMovementEventType(const TrainMovementEventType& value) {
    switch(value) {
        case TrainMovementEventType::HeadLeaveTrack:
            return "HeadLeaveTrack";
            break;

        case TrainMovementEventType::WaitForTracks:
            return "WaitForTracks";
            break;

        case TrainMovementEventType::EnterTrack:
            return "EnterTrack";
            break;

        case TrainMovementEventType::TailLeaveTrack:
            return "TailLeaveTrack";
            break;

        case TrainMovementEventType::ReachedSignal:
            return "ReachedSignal";
            break;

        case TrainMovementEventType::WaitingStart:
            return "WaitingStart";
            break;

        case TrainMovementEventType::MaintenanceAttempted:
            return "MaintAttempted";
            break;

        case TrainMovementEventType::WaitingComplete:
            return "WaitingComp";
            break;

        case TrainMovementEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case TrainMovementEventType::MaintenanceCompleted:
            return "MaintCompleted";
            break;

        default:
            return "Invalid";
    }
}