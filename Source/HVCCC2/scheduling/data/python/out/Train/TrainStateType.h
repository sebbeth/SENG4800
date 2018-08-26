#pragma once
#include <string>

enum class TrainStateType {
    ArrivedDumpstation,
    ArrivedLoadpoint,
    Created,
    DepartedLoadpoint,
    DepartedTerminal,
    DumpCompleted,
    DumpStarted,
    EnteredTrack,
    HeadLeftTrack,
    LoadCompleted,
    LoadStarted,
    MaintenanceAttempted,
    MaintenanceCompleted,
    MaintenanceStarted,
    ReachedSignal,
    TailLeftTrack,
    WaitingEnd,
    WaitingForTracks,
    WaitingJunction,
    WaitingSignal,
    Invalid
};