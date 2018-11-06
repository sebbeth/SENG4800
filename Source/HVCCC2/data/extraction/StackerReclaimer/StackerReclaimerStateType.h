/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class StackerReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostReclaimDoubleHandleReserved,
    PostReclaimDoubleHandleReservedFail,
    PostReclaimDoubleHandleReservedSyncFail,
    PostReclaimReserved,
    PostReclaimReservedFail,
    PostReclaimReservedSyncFail,
    PostStackDoubleHandleReserved,
    PostStackDoubleHandleReservedFail,
    PostStackDoubleHandleReservedSyncFail,
    PostStackReserved,
    PostStackReservedFail,
    PostStackReservedSyncFail,
    PreReclaimDoubleHandleReserved,
    PreReclaimDoubleHandleReservedFail,
    PreReclaimDoubleHandleReservedSyncFail,
    PreReclaimReserved,
    PreReclaimReservedFail,
    PreReclaimReservedSyncFail,
    PreStackDoubleHandleReserved,
    PreStackDoubleHandleReservedFail,
    PreStackDoubleHandleReservedSyncFail,
    PreStackReserved,
    PreStackReservedFail,
    PreStackReservedSyncFail,
    WorkingReclaim,
    WorkingReclaimDoubleHandle,
    WorkingReclaimDoubleHandleFail,
    WorkingReclaimDoubleHandleSyncFail,
    WorkingReclaimFail,
    WorkingReclaimSyncFail,
    WorkingStack,
    WorkingStackDoubleHandle,
    WorkingStackDoubleHandleFail,
    WorkingStackDoubleHandleSyncFail,
    WorkingStackFail,
    WorkingStackSyncFail,
    WrappedUp,
    Invalid
};

std::string encodeStackerReclaimerStateType(const StackerReclaimerStateType& value);