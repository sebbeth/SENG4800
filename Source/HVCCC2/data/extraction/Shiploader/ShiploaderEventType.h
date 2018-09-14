/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#pragma once
#include <string>

enum class ShiploaderEventType {
    Fail,
    FinishVesselDraftSurvey,
    Fix,
    HatchChangeStart,
    LoadComplete,
    LoadOperationComplete,
    LoadOperationStart,
    LoadStart,
    MaintenanceComplete,
    MaintenanceStart,
    OnHatchChangeComplete,
    OnMove,
    OnStopMove,
    StartVesselDraftSurvey,
    StartVesselLoad,
    SyncedFail,
    SyncedFix,
    Invalid
};

ShiploaderEventType decodeShiploaderEventType(const std::string& enumeratorString);
std::string encodeShiploaderEventType(const ShiploaderEventType& value);