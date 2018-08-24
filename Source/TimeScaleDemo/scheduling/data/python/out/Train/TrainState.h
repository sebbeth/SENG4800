#pragma once
#include <string>
#include "TrainEvent.h"
#include "TrainStateType.h"

class TrainState {
public:
    typedef TrainEvent AssociatedEvent;
    TrainStateType type;
    /* STUB: SOME OF THESE PROPERTIES MAY NOT BE PRESENT IN ANY OF THE STATES (OR MAY BE PRESENT IN ALL STATES BUT NOT IN ALL EVENTS); IT CANNOT BE DETERMINED PURELY PROGRAMMATICALLY */

    double amount;
    int cycleID;
    std::string depotID;
    std::string direction;
    std::string dumpStationID;
    std::string junctionID;
    std::string loadPointID;
    std::string maintenanceActivity;
    double plannedTime;
    std::string sectionID;
    std::string signalID;
    SignalStateType signalState;
    double speed;
    std::string terminalID;
    double time;
    std::string trackID;
    std::string trainID;
    std::string trainType;
    TrainState() = default;
    static TrainStateType determineNextType(TrainStateType stateType, TrainEventType eventType);
    template<class Archive>
    void serialize(Archive & archive);
};

template<class Archive>
void TrainState::serialize(Archive & archive) {
    archive(type, amount, cycleID, depotID, direction, dumpStationID, junctionID, loadPointID, maintenanceActivity, plannedTime, sectionID, signalID, signalState, speed, terminalID, time, trackID, trainID, trainType);
}