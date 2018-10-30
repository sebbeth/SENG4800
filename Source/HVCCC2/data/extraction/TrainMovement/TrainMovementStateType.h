/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class TrainMovementStateType {
    EnteringTrack,
    Idle,
    LeavingTrack,
    Invalid
};

TrainMovementStateType decodeTrainMovementStateType(const std::string& enumeratorString);
std::string encodeTrainMovementStateType(const TrainMovementStateType& value);