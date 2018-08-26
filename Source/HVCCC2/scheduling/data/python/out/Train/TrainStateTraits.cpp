#include "TrainStateTraits.h"
    
TrainState StateTraits<TrainState>::initializeFromEvent(const TrainEvent& src) {
    /* STUB: REPLACE WITH LOGIC FOR GUESSING THE INITIAL STATE FROM THE EVENT */
    return {TrainStateType::Created, src.amount, src.cycleID, src.depotID, src.direction, src.dumpStationID, src.junctionID, src.loadPointID, src.maintenanceActivity, src.plannedTime, src.sectionID, src.signalID, src.signalState, src.speed, src.terminalID, src.time, src.trackID, src.trainID, src.trainType};
}

TrainState StateTraits<TrainState>::generateNextState(const TrainState& current, const TrainEvent& event) {
    /* STUB: FILL IN WITH LOGIC FOR UPDATING ALL THE ATTRIBUTES */
    TrainState result = initializeFromEvent(event);//remove this line if/when you do
    result.type = TrainState::determineNextType(current.type, event.type);
    if(event.hasAmount()) {
        result.amount = event.amount;
    }
    if(event.hasCycleID()) {
        result.cycleID = event.cycleID;
    }
    if(event.hasDepotID()) {
        result.depotID = event.depotID;
    }
    if(event.hasDirection()) {
        result.direction = event.direction;
    }
    if(event.hasDumpStationID()) {
        result.dumpStationID = event.dumpStationID;
    }
    if(event.hasJunctionID()) {
        result.junctionID = event.junctionID;
    }
    if(event.hasLoadPointID()) {
        result.loadPointID = event.loadPointID;
    }
    if(event.hasMaintenanceActivity()) {
        result.maintenanceActivity = event.maintenanceActivity;
    }
    if(event.hasPlannedTime()) {
        result.plannedTime = event.plannedTime;
    }
    if(event.hasSectionID()) {
        result.sectionID = event.sectionID;
    }
    if(event.hasSignalID()) {
        result.signalID = event.signalID;
    }
    if(event.hasSignalState()) {
        result.signalState = event.signalState;
    }
    if(event.hasSpeed()) {
        result.speed = event.speed;
    }
    if(event.hasTerminalID()) {
        result.terminalID = event.terminalID;
    }
    if(event.hasTime()) {
        result.time = event.time;
    }
    if(event.hasTrackID()) {
        result.trackID = event.trackID;
    }
    if(event.hasTrainID()) {
        result.trainID = event.trainID;
    }
    if(event.hasTrainType()) {
        result.trainType = event.trainType;
    }
    return result;
}