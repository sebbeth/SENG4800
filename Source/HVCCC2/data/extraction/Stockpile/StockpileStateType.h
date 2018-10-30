/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class StockpileStateType {
    Built,
    Created,
    DeciatedReclaiming,
    DedicatedCreated,
    DedicatedReclaiming,
    DedicatedStacking,
    Idle,
    Reclaimed,
    Reclaiming,
    Remnant,
    RemnantReclaiming,
    RemnantStacking,
    Stacking,
    StackingBuilt,
    Invalid
};

StockpileStateType decodeStockpileStateType(const std::string& enumeratorString);
std::string encodeStockpileStateType(const StockpileStateType& value);