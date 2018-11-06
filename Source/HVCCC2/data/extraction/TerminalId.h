/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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
