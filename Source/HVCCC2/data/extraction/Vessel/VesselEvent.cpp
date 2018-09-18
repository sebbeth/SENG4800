/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:05:50.446537
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
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}

bool VesselEvent::hasCargo() const {
    switch (type) {
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::StartLoading:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}

bool VesselEvent::hasTerminalID() const {
    switch (type) {
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::StartLoading:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}

bool VesselEvent::hasTime() const {
    switch (type) {
        case VesselEventType::Created:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
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