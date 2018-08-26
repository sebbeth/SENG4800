#include "LoadPointEventType.h"

LoadPointEventType decodeLoadPointEventType(const std::string& enumeratorString) {
    if (enumeratorString == "FinishLoad") {
        return LoadPointEventType::FinishLoad;
    } else if (enumeratorString == "MaintComp") {
        return LoadPointEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return LoadPointEventType::MaintenanceStart;
    } else if (enumeratorString == "OnFail") {
        return LoadPointEventType::OnFail;
    } else if (enumeratorString == "OnFix") {
        return LoadPointEventType::OnFix;
    } else if (enumeratorString == "StartIdle") {
        return LoadPointEventType::StartIdle;
    } else if (enumeratorString == "StartLoad") {
        return LoadPointEventType::StartLoad;
    } else if (enumeratorString == "StartPostload") {
        return LoadPointEventType::StartPostload;
    } else if (enumeratorString == "StartPreload") {
        return LoadPointEventType::StartPreload;
    } else if (enumeratorString == "StartRecharge") {
        return LoadPointEventType::StartRecharge;
    } else if (enumeratorString == "WrapUp") {
        return LoadPointEventType::WrapUp;
    } else {
        return LoadPointEventType::Invalid;
    }
}