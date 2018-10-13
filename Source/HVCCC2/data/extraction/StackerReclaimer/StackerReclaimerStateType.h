/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#pragma once
#include <string>

enum class StackerReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
    PostDoubleHandleReservedFail,
    PostDoubleHandleReservedSyncFail,
    PostReclaimReserved,
    PostReclaimReservedFail,
    PostReclaimReservedSyncFail,
    PostStackReserved,
    PostStackReservedFail,
    PostStackReservedSyncFail,
    PreDoubleHandleReserved,
    PreDoubleHandleReservedFail,
    PreDoubleHandleReservedSyncFail,
    PreReclaimReserved,
    PreReclaimReservedFail,
    PreReclaimReservedSyncFail,
    PreStackReserved,
    PreStackReservedFail,
    PreStackReservedSyncFail,
    WorkingDoubleHandle,
    WorkingDoubleHandleFail,
    WorkingDoubleHandleSyncFail,
    WorkingReclaim,
    WorkingReclaimFail,
    WorkingReclaimSyncFail,
    WorkingStack,
    WorkingStackFail,
    WorkingStackSyncFail,
    WrappedUp,
    Invalid
};

std::string encodeStackerReclaimerStateType(const StackerReclaimerStateType& value);