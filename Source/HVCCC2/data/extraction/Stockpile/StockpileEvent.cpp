/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "StockpileEvent.h"

bool StockpileEvent::hasAmount() const {
    switch (type) {
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StockpileRemnant:
            return true;
        case StockpileEventType::DedicatedStockpileCreated:
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferStart:
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasLength() const {
    switch (type) {
        case StockpileEventType::DedicatedStockpileCreated:
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
        case StockpileEventType::DedicatedStockpileCreated:
        case StockpileEventType::StockpileBuilt:
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasPadID() const {
    switch (type) {
        case StockpileEventType::DedicatedStockpileCreated:
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
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemnant:
            return true;
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasPosition() const {
    switch (type) {
        case StockpileEventType::DedicatedStockpileCreated:
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

bool StockpileEvent::hasTime() const {
    switch (type) {
        case StockpileEventType::DedicatedStockpileCreated:
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
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemnant:
            return true;
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}

bool StockpileEvent::hasVesselID() const {
    switch (type) {
        case StockpileEventType::DedicatedStockpileCreated:
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
        case StockpileEventType::StockpileCreated:
        case StockpileEventType::StockpileRemnant:
            return true;
        case StockpileEventType::StockpileRemoved:
        default:
            return false;
    }
}