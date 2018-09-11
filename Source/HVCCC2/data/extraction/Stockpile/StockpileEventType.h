/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#pragma once
#include <string>

enum class StockpileEventType {
    DedicatedStockpileCreated,
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
std::string encodeStockpileEventType(const StockpileEventType& value);