/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-30 21:30:03.549963
 **/
#include "StackerStateType.h"
        
StackerStateType decodeStackerStateType(const std::string& enumeratorString) {
    if (enumeratorString == "Idle") {
        return StackerStateType::Idle;
    } else if (enumeratorString == "Maintenance") {
        return StackerStateType::Maintenance;
    } else if (enumeratorString == "Moving") {
        return StackerStateType::Moving;
    } else if (enumeratorString == "PostDoubleHandleReserved") {
        return StackerStateType::PostDoubleHandleReserved;
    } else if (enumeratorString == "PostDoubleHandleReservedFail") {
        return StackerStateType::PostDoubleHandleReservedFail;
    } else if (enumeratorString == "PostDoubleHandleReservedSyncFail") {
        return StackerStateType::PostDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PostStackReserved") {
        return StackerStateType::PostStackReserved;
    } else if (enumeratorString == "PostStackReservedFail") {
        return StackerStateType::PostStackReservedFail;
    } else if (enumeratorString == "PostStackReservedSyncFail") {
        return StackerStateType::PostStackReservedSyncFail;
    } else if (enumeratorString == "PreDoubleHandleReserved") {
        return StackerStateType::PreDoubleHandleReserved;
    } else if (enumeratorString == "PreDoubleHandleReservedFail") {
        return StackerStateType::PreDoubleHandleReservedFail;
    } else if (enumeratorString == "PreDoubleHandleReservedSyncFail") {
        return StackerStateType::PreDoubleHandleReservedSyncFail;
    } else if (enumeratorString == "PreStackReserved") {
        return StackerStateType::PreStackReserved;
    } else if (enumeratorString == "PreStackReservedFail") {
        return StackerStateType::PreStackReservedFail;
    } else if (enumeratorString == "PreStackReservedSyncFail") {
        return StackerStateType::PreStackReservedSyncFail;
    } else if (enumeratorString == "WorkingDoubleHandle") {
        return StackerStateType::WorkingDoubleHandle;
    } else if (enumeratorString == "WorkingDoubleHandleFail") {
        return StackerStateType::WorkingDoubleHandleFail;
    } else if (enumeratorString == "WorkingDoubleHandleSyncFail") {
        return StackerStateType::WorkingDoubleHandleSyncFail;
    } else if (enumeratorString == "WorkingStack") {
        return StackerStateType::WorkingStack;
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

        case StackerStateType::PreDoubleHandleReserved:
            return "PreDoubleHandleReserved";
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

        case StackerStateType::PreDoubleHandleReservedFail:
            return "PreDoubleHandleReservedFail";
            break;

        case StackerStateType::PreDoubleHandleReservedSyncFail:
            return "PreDoubleHandleReservedSyncFail";
            break;

        case StackerStateType::WorkingDoubleHandle:
            return "WorkingDoubleHandle";
            break;

        case StackerStateType::PostDoubleHandleReserved:
            return "PostDoubleHandleReserved";
            break;

        case StackerStateType::WorkingDoubleHandleFail:
            return "WorkingDoubleHandleFail";
            break;

        case StackerStateType::WorkingDoubleHandleSyncFail:
            return "WorkingDoubleHandleSyncFail";
            break;

        case StackerStateType::PostDoubleHandleReservedFail:
            return "PostDoubleHandleReservedFail";
            break;

        case StackerStateType::PostDoubleHandleReservedSyncFail:
            return "PostDoubleHandleReservedSyncFail";
            break;

        default:
            return "Invalid";
    }
}