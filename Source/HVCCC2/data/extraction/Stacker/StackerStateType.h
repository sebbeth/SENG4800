/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#pragma once
#include <string>

enum class StackerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
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
    Invalid
};