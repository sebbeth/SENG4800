/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StockpileStateType.h"
        
StockpileStateType decodeStockpileStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Built") {
        return StockpileStateType::Built;
    } else if (enumeratorString == "Created") {
        return StockpileStateType::Created;
    } else if (enumeratorString == "DeciatedReclaiming") {
        return StockpileStateType::DeciatedReclaiming;
    } else if (enumeratorString == "DedicatedCreated") {
        return StockpileStateType::DedicatedCreated;
    } else if (enumeratorString == "DedicatedReclaiming") {
        return StockpileStateType::DedicatedReclaiming;
    } else if (enumeratorString == "DedicatedStacking") {
        return StockpileStateType::DedicatedStacking;
    } else if (enumeratorString == "Idle") {
        return StockpileStateType::Idle;
    } else if (enumeratorString == "Reclaimed") {
        return StockpileStateType::Reclaimed;
    } else if (enumeratorString == "Reclaiming") {
        return StockpileStateType::Reclaiming;
    } else if (enumeratorString == "Remnant") {
        return StockpileStateType::Remnant;
    } else if (enumeratorString == "RemnantReclaiming") {
        return StockpileStateType::RemnantReclaiming;
    } else if (enumeratorString == "RemnantStacking") {
        return StockpileStateType::RemnantStacking;
    } else if (enumeratorString == "Stacking") {
        return StockpileStateType::Stacking;
    } else if (enumeratorString == "StackingBuilt") {
        return StockpileStateType::StackingBuilt;
    } else {
        return StockpileStateType::Invalid;
    }
}
std::string encodeStockpileStateType(const StockpileStateType& value) {
    switch(value) {
        case StockpileStateType::Idle:
            return "Idle";
            break;

        case StockpileStateType::Built:
            return "Built";
            break;

        case StockpileStateType::StackingBuilt:
            return "StackingBuilt";
            break;

        case StockpileStateType::Reclaiming:
            return "Reclaiming";
            break;

        case StockpileStateType::Created:
            return "Created";
            break;

        case StockpileStateType::Stacking:
            return "Stacking";
            break;

        case StockpileStateType::DeciatedReclaiming:
            return "DeciatedReclaiming";
            break;

        case StockpileStateType::DedicatedCreated:
            return "DedicatedCreated";
            break;

        case StockpileStateType::DedicatedReclaiming:
            return "DedicatedReclaiming";
            break;

        case StockpileStateType::RemnantStacking:
            return "RemnantStacking";
            break;

        case StockpileStateType::DedicatedStacking:
            return "DedicatedStacking";
            break;

        case StockpileStateType::Reclaimed:
            return "Reclaimed";
            break;

        case StockpileStateType::Remnant:
            return "Remnant";
            break;

        case StockpileStateType::RemnantReclaiming:
            return "RemnantReclaiming";
            break;

        default:
            return "Invalid";
    }
}