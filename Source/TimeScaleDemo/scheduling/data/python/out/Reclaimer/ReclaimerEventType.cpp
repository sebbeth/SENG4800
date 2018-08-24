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