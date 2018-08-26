#include "LoadPointEvent.h"

bool LoadPointEvent::hasAmount() const {
    switch (type) {
        case LoadPointEventType::FinishLoad:
            return true;
        case LoadPointEventType::MaintenanceComplete:
        case LoadPointEventType::MaintenanceStart:
        case LoadPointEventType::OnFail:
        case LoadPointEventType::OnFix:
        case LoadPointEventType::StartIdle:
        case LoadPointEventType::StartLoad:
        case LoadPointEventType::StartPostload:
        case LoadPointEventType::StartPreload:
        case LoadPointEventType::StartRecharge:
        case LoadPointEventType::WrapUp:
        default:
            return false;
    }
}

bool LoadPointEvent::hasCycleID() const {
    switch (type) {
        case LoadPointEventType::FinishLoad:
        case LoadPointEventType::StartLoad:
            return true;
        case LoadPointEventType::MaintenanceComplete:
        case LoadPointEventType::MaintenanceStart:
        case LoadPointEventType::OnFail:
        case LoadPointEventType::OnFix:
        case LoadPointEventType::StartIdle:
        case LoadPointEventType::StartPostload:
        case LoadPointEventType::StartPreload:
        case LoadPointEventType::StartRecharge:
        case LoadPointEventType::WrapUp:
        default:
            return false;
    }
}

bool LoadPointEvent::hasLoadPointID() const {
    switch (type) {
        case LoadPointEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool LoadPointEvent::hasLoadPointName() const {
    switch (type) {
        case LoadPointEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool LoadPointEvent::hasTime() const {
    switch (type) {
        case LoadPointEventType::Invalid:
            return false;
        default:
            return true;

    }
}