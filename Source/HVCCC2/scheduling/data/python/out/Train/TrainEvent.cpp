#include "TrainEvent.h"

bool TrainEvent::hasAmount() const {
    switch (type) {
        case TrainEventType::DumpComplete:
        case TrainEventType::LoadComplete:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasCycleID() const {
    switch (type) {
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
            return true;
        case TrainEventType::Created:
        default:
            return false;
    }
}

bool TrainEvent::hasDepotID() const {
    switch (type) {
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasDirection() const {
    switch (type) {
        case TrainEventType::Created:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::TailLeaveTrack:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasDumpStationID() const {
    switch (type) {
        case TrainEventType::ArrivedDumpstation:
            return true;
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasJunctionID() const {
    switch (type) {
        case TrainEventType::Created:
        case TrainEventType::WaitJunction:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasLoadPointID() const {
    switch (type) {
        case TrainEventType::ArrivedLoadpoint:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasMaintenanceActivity() const {
    switch (type) {
        case TrainEventType::MaintenanceStart:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasPlannedTime() const {
    switch (type) {
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
            return true;
        case TrainEventType::Created:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasSectionID() const {
    switch (type) {
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::TailLeaveTrack:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasSignalID() const {
    switch (type) {
        case TrainEventType::ReachedSignal:
        case TrainEventType::WaitSignal:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        default:
            return false;
    }
}

bool TrainEvent::hasSignalState() const {
    switch (type) {
        case TrainEventType::ReachedSignal:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasSpeed() const {
    switch (type) {
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::TailLeaveTrack:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasTerminalID() const {
    switch (type) {
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::DepartTerminal:
            return true;
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}

bool TrainEvent::hasTime() const {
    switch (type) {
        case TrainEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainEvent::hasTrackID() const {
    switch (type) {
        case TrainEventType::Created:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitSignal:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        default:
            return false;
    }
}

bool TrainEvent::hasTrainID() const {
    switch (type) {
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::Created:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
            return true;
        case TrainEventType::DumpComplete:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        default:
            return false;
    }
}

bool TrainEvent::hasTrainType() const {
    switch (type) {
        case TrainEventType::Created:
            return true;
        case TrainEventType::ArrivedDumpstation:
        case TrainEventType::ArrivedLoadpoint:
        case TrainEventType::DepartLoadpoint:
        case TrainEventType::DepartTerminal:
        case TrainEventType::DumpComplete:
        case TrainEventType::DumpStart:
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::LoadComplete:
        case TrainEventType::LoadStart:
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
        case TrainEventType::MaintenanceStart:
        case TrainEventType::ReachedSignal:
        case TrainEventType::TailLeaveTrack:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
        case TrainEventType::WaitJunction:
        case TrainEventType::WaitSignal:
        default:
            return false;
    }
}