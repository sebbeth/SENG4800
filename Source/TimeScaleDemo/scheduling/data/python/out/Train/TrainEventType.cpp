#include "TrainEventType.h"

TrainEventType decodeTrainEventType(const std::string& enumeratorString) {
    if (enumeratorString == "ArrivedDumpstation") {
        return TrainEventType::ArrivedDumpstation;
    } else if (enumeratorString == "ArrivedLoadpoint") {
        return TrainEventType::ArrivedLoadpoint;
    } else if (enumeratorString == "Created") {
        return TrainEventType::Created;
    } else if (enumeratorString == "DepartLoadpoint") {
        return TrainEventType::DepartLoadpoint;
    } else if (enumeratorString == "DepartTerminal") {
        return TrainEventType::DepartTerminal;
    } else if (enumeratorString == "DumpComp") {
        return TrainEventType::DumpComplete;
    } else if (enumeratorString == "DumpStart") {
        return TrainEventType::DumpStart;
    } else if (enumeratorString == "EnterTrack") {
        return TrainEventType::EnterTrack;
    } else if (enumeratorString == "HeadLeaveTrack") {
        return TrainEventType::HeadLeaveTrack;
    } else if (enumeratorString == "LoadComp") {
        return TrainEventType::LoadComplete;
    } else if (enumeratorString == "LoadStart") {
        return TrainEventType::LoadStart;
    } else if (enumeratorString == "MaintAttempted") {
        return TrainEventType::MaintenanceAttempted;
    } else if (enumeratorString == "MaintCompleted") {
        return TrainEventType::MaintenanceCompleted;
    } else if (enumeratorString == "MaintStart") {
        return TrainEventType::MaintenanceStart;
    } else if (enumeratorString == "ReachedSignal") {
        return TrainEventType::ReachedSignal;
    } else if (enumeratorString == "TailLeaveTrack") {
        return TrainEventType::TailLeaveTrack;
    } else if (enumeratorString == "WaitEnd") {
        return TrainEventType::WaitEnd;
    } else if (enumeratorString == "WaitForTracks") {
        return TrainEventType::WaitForTracks;
    } else if (enumeratorString == "WaitJunction") {
        return TrainEventType::WaitJunction;
    } else if (enumeratorString == "WaitSignal") {
        return TrainEventType::WaitSignal;
    } else {
        return TrainEventType::Invalid;
    }
}