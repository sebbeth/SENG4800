/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#pragma once
#include <string>

enum class TrainMovementEventType {
    EnterTrack,
    HeadLeaveTrack,
    MaintenanceAttempted,
    MaintenanceCompleted,
    MaintenanceStart,
    ReachedSignal,
    TailLeaveTrack,
    WaitForTracks,
    WaitingComplete,
    WaitingStart,
    Invalid
};

TrainMovementEventType decodeTrainMovementEventType(const std::string& enumeratorString);
std::string encodeTrainMovementEventType(const TrainMovementEventType& value);