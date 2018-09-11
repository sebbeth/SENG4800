/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>

enum class SignalEventType {
    StateChange,
    Invalid
};

SignalEventType decodeSignalEventType(const std::string& enumeratorString);
std::string encodeSignalEventType(const SignalEventType& value);