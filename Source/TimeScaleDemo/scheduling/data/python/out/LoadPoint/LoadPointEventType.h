#pragma once
#include <string>

enum class LoadPointEventType {
    FinishLoad,
    MaintenanceComplete,
    MaintenanceStart,
    OnFail,
    OnFix,
    StartIdle,
    StartLoad,
    StartPostload,
    StartPreload,
    StartRecharge,
    WrapUp,
    Invalid
};

LoadPointEventType decodeLoadPointEventType(const std::string& enumeratorString);