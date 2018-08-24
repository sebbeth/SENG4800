#include "StockpileEvent.h"

bool StockpileEvent::hasAmount() const {
    switch (type) {
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StockpileRemnant:
        case StockpileEventType::StockpileRemoved:
            return true;
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferStart:
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileCreated:
        default:
            return false;
    }
}

bool StockpileEvent::hasLength() const {
    switch (type) {
        case StockpileEventType::StockpileCreated:
            return true;
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StackTransferStart:
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileRemnant:
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasMachineID() const {
    switch (type) {
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StackTransferStart:
        case StockpileEventType::StockpileRemnant:
            return true;
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasPadID() const {
    switch (type) {
        case StockpileEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool StockpileEvent::hasStartPosition() const {
    switch (type) {
        case StockpileEventType::StockpileCreated:
            return true;
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StackTransferStart:
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileRemnant:
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasStockpileID() const {
    switch (type) {
        case StockpileEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool StockpileEvent::hasTime() const {
    switch (type) {
        case StockpileEventType::Invalid:
            return false;
        default:
            return true;

    }
}

bool StockpileEvent::hasVesselID() const {
    switch (type) {
        case StockpileEventType::Invalid:
            return false;
        default:
            return true;

    }
}