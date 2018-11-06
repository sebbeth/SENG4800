/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "ReclaimerEventType.h"
        
ReclaimerEventType decodeReclaimerEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Comp") {
        return ReclaimerEventType::Complete;
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
    } else if (enumeratorString == "ReclaimDoubleHandleComp") {
        return ReclaimerEventType::ReclaimDoubleHandleComplete;
    } else if (enumeratorString == "ReclaimDoubleHandleOpComp") {
        return ReclaimerEventType::ReclaimDoubleHandleOperationComplete;
    } else if (enumeratorString == "ReclaimDoubleHandleOpStart") {
        return ReclaimerEventType::ReclaimDoubleHandleOperationStart;
    } else if (enumeratorString == "ReclaimDoubleHandleStart") {
        return ReclaimerEventType::ReclaimDoubleHandleStart;
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

        case ReclaimerEventType::ReclaimDoubleHandleOperationStart:
            return "ReclaimDoubleHandleOpStart";
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

        case ReclaimerEventType::ReclaimDoubleHandleStart:
            return "ReclaimDoubleHandleStart";
            break;

        case ReclaimerEventType::ReclaimDoubleHandleComplete:
            return "ReclaimDoubleHandleComp";
            break;

        case ReclaimerEventType::ReclaimDoubleHandleOperationComplete:
            return "ReclaimDoubleHandleOpComp";
            break;

        default:
            return "Invalid";
    }
}