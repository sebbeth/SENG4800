#include "VesselState.h"

VesselStateType VesselState::determineNextType(VesselStateType stateType, VesselEventType eventType) {
    switch(eventType) {
        case VesselEventType::ArriveTerminal:
            switch(stateType) {
                case VesselStateType::TravellingToTerminal:
                    return VesselStateType::Berthed;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::AtAnchorage:
            switch(stateType) {
                case VesselStateType::Idle:
                    return VesselStateType::WaitingForCoal;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::DepartTerminal:
            switch(stateType) {
                case VesselStateType::WaitingToSail:
                    return VesselStateType::TravellingFromTerminal;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::EnterChannel:
            switch(stateType) {
                case VesselStateType::WaitingToEnter:
                    return VesselStateType::TravellingToTerminal;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::ExitChannel:
            switch(stateType) {
                case VesselStateType::TravellingFromTerminal:
                    return VesselStateType::Exited;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::MoveToSwingBasin:
            switch(stateType) {
                case VesselStateType::Exited:
                    return VesselStateType::Invalid;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::WaitBerth:
            switch(stateType) {
                case VesselStateType::WaitingForCoal:
                    return VesselStateType::WaitingForBerth;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::WaitEnter:
            switch(stateType) {
                case VesselStateType::WaitingForBerth:
                    return VesselStateType::WaitingToEnter;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::WaitSail:
            switch(stateType) {
                case VesselStateType::Berthed:
                    return VesselStateType::WaitingToSail;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselEventType::YardSpaceAllocated:
            switch(stateType) {
                case VesselStateType::NA:
                    return VesselStateType::NA;
                default:
                    return VesselStateType::Invalid;
            }
        default:
            return VesselStateType::Invalid;
    }
}