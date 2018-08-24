#pragma once
#include <string>

enum class StockpileStateType {
    Built,
    Created,
    Idle,
    Reclaiming,
    Remnant,
    RemnantReclaiming,
    RemnantStacking,
    Stacking,
    Invalid
};