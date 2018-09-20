/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
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
    Invalid
};

LoadpointsEventType decodeLoadpointsEventType(const std::string& enumeratorString);
std::string encodeLoadpointsEventType(const LoadpointsEventType& value);