/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "LoadpointsEventType.h"
        
LoadpointsEventType decodeLoadpointsEventType(const std::string& enumeratorString) {
    if (enumeratorString == "FinishLoad") {
        return LoadpointsEventType::FinishLoad;
    } else if (enumeratorString == "MaintComp") {
        return LoadpointsEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return LoadpointsEventType::MaintenanceStart;
    } else if (enumeratorString == "OnFail") {
        return LoadpointsEventType::OnFail;
    } else if (enumeratorString == "OnFix") {
        return LoadpointsEventType::OnFix;
    } else if (enumeratorString == "StartIdle") {
        return LoadpointsEventType::StartIdle;
    } else if (enumeratorString == "StartLoad") {
        return LoadpointsEventType::StartLoad;
    } else if (enumeratorString == "StartPostLoad") {
        return LoadpointsEventType::StartPostLoad;
    } else if (enumeratorString == "StartPostload") {
        return LoadpointsEventType::StartPostload;
    } else if (enumeratorString == "StartPreload") {
        return LoadpointsEventType::StartPreload;
    } else if (enumeratorString == "StartRecharge") {
        return LoadpointsEventType::StartRecharge;
    } else if (enumeratorString == "WrapUp") {
        return LoadpointsEventType::WrapUp;
    } else {
        return LoadpointsEventType::Invalid;
    }
}
std::string encodeLoadpointsEventType(const LoadpointsEventType& value) {
    switch(value) {
        case LoadpointsEventType::StartPreload:
            return "StartPreload";
            break;

        case LoadpointsEventType::OnFail:
            return "OnFail";
            break;

        case LoadpointsEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case LoadpointsEventType::StartIdle:
            return "StartIdle";
            break;

        case LoadpointsEventType::WrapUp:
            return "WrapUp";
            break;

        case LoadpointsEventType::OnFix:
            return "OnFix";
            break;

        case LoadpointsEventType::MaintenanceComplete:
            return "MaintComp";
            break;

        case LoadpointsEventType::StartLoad:
            return "StartLoad";
            break;

        case LoadpointsEventType::FinishLoad:
            return "FinishLoad";
            break;

        case LoadpointsEventType::StartPostLoad:
            return "StartPostLoad";
            break;

        case LoadpointsEventType::StartRecharge:
            return "StartRecharge";
            break;

        case LoadpointsEventType::StartPostload:
            return "StartPostload";
            break;

        default:
            return "Invalid";
    }
}