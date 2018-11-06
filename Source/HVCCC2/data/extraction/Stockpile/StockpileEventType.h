/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class StockpileEventType {
    DedicatedStockpileCreated,
    ReclaimComplete,
    ReclaimStart,
    ReclaimTransferComplete,
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