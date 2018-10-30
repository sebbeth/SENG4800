/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class StockpileEventType {
    DedicatedStockpileCreated,
    ReclaimComplete,
    ReclaimStart,
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