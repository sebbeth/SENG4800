/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "TrainMovementEvent.h"

bool TrainMovementEvent::hasCycleID() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::TailLeaveTrack:
        case TrainMovementEventType::WaitForTracks:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasDirection() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::TailLeaveTrack:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasSectionID() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::TailLeaveTrack:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasSignalID() const {
    switch (type) {
        case TrainMovementEventType::ReachedSignal:
            return true;
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::TailLeaveTrack:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasSignalState() const {
    switch (type) {
        case TrainMovementEventType::ReachedSignal:
            return true;
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::TailLeaveTrack:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasSpeed() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::TailLeaveTrack:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasTime() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::TailLeaveTrack:
        case TrainMovementEventType::WaitForTracks:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}

bool TrainMovementEvent::hasTrackID() const {
    switch (type) {
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::TailLeaveTrack:
            return true;
        case TrainMovementEventType::MaintenanceAttempted:
        case TrainMovementEventType::MaintenanceCompleted:
        case TrainMovementEventType::MaintenanceStart:
        case TrainMovementEventType::ReachedSignal:
        case TrainMovementEventType::WaitForTracks:
        case TrainMovementEventType::WaitingComplete:
        case TrainMovementEventType::WaitingStart:
        default:
            return false;
    }
}