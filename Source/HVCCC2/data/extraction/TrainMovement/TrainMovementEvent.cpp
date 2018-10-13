/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "TrainMovementEvent.h"

bool TrainMovementEvent::hasCycleID() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainMovementEvent::hasDirection() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainMovementEvent::hasSectionID() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainMovementEvent::hasSpeed() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainMovementEvent::hasTime() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool TrainMovementEvent::hasTrackID() const {
    switch (type) {
        case TrainMovementEventType::Invalid:
            return false;
        default:
            return true;

    }
}