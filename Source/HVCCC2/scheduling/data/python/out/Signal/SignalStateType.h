#pragma once
#include <string>

enum class SignalStateType {
    Green,
    Red,
    Invalid
};

SignalStateType decodeSignalStateType(const std::string& enumeratorString);