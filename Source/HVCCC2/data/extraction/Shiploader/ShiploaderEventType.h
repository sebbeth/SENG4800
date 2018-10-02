/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
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
    WrapUp,
    Invalid
};

ShiploaderEventType decodeShiploaderEventType(const std::string& enumeratorString);
std::string encodeShiploaderEventType(const ShiploaderEventType& value);