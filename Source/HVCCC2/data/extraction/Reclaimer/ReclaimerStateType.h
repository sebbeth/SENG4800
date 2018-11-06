/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#pragma once
#include <string>

enum class ReclaimerStateType {
    Idle,
    Maintenance,
    Moving,
    PostReclaimDoubleHandleReserved,
    PostReclaimDoubleHandleReservedFail,
    PostReclaimDoubleHandleReservedSyncFail,
    PostReclaimReserved,
    PostReclaimReservedFail,
    PostReclaimReservedSyncFail,
    PreReclaimDoubleHandleReserved,
    PreReclaimDoubleHandleReservedFail,
    PreReclaimDoubleHandleReservedSyncFail,
    PreReclaimReserved,
    PreReclaimReservedFail,
    PreReclaimReservedSyncFail,
    WorkingReclaim,
    WorkingReclaimDoubleHandle,
    WorkingReclaimDoubleHandleFail,
    WorkingReclaimDoubleHandleSyncFail,
    WorkingReclaimFail,
    WorkingReclaimSyncFail,
    WrappedUp,
    Invalid
};

ReclaimerStateType decodeReclaimerStateType(const std::string& enumeratorString);
std::string encodeReclaimerStateType(const ReclaimerStateType& value);