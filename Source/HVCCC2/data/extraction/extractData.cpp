/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
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
        case DumpstationEventType::DumpOperationComplete:
        case DumpstationEventType::DumpOperationStart:
        case DumpstationEventType::DumpStart:
        case DumpstationEventType::MaintenanceComplete:
        case DumpstationEventType::MaintenanceStart:
        case DumpstationEventType::SyncedFail:
        case DumpstationEventType::SyncedFix:
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case DumpstationEventType::DumpComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID.name, "trainID"), 0);
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
        case LoadpointsEventType::OnFail:
        case LoadpointsEventType::OnFix:
        case LoadpointsEventType::StartIdle:
        case LoadpointsEventType::StartLoad:
        case LoadpointsEventType::StartPostload:
        case LoadpointsEventType::StartPreload:
        case LoadpointsEventType::StartRecharge:
            XMLCheckResult(extractAttribute(source, destination.loadpointName, "loadpointName"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case LoadpointsEventType::FinishLoad:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
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
        case ReclaimerEventType::MaintenanceComplete:
        case ReclaimerEventType::MaintenanceStart:
        case ReclaimerEventType::OnMove:
        case ReclaimerEventType::OnStopMove:
        case ReclaimerEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
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
        case ShiploaderEventType::MaintenanceComplete:
        case ShiploaderEventType::MaintenanceStart:
        case ShiploaderEventType::OnMove:
        case ShiploaderEventType::OnStopMove:
        case ShiploaderEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case ShiploaderEventType::Fail:
        case ShiploaderEventType::Fix:
        case ShiploaderEventType::LoadOperationStart:
        case ShiploaderEventType::LoadStart:
        case ShiploaderEventType::SyncedFail:
        case ShiploaderEventType::SyncedFix:
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
        case StackerEventType::MaintenanceComplete:
        case StackerEventType::MaintenanceStart:
        case StackerEventType::OnMove:
        case StackerEventType::OnStopMove:
        case StackerEventType::WrapUp:
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
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
        case StockpileEventType::ReclaimStart:
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
        case StockpileEventType::StockpileRemoved:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.machineID.name, "machineID"), 0);
            destination.machineID.terminal = theTerminal;
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.vesselID.name, "vesselID"), 0);
            break;
        case StockpileEventType::StockpileCreated:
            XMLCheckResult(extractAttribute(source, destination.length, "length"), 0);
            XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
            XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
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

    XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
    XMLCheckResult(extractAttribute(source, destination.direction, "direction"), 0);
    XMLCheckResult(extractAttribute(source, destination.sectionID, "sectionID"), 0);
    XMLCheckResult(extractAttribute(source, destination.speed, "speed"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
    XMLCheckResult(extractAttribute(source, destination.trackID, "trackID"), 0);
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
        case VesselEventType::ExitChannel:
        case VesselEventType::WaitBerth:
        case VesselEventType::WaitSail:
        case VesselEventType::YardSpaceAllocated:
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case VesselEventType::ArriveTerminal:
            XMLCheckResult(extractAttribute(source, destination.metermark, "meterMark"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case VesselEventType::AtAnchorage:
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            break;
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
            XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
            XMLCheckResult(extractAttribute(source, destination.tugs, "tugs"), 0);
            break;
        case VesselEventType::WaitEnter:
            XMLCheckResult(extractAttribute(source, destination.isTidal, "isTidal"), 0);
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