/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#include "StockpileEventType.h"
        
StockpileEventType decodeStockpileEventType(const std::string& enumeratorString) {
    if (enumeratorString == "DedicatedStockpileCreated") {
        return StockpileEventType::DedicatedStockpileCreated;
    } else if (enumeratorString == "ReclaimComp") {
        return StockpileEventType::ReclaimComplete;
    } else if (enumeratorString == "ReclaimStart") {
        return StockpileEventType::ReclaimStart;
    } else if (enumeratorString == "ReclaimTransComp") {
        return StockpileEventType::ReclaimTransferComplete;
    } else if (enumeratorString == "ReclaimTransStart") {
        return StockpileEventType::ReclaimTransferStart;
    } else if (enumeratorString == "RemnantRemoved") {
        return StockpileEventType::RemnantRemoved;
    } else if (enumeratorString == "StackComp") {
        return StockpileEventType::StackComplete;
    } else if (enumeratorString == "StackStart") {
        return StockpileEventType::StackStart;
    } else if (enumeratorString == "StackTransComp") {
        return StockpileEventType::StackTransferComplete;
    } else if (enumeratorString == "StackTransStart") {
        return StockpileEventType::StackTransferStart;
    } else if (enumeratorString == "StockpileBuilt") {
        return StockpileEventType::StockpileBuilt;
    } else if (enumeratorString == "StockpileCreated") {
        return StockpileEventType::StockpileCreated;
    } else if (enumeratorString == "StockpileRemnant") {
        return StockpileEventType::StockpileRemnant;
    } else if (enumeratorString == "StockpileRemoved") {
        return StockpileEventType::StockpileRemoved;
    } else {
        return StockpileEventType::Invalid;
    }
}
std::string encodeStockpileEventType(const StockpileEventType& value) {
    switch(value) {
        case StockpileEventType::StackStart:
            return "StackStart";
            break;

        case StockpileEventType::ReclaimStart:
            return "ReclaimStart";
            break;

        case StockpileEventType::StockpileBuilt:
            return "StockpileBuilt";
            break;

        case StockpileEventType::ReclaimComplete:
            return "ReclaimComp";
            break;

        case StockpileEventType::StackTransferStart:
            return "StackTransStart";
            break;

        case StockpileEventType::StackComplete:
            return "StackComp";
            break;

        case StockpileEventType::StockpileCreated:
            return "StockpileCreated";
            break;

        case StockpileEventType::DedicatedStockpileCreated:
            return "DedicatedStockpileCreated";
            break;

        case StockpileEventType::StockpileRemnant:
            return "StockpileRemnant";
            break;

        case StockpileEventType::StockpileRemoved:
            return "StockpileRemoved";
            break;

        case StockpileEventType::ReclaimTransferStart:
            return "ReclaimTransStart";
            break;

        case StockpileEventType::RemnantRemoved:
            return "RemnantRemoved";
            break;

        case StockpileEventType::ReclaimTransferComplete:
            return "ReclaimTransComp";
            break;

        case StockpileEventType::StackTransferComplete:
            return "StackTransComp";
            break;

        default:
            return "Invalid";
    }
}