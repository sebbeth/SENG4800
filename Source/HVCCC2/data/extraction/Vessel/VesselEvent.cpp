/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#include "VesselEvent.h"

bool VesselEvent::hasBallast() const {
    switch (type) {
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::StartLoading:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::FullyLoaded:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasCargo() const {
    switch (type) {
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::FullyLoaded:
        case VesselEventType::StartLoading:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasNumcargoes() const {
    switch (type) {
        case VesselEventType::FullyLoaded:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasTerminalID() const {
    switch (type) {
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::FullyLoaded:
        case VesselEventType::StartLoading:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
        default:
            return false;
    }
}

bool VesselEvent::hasTime() const {
    switch (type) {
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::FullyLoaded:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::YardSpaceAllocated:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}