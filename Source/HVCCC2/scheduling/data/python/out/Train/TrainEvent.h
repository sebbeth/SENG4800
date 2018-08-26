#pragma once
#include <string>
#include "TrainEventType.h"

//forward declare a class to associate with the event
class TrainState;

#include "../Signal/SignalStateType.h"
class TrainEvent {
public:
    typedef TrainState AssociatedState;
    TrainEventType type;

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

    bool hasAmount() const;
    bool hasCycleID() const;
    bool hasDepotID() const;
    bool hasDirection() const;
    bool hasDumpStationID() const;
    bool hasJunctionID() const;
    bool hasLoadPointID() const;
    bool hasMaintenanceActivity() const;
    bool hasPlannedTime() const;
    bool hasSectionID() const;
    bool hasSignalID() const;
    bool hasSignalState() const;
    bool hasSpeed() const;
    bool hasTerminalID() const;
    bool hasTime() const;
    bool hasTrackID() const;
    bool hasTrainID() const;
    bool hasTrainType() const;

    template<class Archive>
    void serialize(Archive & archive);

    //STUB: INCLUDE A SPECIFIER FOR THE ID TYPE AND AN ID GETTER
};

template<class Archive>
void TrainEvent::serialize(Archive & archive) {
    archive(type, amount, cycleID, depotID, direction, dumpStationID, junctionID, loadPointID, maintenanceActivity, plannedTime, sectionID, signalID, signalState, speed, terminalID, time, trackID, trainID, trainType);
}