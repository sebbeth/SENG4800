#include "StockpileEventType.h"

StockpileEventType decodeStockpileEventType(const std::string& enumeratorString) {
    if (enumeratorString == "ReclaimComp") {
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