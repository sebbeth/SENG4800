/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class TrainMovementEventType {
    EnterTrack,
    HeadLeaveTrack,
    Invalid
};

TrainMovementEventType decodeTrainMovementEventType(const std::string& enumeratorString);
std::string encodeTrainMovementEventType(const TrainMovementEventType& value);