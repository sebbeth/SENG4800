/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
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