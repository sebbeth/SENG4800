/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#include "SignalEvent.h"

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