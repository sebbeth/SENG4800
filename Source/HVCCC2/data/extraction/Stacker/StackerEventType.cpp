/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 23:08:55.254916
 **/
#include "StackerEventType.h"
        
StackerEventType decodeStackerEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Comp") {
        return StackerEventType::Complete;
    } else if (enumeratorString == "DoubleHandleComp") {
        return StackerEventType::DoubleHandleComplete;
    } else if (enumeratorString == "DoubleHandleOpStart") {
        return StackerEventType::DoubleHandleOperationStart;
    } else if (enumeratorString == "DoubleHandleStart") {
        return StackerEventType::DoubleHandleStart;
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
    } else if (enumeratorString == "Start") {
        return StackerEventType::Start;
    } else if (enumeratorString == "SyncedFail") {
        return StackerEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return StackerEventType::SyncedFix;
    } else {
        return StackerEventType::Invalid;
    }
}
std::string encodeStackerEventType(const StackerEventType& value) {
    switch(value) {
        case StackerEventType::OperationStart:
            return "OpStart";
            break;

        case StackerEventType::DoubleHandleOperationStart:
            return "DoubleHandleOpStart";
            break;

        case StackerEventType::OnMove:
            return "OnMove";
            break;

        case StackerEventType::MaintenanceStart:
            return "MaintStart";
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

        case StackerEventType::DoubleHandleStart:
            return "DoubleHandleStart";
            break;

        case StackerEventType::DoubleHandleComplete:
            return "DoubleHandleComp";
            break;

        default:
            return "Invalid";
    }
}