/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-02 12:43:09.061192
 **/
#pragma once
#include <string>

enum class LoadpointsEventType {
    FinishLoad,
    MaintenanceComplete,
    MaintenanceStart,
    OnFail,
    OnFix,
    StartIdle,
    StartLoad,
    StartPostLoad,
    StartPostload,
    StartPreload,
    StartRecharge,
    WrapUp,
    Invalid
};

LoadpointsEventType decodeLoadpointsEventType(const std::string& enumeratorString);
std::string encodeLoadpointsEventType(const LoadpointsEventType& value);