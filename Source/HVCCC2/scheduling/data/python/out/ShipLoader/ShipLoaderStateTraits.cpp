#include "ShipLoaderStateTraits.h"
    
ShipLoaderState StateTraits<ShipLoaderState>::initializeFromEvent(const ShipLoaderEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {ShipLoaderStateType::Idle, src.amount, src.position, src.shipLoaderID, src.stockpileID, src.time, src.vesselID};
}

ShipLoaderState StateTraits<ShipLoaderState>::generateNextState(const ShipLoaderState& current, const ShipLoaderEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    ShipLoaderState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = ShipLoaderState::determineNextType(current.type, event.type);
    if(event.hasAmount()) {
        result.amount = event.amount;
    }
    if(event.hasPosition()) {
        result.position = event.position;
    }
    if(event.hasShipLoaderID()) {
        result.shipLoaderID = event.shipLoaderID;
    }
    if(event.hasStockpileID()) {
        result.stockpileID = event.stockpileID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    if(event.hasVesselID()) {
        result.vesselID = event.vesselID;
    }
    return result;
}