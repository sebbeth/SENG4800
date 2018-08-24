#include "SignalEvent.h"

bool SignalEvent::hasSignalID() const {
    switch (type) {
        case SignalEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool SignalEvent::hasSignalState() const {
    switch (type) {
        case SignalEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool SignalEvent::hasTime() const {
    switch (type) {
        case SignalEventType::Invalid:
            return false;
        default:
            return true;

    }
}