/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class LoadpointsStateType {
    Idle,
    IdleFail,
    IdleFix,
    IdleLoading,
    IdleLoadingFail,
    IdleLoadingFix,
    Loading,
    Maintenance,
    Postload,
    PostloadFail,
    PostloadFix,
    Preload,
    PreloadFail,
    PreloadFix,
    Recharging,
    RechargingFail,
    RechargingFix,
    RecharingFix,
    WrappedUp,
    Invalid
};

LoadpointsStateType decodeLoadpointsStateType(const std::string& enumeratorString);
std::string encodeLoadpointsStateType(const LoadpointsStateType& value);