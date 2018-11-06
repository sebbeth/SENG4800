/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class StackerStateType {
    Idle,
    Maintenance,
    Moving,
    PostStackDoubleHandleReserved,
    PostStackDoubleHandleReservedFail,
    PostStackDoubleHandleReservedSyncFail,
    PostStackReserved,
    PostStackReservedFail,
    PostStackReservedSyncFail,
    PreStackDoubleHandleReserved,
    PreStackDoubleHandleReservedFail,
    PreStackDoubleHandleReservedSyncFail,
    PreStackReserved,
    PreStackReservedFail,
    PreStackReservedSyncFail,
    WorkingStack,
    WorkingStackDoubleHandle,
    WorkingStackDoubleHandleFail,
    WorkingStackDoubleHandleSyncFail,
    WorkingStackFail,
    WorkingStackSyncFail,
    WrappedUp,
    Invalid
};

StackerStateType decodeStackerStateType(const std::string& enumeratorString);
std::string encodeStackerStateType(const StackerStateType& value);