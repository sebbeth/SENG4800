#include "StackerEventType.h"

StackerEventType decodeStackerEventType(const std::string& enumeratorString) {
    if (enumeratorString == "Comp") {
        return StackerEventType::Complete;
    } else if (enumeratorString == "DoubleHandleComp") {
        return StackerEventType::DoubleHandleComplete;
    } else if (enumeratorString == "DoubleHandleOpComp") {
        return StackerEventType::DoubleHandleOperationComplete;
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
    } else if (enumeratorString == "WrapUp") {
        return StackerEventType::WrapUp;
    } else {
        return StackerEventType::Invalid;
    }
}