/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include <string>

enum class ReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
    PostDoubleHandleReservedFail,
    PostDoubleHandleReservedSyncFail,
    PostReclaimReserved,
    PostReclaimReservedFail,
    PostReclaimReservedSyncFail,
    PreDoubleHandleReserved,
    PreDoubleHandleReservedFail,
    PreDoubleHandleReservedSyncFail,
    PreReclaimReserved,
    PreReclaimReservedFail,
    PreReclaimReservedSyncFail,
    WorkingDoubleHandle,
    WorkingDoubleHandleFail,
    WorkingDoubleHandleSyncFail,
    WorkingReclaim,
    WorkingReclaimFail,
    WorkingReclaimSyncFail,
    WrappedUp,
    Invalid
};