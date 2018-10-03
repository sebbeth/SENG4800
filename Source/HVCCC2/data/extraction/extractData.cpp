/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-03 22:59:09.760513
 **/
#include "extractData.h"
#include <regex>

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, DumpstationEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    destination.type = decodeDumpstationEventType(eventTypeCode);
    if (destination.type == DumpstationEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "dumpstationID"), 0);
    destination.id.terminal = theTerminal;

    switch(destination.type) {
        case DumpstationEventType::DumpComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
        case DumpstationEventType::DumpStart:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, LoadpointsEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeLoadpointsEventType(eventTypeCode);
    if (destination.type == LoadpointsEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "loadpointID"), 0);

    switch(destination.type) {
        case LoadpointsEventType::MaintenanceComplete:
        case LoadpointsEventType::MaintenanceStart:
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
        case LoadpointsEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.loadpointName, "loadpointName"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case LoadpointsEventType::StartLoad:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.loadpointName, "loadpointName"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case LoadpointsEventType::FinishLoad:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.loadpointName, "loadpointName"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ReclaimerEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    destination.type = decodeReclaimerEventType(eventTypeCode);
    if (destination.type == ReclaimerEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "reclaimerID"), 0);
    destination.id.terminal = theTerminal;

    switch(destination.type) {
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationComplete:
        case ReclaimerEventType::OperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ShiploaderEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    destination.type = decodeShiploaderEventType(eventTypeCode);
    if (destination.type == ShiploaderEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "shiploaderID"), 0);
    destination.id.terminal = theTerminal;

    switch(destination.type) {
        case ShiploaderEventType::HatchChangeStart:
        case ShiploaderEventType::OnHatchChangeComplete:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ShiploaderEventType::FinishVesselDraftSurvey:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::StartVesselDraftSurvey:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ShiploaderEventType::LoadComplete:
        case ShiploaderEventType::LoadOperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ShiploaderEventType::StartVesselLoad:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StackerEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    destination.type = decodeStackerEventType(eventTypeCode);
    if (destination.type == StackerEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "stackerID"), 0);
    destination.id.terminal = theTerminal;

    switch(destination.type) {
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationComplete:
        case StackerEventType::OperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID.name, "stockpileID"), 0);
            destination.stockpileID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StockpileEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    destination.type = decodeStockpileEventType(eventTypeCode);
    if (destination.type == StockpileEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "stockpileID"), 0);
    destination.id.terminal = theTerminal;

    switch(destination.type) {
        case StockpileEventType::StockpileBuilt:
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
        case StockpileEventType::DedicatedStockpileCreated:
        case StockpileEventType::StockpileCreated:
            XMLCheckResult(extractAttribute(source, destination.length, "length"), 0);
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferStart:
            XMLCheckResult(extractAttribute(source, destination.machineID.name, "machineID"), 0);
            destination.machineID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StockpileRemnant:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.machineID.name, "machineID"), 0);
            destination.machineID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, TrainMovementEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeTrainMovementEventType(eventTypeCode);
    if (destination.type == TrainMovementEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "trainID"), 0);

    switch(destination.type) {
        case TrainMovementEventType::WaitForTracks:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case TrainMovementEventType::EnterTrack:
        case TrainMovementEventType::HeadLeaveTrack:
        case TrainMovementEventType::TailLeaveTrack:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.direction, "direction"), 0);
            XMLCheckResult(extractAttribute(source, destination.sectionID, "sectionID"), 0);
            XMLCheckResult(extractAttribute(source, destination.speed, "speed"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.trackID, "trackID"), 0);
            break;
        case TrainMovementEventType::ReachedSignal:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.signalID, "signalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.signalState, "signalState"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, VesselEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeVesselEventType(eventTypeCode);
    if (destination.type == VesselEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }
    //extract the identifying name
    XMLCheckResult(extractAttribute(source, destination.id.name, "vesselID"), 0);

    switch(destination.type) {
        case VesselEventType::BallastTankEmpty:
        case VesselEventType::Created:
        case VesselEventType::HatchChangeComplete:
        case VesselEventType::HatchChangeStart:
        case VesselEventType::StopForDeballasting:
        case VesselEventType::StopForDeballastingComplete:
        case VesselEventType::YardSpaceAllocated:
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case VesselEventType::DraftSurveyComplete:
        case VesselEventType::DraftSurveyStart:
        case VesselEventType::StartLoading:
            XMLCheckResult(extractAttribute(source, destination.ballast, "ballast"), 0);
            XMLCheckResult(extractAttribute(source, destination.cargo, "cargo"), 0);
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case VesselEventType::FullyLoaded:
            XMLCheckResult(extractAttribute(source, destination.cargo, "cargo"), 0);
            XMLCheckResult(extractAttribute(source, destination.numcargoes, "numCargoes"), 0);
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple& destination) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLNode* root;
    tinyxml2::XMLElement* eachElement;

    int fileNameIndex = std::max(int(srcFilePath.rfind('/')), int(srcFilePath.rfind('\\')))+1;
    std::string terminalName = srcFilePath.substr(fileNameIndex, TERMINAL_CODE_LENGTH);
    TerminalId theTerminal = decodeTerminalId(terminalName); //not that this could easily be null;

    tinyxml2::XMLError eResult = document.LoadFile(srcFilePath.c_str());
    XMLCheckResult(eResult, 0);

    //Set the root pointer to point to the root element; this is different to FirstChild and should skip the xml version declaration node
    root = document.RootElement();
    if (root == nullptr) {
        return tinyxml2::XML_ERROR_FILE_READ_ERROR;
    }

    eachElement = root->FirstChildElement();
    if (eachElement == nullptr) {
        return tinyxml2::XML_ERROR_PARSING_ELEMENT;
    }

    //The program keeps looping until all of the elements have been read:
    while (eachElement != nullptr) {
        std::string tagName = eachElement->Name();
        std::string entityTypeCode, eventTypeCode;
        std::regex prefixRegex("^[A-Z][a-z]+");
        std::sregex_iterator regItBegin(tagName.begin(), tagName.end(), prefixRegex);

        if (regItBegin != std::sregex_iterator()) {
            entityTypeCode = (*regItBegin).str();
            eventTypeCode = tagName.substr(entityTypeCode.size());
            if (entityTypeCode == Dumpstation::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<DumpstationEvent>>(destination), eventTypeCode, theTerminal); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Loadpoints::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<LoadpointsEvent>>(destination), eventTypeCode); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Reclaimer::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<ReclaimerEvent>>(destination), eventTypeCode, theTerminal); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Shiploader::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<ShiploaderEvent>>(destination), eventTypeCode, theTerminal); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Stacker::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<StackerEvent>>(destination), eventTypeCode, theTerminal); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Stockpile::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<StockpileEvent>>(destination), eventTypeCode, theTerminal); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == TrainMovement::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<TrainMovementEvent>>(destination), eventTypeCode); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else if (entityTypeCode == Vessel::XML_TAG_PREFIX) {
                extractEvent(*eachElement, std::get<std::vector<VesselEvent>>(destination), eventTypeCode); //note: no longer cancelling when an individual event fails to extract so that some tags can be skipped
            } else {
                //state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
                std::printf("Warning: unrecognised tag '%s'\n", tagName.c_str()); //todo: should probably print a better warning, etc
            }
        } else {
            //if it's an element that we know might have children we want, check those instead of assuming it's wrong
            if (std::string(tagName.c_str()) == "railEvents" && !eachElement->NoChildren()) {
                eachElement = eachElement->FirstChildElement();
                continue;
            } else {
                //state that we had a problem, but continue parsing since it may just be an event we haven't coded for yet
                std::printf("Warning: unrecognised tag '%s'\n", tagName.c_str()); //todo: should probably print a better warning, etc
            }
        }
        //Moves the element pointer to the next event element:
        tinyxml2::XMLElement* nextElement = eachElement->NextSiblingElement();

        //if we reach the end of a sublist and there's a parent, move onto that. instead of giving up
        if (nextElement == nullptr && eachElement->Parent() != nullptr) {
            nextElement = eachElement->Parent()->NextSiblingElement();
        }
        eachElement = nextElement;
    }
    return tinyxml2::XML_SUCCESS;
}