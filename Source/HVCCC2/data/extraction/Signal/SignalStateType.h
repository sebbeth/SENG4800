/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:04:35.914436
 **/
#pragma once
#include <string>

enum class SignalStateType {
    Green,
    Red,
    Invalid
};

SignalStateType decodeSignalStateType(const std::string& enumeratorString);
std::string encodeSignalStateType(const SignalStateType& value);