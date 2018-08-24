#pragma once
#include <string>

enum class StockpileEventType {
    ReclaimComplete,
    ReclaimStart,
    ReclaimTransferComplete,
    ReclaimTransferStart,
    RemnantRemoved,
    StackComplete,
    StackStart,
    StackTransferComplete,
    StackTransferStart,
    StockpileBuilt,
    StockpileCreated,
    StockpileRemnant,
    StockpileRemoved,
    Invalid
};

StockpileEventType decodeStockpileEventType(const std::string& enumeratorString);