/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#pragma once
#include <string>

enum class TerminalId {
    CCT,
    KTC,
    NCT,
    Invalid
};

TerminalId decodeTerminalId(const std::string& enumeratorString);
std::string encodeTerminalId(const TerminalId& value);
static const int TERMINAL_CODE_LENGTH = 3;
