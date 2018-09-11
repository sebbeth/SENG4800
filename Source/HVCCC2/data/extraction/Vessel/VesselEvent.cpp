/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-10 19:35:46.474699
 **/
#include "VesselEvent.h"

bool VesselEvent::hasIsTidal() const {
    switch (type) {
        case VesselEventType::WaitEnter:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}

bool VesselEvent::hasMetermark() const {
    switch (type) {
        case VesselEventType::ArriveTerminal:
            return true;
        case VesselEventType::AtAnchorage:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
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
        case VesselEventType::AtAnchorage:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::Created:
        case VesselEventType::DepartTerminal:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
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
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
        case VesselEventType::ExitChannel:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
            return true;
        case VesselEventType::Created:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        default:
            return false;
    }
}

bool VesselEvent::hasTugs() const {
    switch (type) {
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
            return true;
        case VesselEventType::ArriveTerminal:
        case VesselEventType::AtAnchorage:
        case VesselEventType::Created:
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::ExitChannel:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::StartLoading:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitEnter:
        case VesselEventType::WaitSail:
        default:
            return false;
    }
}