/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class ShiploaderStateType {
    ChangingHatches,
    ChangingHatchesFailed,
    ChangingHatchesSyncedFail,
    ChangingHatchesSyncedFailed,
    ChaningHatches,
    Idle,
    InterimDraftSurvey,
    InterimDraftSyncFail,
    Maintenance,
    Moving,
    PostLoadFailed,
    PostLoadReserved,
    PostLoadSyncedFail,
    PreLoadFailed,
    PreLoadReserved,
    PreLoadSyncedFail,
    Working,
    WorkingFailed,
    WorkingSyncedFail,
    WrappedUp,
    Invalid
};

ShiploaderStateType decodeShiploaderStateType(const std::string& enumeratorString);
std::string encodeShiploaderStateType(const ShiploaderStateType& value);