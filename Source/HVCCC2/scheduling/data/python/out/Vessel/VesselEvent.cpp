#include "VesselEvent.h"

bool VesselEvent::hasIsTidal() const {
    switch (type) {
        case VesselEventType::WaitEnter:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::MoveToSwingBasin:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasMeterMark() const {
    switch (type) {
        case VesselEventType::ArriveTerminal:
            return true;
        case VesselEventType::AtAnchorage:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::MoveToSwingBasin:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasNumberOfTugs() const {
    switch (type) {
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::ExitChannel:
        case VesselEventType::MoveToSwingBasin:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasTerminalID() const {
    switch (type) {
        case VesselEventType::AtAnchorage:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::MoveToSwingBasin:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasTime() const {
    switch (type) {
        case VesselEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool VesselEvent::hasVesselID() const {
    switch (type) {
        case VesselEventType::Invalid:
            return false;
        default:
            return true;

    }
}