/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-08 19:15:43.572274
 **/
#include "ReclaimerEventType.h"
        
ReclaimerEventType decodeReclaimerEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Comp") {
        return ReclaimerEventType::Complete;
    } else if (enumeratorString == "DoubleHandleComp") {
        return ReclaimerEventType::DoubleHandleComplete;
    } else if (enumeratorString == "DoubleHandleOpComp") {
        return ReclaimerEventType::DoubleHandleOperationComplete;
    } else if (enumeratorString == "DoubleHandleOpStart") {
        return ReclaimerEventType::DoubleHandleOperationStart;
    } else if (enumeratorString == "DoubleHandleStart") {
        return ReclaimerEventType::DoubleHandleStart;
    } else if (enumeratorString == "Fail") {
        return ReclaimerEventType::Fail;
    } else if (enumeratorString == "Fix") {
        return ReclaimerEventType::Fix;
    } else if (enumeratorString == "MaintComp") {
        return ReclaimerEventType::MaintenanceComplete;
    } else if (enumeratorString == "MaintStart") {
        return ReclaimerEventType::MaintenanceStart;
    } else if (enumeratorString == "OnMove") {
        return ReclaimerEventType::OnMove;
    } else if (enumeratorString == "OnStopMove") {
        return ReclaimerEventType::OnStopMove;
    } else if (enumeratorString == "OpComp") {
        return ReclaimerEventType::OperationComplete;
    } else if (enumeratorString == "OpStart") {
        return ReclaimerEventType::OperationStart;
    } else if (enumeratorString == "Start") {
        return ReclaimerEventType::Start;
    } else if (enumeratorString == "SyncedFail") {
        return ReclaimerEventType::SyncedFail;
    } else if (enumeratorString == "SyncedFix") {
        return ReclaimerEventType::SyncedFix;
    } else if (enumeratorString == "WrapUp") {
        return ReclaimerEventType::WrapUp;
    } else {
        return ReclaimerEventType::Invalid;
    }
}
std::string encodeReclaimerEventType(const ReclaimerEventType& value) {
    switch(value) {
        case ReclaimerEventType::OperationStart:
            return "OpStart";
            break;

        case ReclaimerEventType::DoubleHandleOperationStart:
            return "DoubleHandleOpStart";
            break;

        case ReclaimerEventType::OnMove:
            return "OnMove";
            break;

        case ReclaimerEventType::MaintenanceStart:
            return "MaintStart";
            break;

        case ReclaimerEventType::WrapUp:
            return "WrapUp";
            break;

        case ReclaimerEventType::MaintenanceComplete:
            return "MaintComp";
            break;

        case ReclaimerEventType::OnStopMove:
            return "OnStopMove";
            break;

        case ReclaimerEventType::Start:
            return "Start";
            break;

        case ReclaimerEventType::Fail:
            return "Fail";
            break;

        case ReclaimerEventType::SyncedFail:
            return "SyncedFail";
            break;

        case ReclaimerEventType::Fix:
            return "Fix";
            break;

        case ReclaimerEventType::SyncedFix:
            return "SyncedFix";
            break;

        case ReclaimerEventType::Complete:
            return "Comp";
            break;

        case ReclaimerEventType::OperationComplete:
            return "OpComp";
            break;

        case ReclaimerEventType::DoubleHandleStart:
            return "DoubleHandleStart";
            break;

        case ReclaimerEventType::DoubleHandleComplete:
            return "DoubleHandleComp";
            break;

        case ReclaimerEventType::DoubleHandleOperationComplete:
            return "DoubleHandleOpComp";
            break;

        default:
            return "Invalid";
    }
}