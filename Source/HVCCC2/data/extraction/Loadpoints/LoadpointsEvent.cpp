/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "LoadpointsEvent.h"

bool LoadpointsEvent::hasAmount() const {
    switch (type) {
        case LoadpointsEventType::FinishLoad:
            return true;
        case LoadpointsEventType::MaintenanceComplete:
        case LoadpointsEventType::MaintenanceStart:
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartLoad:
        case LoadpointsEventType::StartPostLoad:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
        case LoadpointsEventType::WrapUp:
        default:
            return false;
    }
}

bool LoadpointsEvent::hasCycleID() const {
    switch (type) {
        case LoadpointsEventType::FinishLoad:
        case LoadpointsEventType::StartLoad:
            return true;
        case LoadpointsEventType::MaintenanceComplete:
        case LoadpointsEventType::MaintenanceStart:
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartPostLoad:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
        case LoadpointsEventType::WrapUp:
        default:
            return false;
    }
}

bool LoadpointsEvent::hasLoadpointName() const {
    switch (type) {
        case LoadpointsEventType::FinishLoad:
        case LoadpointsEventType::MaintenanceComplete:
        case LoadpointsEventType::MaintenanceStart:
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartLoad:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
        case LoadpointsEventType::WrapUp:
            return true;
        case LoadpointsEventType::StartPostLoad:
        default:
            return false;
    }
}

bool LoadpointsEvent::hasTime() const {
    switch (type) {
        case LoadpointsEventType::FinishLoad:
        case LoadpointsEventType::MaintenanceComplete:
        case LoadpointsEventType::MaintenanceStart:
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartLoad:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
        case LoadpointsEventType::WrapUp:
            return true;
        case LoadpointsEventType::StartPostLoad:
        default:
            return false;
    }
}