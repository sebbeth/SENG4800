/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#pragma once
#include <string>

enum class TerminalId {
    CCT,
    KCT,
    NCT,
    Invalid
};

TerminalId decodeTerminalId(const std::string& enumeratorString);
std::string encodeTerminalId(const TerminalId& value);
static const int TERMINAL_CODE_LENGTH = 3;
