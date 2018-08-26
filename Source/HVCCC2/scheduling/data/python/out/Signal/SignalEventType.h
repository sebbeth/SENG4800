#pragma once
#include <string>

enum class SignalEventType {
    StateChange,
    Invalid
};

SignalEventType decodeSignalEventType(const std::string& enumeratorString);