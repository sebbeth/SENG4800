/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#pragma once
#include <string>

enum class StackerReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
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
    Invalid
};

std::string encodeStackerReclaimerStateType(const StackerReclaimerStateType& value);