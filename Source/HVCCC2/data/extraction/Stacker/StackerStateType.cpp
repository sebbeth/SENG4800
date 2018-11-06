/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StackerStateType.h"
        
StackerStateType decodeStackerStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return StackerStateType::Idle;
    } else if (enumeratorString == "Maintenance") {
        return StackerStateType::Maintenance;
    } else if (enumeratorString == "Moving") {
        return StackerStateType::Moving;
    } else if (enumeratorString == "PostStackDoubleHandleReserved") {
        return StackerStateType::PostStackDoubleHandleReserved;
    } else if (enumeratorString == "PostStackDoubleHandleReservedFail") {
        return StackerStateType::PostStackDoubleHandleReservedFail;
    } else if (enumeratorString == "PostStackDoubleHandleReservedSyncFail") {
        return StackerStateType::PostStackDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PostStackReserved") {
        return StackerStateType::PostStackReserved;
    } else if (enumeratorString == "PostStackReservedFail") {
        return StackerStateType::PostStackReservedFail;
    } else if (enumeratorString == "PostStackReservedSyncFail") {
        return StackerStateType::PostStackReservedSyncFail;
    } else if (enumeratorString == "PreStackDoubleHandleReserved") {
        return StackerStateType::PreStackDoubleHandleReserved;
    } else if (enumeratorString == "PreStackDoubleHandleReservedFail") {
        return StackerStateType::PreStackDoubleHandleReservedFail;
    } else if (enumeratorString == "PreStackDoubleHandleReservedSyncFail") {
        return StackerStateType::PreStackDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PreStackReserved") {
        return StackerStateType::PreStackReserved;
    } else if (enumeratorString == "PreStackReservedFail") {
        return StackerStateType::PreStackReservedFail;
    } else if (enumeratorString == "PreStackReservedSyncFail") {
        return StackerStateType::PreStackReservedSyncFail;
    } else if (enumeratorString == "WorkingStack") {
        return StackerStateType::WorkingStack;
    } else if (enumeratorString == "WorkingStackDoubleHandle") {
        return StackerStateType::WorkingStackDoubleHandle;
    } else if (enumeratorString == "WorkingStackDoubleHandleFail") {
        return StackerStateType::WorkingStackDoubleHandleFail;
    } else if (enumeratorString == "WorkingStackDoubleHandleSyncFail") {
        return StackerStateType::WorkingStackDoubleHandleSyncFail;
    } else if (enumeratorString == "WorkingStackFail") {
        return StackerStateType::WorkingStackFail;
    } else if (enumeratorString == "WorkingStackSyncFail") {
        return StackerStateType::WorkingStackSyncFail;
    } else if (enumeratorString == "WrappedUp") {
        return StackerStateType::WrappedUp;
    } else {
        return StackerStateType::Invalid;
    }
}
std::string encodeStackerStateType(const StackerStateType& value) {
    switch(value) {
        case StackerStateType::Idle:
            return "Idle";
            break;

        case StackerStateType::PreStackReserved:
            return "PreStackReserved";
            break;

        case StackerStateType::PreStackDoubleHandleReserved:
            return "PreStackDoubleHandleReserved";
            break;

        case StackerStateType::Moving:
            return "Moving";
            break;

        case StackerStateType::Maintenance:
            return "Maintenance";
            break;

        case StackerStateType::WrappedUp:
            return "WrappedUp";
            break;

        case StackerStateType::WorkingStack:
            return "WorkingStack";
            break;

        case StackerStateType::PreStackReservedFail:
            return "PreStackReservedFail";
            break;

        case StackerStateType::PreStackReservedSyncFail:
            return "PreStackReservedSyncFail";
            break;

        case StackerStateType::PostStackReserved:
            return "PostStackReserved";
            break;

        case StackerStateType::WorkingStackFail:
            return "WorkingStackFail";
            break;

        case StackerStateType::WorkingStackSyncFail:
            return "WorkingStackSyncFail";
            break;

        case StackerStateType::PostStackReservedFail:
            return "PostStackReservedFail";
            break;

        case StackerStateType::PostStackReservedSyncFail:
            return "PostStackReservedSyncFail";
            break;

        case StackerStateType::PreStackDoubleHandleReservedFail:
            return "PreStackDoubleHandleReservedFail";
            break;

        case StackerStateType::PreStackDoubleHandleReservedSyncFail:
            return "PreStackDoubleHandleReservedSyncFail";
            break;

        case StackerStateType::WorkingStackDoubleHandle:
            return "WorkingStackDoubleHandle";
            break;

        case StackerStateType::PostStackDoubleHandleReserved:
            return "PostStackDoubleHandleReserved";
            break;

        case StackerStateType::WorkingStackDoubleHandleFail:
            return "WorkingStackDoubleHandleFail";
            break;

        case StackerStateType::WorkingStackDoubleHandleSyncFail:
            return "WorkingStackDoubleHandleSyncFail";
            break;

        case StackerStateType::PostStackDoubleHandleReservedFail:
            return "PostStackDoubleHandleReservedFail";
            break;

        case StackerStateType::PostStackDoubleHandleReservedSyncFail:
            return "PostStackDoubleHandleReservedSyncFail";
            break;

        default:
            return "Invalid";
    }
}