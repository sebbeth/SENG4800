/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "StackerEventType.h"
        
StackerEventType decodeStackerEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Comp") {
        return StackerEventType::Complete;
    } else if (enumeratorString == "Fail") {
        return StackerEventType::Fail;
    } else if (enumeratorString == "Fix") {
        return StackerEventType::Fix;
    } else if (enumeratorString == "MaintComp") {
        return StackerEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return StackerEventType::MaintenanceStart;
    } else if (enumeratorString == "OnMove") {
        return StackerEventType::OnMove;
    } else if (enumeratorString == "OnStopMove") {
        return StackerEventType::OnStopMove;
    } else if (enumeratorString == "OpComp") {
        return StackerEventType::OperationComplete;
    } else if (enumeratorString == "OpStart") {
        return StackerEventType::OperationStart;
    } else if (enumeratorString == "StackDoubleHandleComp") {
        return StackerEventType::StackDoubleHandleComplete;
    } else if (enumeratorString == "StackDoubleHandleOpComp") {
        return StackerEventType::StackDoubleHandleOperationComplete;
    } else if (enumeratorString == "StackDoubleHandleOpStart") {
        return StackerEventType::StackDoubleHandleOperationStart;
    } else if (enumeratorString == "StackDoubleHandleStart") {
        return StackerEventType::StackDoubleHandleStart;
    } else if (enumeratorString == "Start") {
        return StackerEventType::Start;
    } else if (enumeratorString == "SyncedFail") {
        return StackerEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return StackerEventType::SyncedFix;
    } else if (enumeratorString == "WrapUp") {
        return StackerEventType::WrapUp;
    } else {
        return StackerEventType::Invalid;
    }
}
std::string encodeStackerEventType(const StackerEventType& value) {
    switch(value) {
        case StackerEventType::OperationStart:
            return "OpStart";
            break;

        case StackerEventType::StackDoubleHandleOperationStart:
            return "StackDoubleHandleOpStart";
            break;

        case StackerEventType::OnMove:
            return "OnMove";
            break;

        case StackerEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case StackerEventType::WrapUp:
            return "WrapUp";
            break;

        case StackerEventType::MaintenanceComplete:
            return "MaintComp";
            break;

        case StackerEventType::OnStopMove:
            return "OnStopMove";
            break;

        case StackerEventType::Start:
            return "Start";
            break;

        case StackerEventType::Fail:
            return "Fail";
            break;

        case StackerEventType::SyncedFail:
            return "SyncedFail";
            break;

        case StackerEventType::Fix:
            return "Fix";
            break;

        case StackerEventType::SyncedFix:
            return "SyncedFix";
            break;

        case StackerEventType::Complete:
            return "Comp";
            break;

        case StackerEventType::OperationComplete:
            return "OpComp";
            break;

        case StackerEventType::StackDoubleHandleStart:
            return "StackDoubleHandleStart";
            break;

        case StackerEventType::StackDoubleHandleComplete:
            return "StackDoubleHandleComp";
            break;

        case StackerEventType::StackDoubleHandleOperationComplete:
            return "StackDoubleHandleOpComp";
            break;

        default:
            return "Invalid";
    }
}