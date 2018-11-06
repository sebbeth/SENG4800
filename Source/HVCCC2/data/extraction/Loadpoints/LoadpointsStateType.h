/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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