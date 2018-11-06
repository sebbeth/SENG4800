/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "LoadpointsStateType.h"
        
LoadpointsStateType decodeLoadpointsStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return LoadpointsStateType::Idle;
    } else if (enumeratorString == "IdleFail") {
        return LoadpointsStateType::IdleFail;
    } else if (enumeratorString == "IdleFix") {
        return LoadpointsStateType::IdleFix;
    } else if (enumeratorString == "IdleLoading") {
        return LoadpointsStateType::IdleLoading;
    } else if (enumeratorString == "IdleLoadingFail") {
        return LoadpointsStateType::IdleLoadingFail;
    } else if (enumeratorString == "IdleLoadingFix") {
        return LoadpointsStateType::IdleLoadingFix;
    } else if (enumeratorString == "Loading") {
        return LoadpointsStateType::Loading;
    } else if (enumeratorString == "Maintenance") {
        return LoadpointsStateType::Maintenance;
    } else if (enumeratorString == "Postload") {
        return LoadpointsStateType::Postload;
    } else if (enumeratorString == "PostloadFail") {
        return LoadpointsStateType::PostloadFail;
    } else if (enumeratorString == "PostloadFix") {
        return LoadpointsStateType::PostloadFix;
    } else if (enumeratorString == "Preload") {
        return LoadpointsStateType::Preload;
    } else if (enumeratorString == "PreloadFail") {
        return LoadpointsStateType::PreloadFail;
    } else if (enumeratorString == "PreloadFix") {
        return LoadpointsStateType::PreloadFix;
    } else if (enumeratorString == "Recharging") {
        return LoadpointsStateType::Recharging;
    } else if (enumeratorString == "RechargingFail") {
        return LoadpointsStateType::RechargingFail;
    } else if (enumeratorString == "RechargingFix") {
        return LoadpointsStateType::RechargingFix;
    } else if (enumeratorString == "RecharingFix") {
        return LoadpointsStateType::RecharingFix;
    } else if (enumeratorString == "WrappedUp") {
        return LoadpointsStateType::WrappedUp;
    } else {
        return LoadpointsStateType::Invalid;
    }
}
std::string encodeLoadpointsStateType(const LoadpointsStateType& value) {
    switch(value) {
        case LoadpointsStateType::Idle:
            return "Idle";
            break;

        case LoadpointsStateType::Preload:
            return "Preload";
            break;

        case LoadpointsStateType::IdleFail:
            return "IdleFail";
            break;

        case LoadpointsStateType::Maintenance:
            return "Maintenance";
            break;

        case LoadpointsStateType::WrappedUp:
            return "WrappedUp";
            break;

        case LoadpointsStateType::IdleFix:
            return "IdleFix";
            break;

        case LoadpointsStateType::PreloadFail:
            return "PreloadFail";
            break;

        case LoadpointsStateType::Loading:
            return "Loading";
            break;

        case LoadpointsStateType::PreloadFix:
            return "PreloadFix";
            break;

        case LoadpointsStateType::IdleLoading:
            return "IdleLoading";
            break;

        case LoadpointsStateType::IdleLoadingFail:
            return "IdleLoadingFail";
            break;

        case LoadpointsStateType::Postload:
            return "Postload";
            break;

        case LoadpointsStateType::IdleLoadingFix:
            return "IdleLoadingFix";
            break;

        case LoadpointsStateType::PostloadFail:
            return "PostloadFail";
            break;

        case LoadpointsStateType::Recharging:
            return "Recharging";
            break;

        case LoadpointsStateType::PostloadFix:
            return "PostloadFix";
            break;

        case LoadpointsStateType::RechargingFail:
            return "RechargingFail";
            break;

        case LoadpointsStateType::RechargingFix:
            return "RechargingFix";
            break;

        case LoadpointsStateType::RecharingFix:
            return "RecharingFix";
            break;

        default:
            return "Invalid";
    }
}