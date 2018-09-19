/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-19 13:51:09.974486
 **/
#include "VesselState.h"

VesselStateType VesselState::determineNextType(VesselStateType stateType, VesselEventType eventType) {
    switch(stateType) {
        case VesselStateType::Idle:
            switch(eventType) {
                case VesselEventType::AtAnchorage:
                    return VesselStateType::WaitingForCoal;
                case VesselEventType::Created:
                    return VesselStateType::Idle;
                case VesselEventType::YardSpaceAllocated:
                    return VesselStateType::Idle;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::WaitingForCoal:
            switch(eventType) {
                case VesselEventType::WaitBerth:
                    return VesselStateType::WaitingForBerth;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::WaitingForBerth:
            switch(eventType) {
                case VesselEventType::WaitEnter:
                    return VesselStateType::WaitingToEnter;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::WaitingToEnter:
            switch(eventType) {
                case VesselEventType::EnterChannel:
                    return VesselStateType::TravellingToTerminal;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::TravellingToTerminal:
            switch(eventType) {
                case VesselEventType::ArriveTerminal:
                    return VesselStateType::Berthed;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::Berthed:
            switch(eventType) {
                case VesselEventType::StartLoading:
                    return VesselStateType::Loading;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::Loading:
            switch(eventType) {
                case VesselEventType::HatchChangeStart:
                    return VesselStateType::ChangingHatches;
                case VesselEventType::DraftSurveyStart:
                    return VesselStateType::InterimDraftSurvey;
                case VesselEventType::StopForDeballasting:
                    return VesselStateType::StoppedForDeballasting;
                case VesselEventType::FullyLoaded:
                    return VesselStateType::Loaded;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::ChangingHatches:
            switch(eventType) {
                case VesselEventType::HatchChangeComplete:
                    return VesselStateType::Loading;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::InterimDraftSurvey:
            switch(eventType) {
                case VesselEventType::DraftSurveyComplete:
                    return VesselStateType::Loading;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::StoppedForDeballasting:
            switch(eventType) {
                case VesselEventType::BallastTankEmpty:
                    return VesselStateType::StoppedForDeballasting;
                case VesselEventType::StopForDeballastingComplete:
                    return VesselStateType::Loading;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::Loaded:
            switch(eventType) {
                case VesselEventType::WaitSail:
                    return VesselStateType::WaitingToSail;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::WaitingToSail:
            switch(eventType) {
                case VesselEventType::DepartTerminal:
                    return VesselStateType::TravellingFromTerminal;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::TravellingFromTerminal:
            switch(eventType) {
                case VesselEventType::ExitChannel:
                    return VesselStateType::Exited;
                default:
                    return VesselStateType::Invalid;
            }
        case VesselStateType::Exited:
            return VesselStateType::Invalid;
        default:
            return VesselStateType::Invalid;
    }
}