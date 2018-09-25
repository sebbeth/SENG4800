/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-16 23:45:48.882521
 **/
#pragma once
#include <string>

enum class ReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostDoubleHandleReserved,
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
    Invalid
};