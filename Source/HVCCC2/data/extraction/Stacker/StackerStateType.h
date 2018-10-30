/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#pragma once
#include <string>

enum class StackerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
    PostDoubleHandleReservedFail,
    PostDoubleHandleReservedSyncFail,
    PostStackReserved,
    PostStackReservedFail,
    PostStackReservedSyncFail,
    PreDoubleHandleReserved,
    PreDoubleHandleReservedFail,
    PreDoubleHandleReservedSyncFail,
    PreStackReserved,
    PreStackReservedFail,
    PreStackReservedSyncFail,
    WorkingDoubleHandle,
    WorkingDoubleHandleFail,
    WorkingDoubleHandleSyncFail,
    WorkingStack,
    WorkingStackFail,
    WorkingStackSyncFail,
    WrappedUp,
    Invalid
};

StackerStateType decodeStackerStateType(const std::string& enumeratorString);
std::string encodeStackerStateType(const StackerStateType& value);