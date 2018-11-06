/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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