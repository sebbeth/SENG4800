#pragma once
#include <string>

enum class TrainEventType {
    ArrivedDumpstation,
    ArrivedLoadpoint,
    Created,
    DepartLoadpoint,
    DepartTerminal,
    DumpComplete,
    DumpStart,
    EnterTrack,
    HeadLeaveTrack,
    LoadComplete,
    LoadStart,
    MaintenanceAttempted,
    MaintenanceCompleted,
    MaintenanceStart,
    ReachedSignal,
    TailLeaveTrack,
    WaitEnd,
    WaitForTracks,
    WaitJunction,
    WaitSignal,
    Invalid
};

TrainEventType decodeTrainEventType(const std::string& enumeratorString);