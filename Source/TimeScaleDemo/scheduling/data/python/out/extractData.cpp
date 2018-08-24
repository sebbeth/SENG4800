#include "extractData.h"
#include <regex>

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, DumpStationEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeDumpStationEventType(eventTypeCode);
    if (destination.type == DumpStationEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.dumpStationID, "dumpstationID"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case DumpStationEventType::DumpOperationComplete:
        case DumpStationEventType::DumpOperationStart:
        case DumpStationEventType::DumpStart:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
        case DumpStationEventType::DumpComplete:
            XMLCheckResult(extractAttribute(source, destination.amountDumped, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, LoadPointEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeLoadPointEventType(eventTypeCode);
    if (destination.type == LoadPointEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.loadPointID, "loadpointID"), 0);
    XMLCheckResult(extractAttribute(source, destination.loadPointName, "loadpointName"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case LoadPointEventType::StartLoad:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            break;
        case LoadPointEventType::FinishLoad:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ReclaimerEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeReclaimerEventType(eventTypeCode);
    if (destination.type == ReclaimerEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.machineID, "reclaimerID"), 0);
    XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case ReclaimerEventType::DoubleHandleOperationStart:
        case ReclaimerEventType::DoubleHandleStart:
        case ReclaimerEventType::Fail:
        case ReclaimerEventType::Fix:
        case ReclaimerEventType::OperationStart:
        case ReclaimerEventType::Start:
        case ReclaimerEventType::SyncedFail:
        case ReclaimerEventType::SyncedFix:
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
        case ReclaimerEventType::Complete:
        case ReclaimerEventType::DoubleHandleComplete:
        case ReclaimerEventType::DoubleHandleOperationComplete:
        case ReclaimerEventType::OperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ShipLoaderEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeShipLoaderEventType(eventTypeCode);
    if (destination.type == ShipLoaderEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
    XMLCheckResult(extractAttribute(source, destination.shipLoaderID, "shiploaderID"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case ShipLoaderEventType::StartVesselLoad:
            XMLCheckResult(extractAttribute(source, destination.vesselID, "vesselID"), 0);
            break;
        case ShipLoaderEventType::Fail:
        case ShipLoaderEventType::Fix:
        case ShipLoaderEventType::LoadOperationStart:
        case ShipLoaderEventType::LoadStart:
        case ShipLoaderEventType::SyncedFail:
        case ShipLoaderEventType::SyncedFix:
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
        case ShipLoaderEventType::LoadComplete:
        case ShipLoaderEventType::LoadOperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, SignalEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeSignalEventType(eventTypeCode);
    if (destination.type == SignalEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.signalID, "signalID"), 0);
    XMLCheckResult(extractAttribute(source, destination.signalState, "signalState"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StackerEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeStackerEventType(eventTypeCode);
    if (destination.type == StackerEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.machineID, "stackerID"), 0);
    XMLCheckResult(extractAttribute(source, destination.position, "pos"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case StackerEventType::DoubleHandleOperationStart:
        case StackerEventType::DoubleHandleStart:
        case StackerEventType::Fail:
        case StackerEventType::Fix:
        case StackerEventType::OperationStart:
        case StackerEventType::Start:
        case StackerEventType::SyncedFail:
        case StackerEventType::SyncedFix:
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
        case StackerEventType::Complete:
        case StackerEventType::DoubleHandleComplete:
        case StackerEventType::DoubleHandleOperationComplete:
        case StackerEventType::OperationComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StockpileEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeStockpileEventType(eventTypeCode);
    if (destination.type == StockpileEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.padID, "padID"), 0);
    XMLCheckResult(extractAttribute(source, destination.stockpileID, "stockpileID"), 0);
    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
    XMLCheckResult(extractAttribute(source, destination.vesselID, "vesselID"), 0);

    switch(destination.type) {
        case StockpileEventType::StockpileCreated:
            XMLCheckResult(extractAttribute(source, destination.length, "length"), 0);
            XMLCheckResult(extractAttribute(source, destination.startPosition, "pos"), 0);
            break;
        case StockpileEventType::StockpileRemoved:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            break;
        case StockpileEventType::ReclaimStart:
        case StockpileEventType::ReclaimTransferStart:
        case StockpileEventType::StackStart:
        case StockpileEventType::StackTransferStart:
            XMLCheckResult(extractAttribute(source, destination.machineID, "machineID"), 0);
            break;
        case StockpileEventType::ReclaimComplete:
        case StockpileEventType::ReclaimTransferComplete:
        case StockpileEventType::RemnantRemoved:
        case StockpileEventType::StackComplete:
        case StockpileEventType::StackTransferComplete:
        case StockpileEventType::StockpileRemnant:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.machineID, "machineID"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}

//Note: If this needs to be implemented manually, if can be shortened to one if(hasX) {...extractEvent(source,&destination.x,"attributeTextX")..} for each attribute
tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, TrainEvent& destination, const std::string& eventTypeCode) {
    destination.type = decodeTrainEventType(eventTypeCode);
    if (destination.type == TrainEventType::Invalid) {
        XMLCheckResult(tinyxml2::XML_ERROR_PARSING_ELEMENT, 0);
    }

    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);

    switch(destination.type) {
        case TrainEventType::ArrivedLoadpoint:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.loadPointID, "loadpointID"), 0);
            XMLCheckResult(extractAttribute(source, destination.plannedTime, "plannedTime"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::Created:
            XMLCheckResult(extractAttribute(source, destination.direction, "direction"), 0);
            XMLCheckResult(extractAttribute(source, destination.junctionID, "junctionID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trackID, "trackID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainType, "trainType"), 0);
            break;
        case TrainEventType::LoadStart:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            break;
        case TrainEventType::DumpStart:
        case TrainEventType::WaitEnd:
        case TrainEventType::WaitForTracks:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::WaitSignal:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.signalID, "signalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trackID, "trackID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::ReachedSignal:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.signalID, "signalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.signalState, "signalState"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::DumpComplete:
        case TrainEventType::LoadComplete:
            XMLCheckResult(extractAttribute(source, destination.amount, "amount"), 0);
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            break;
        case TrainEventType::MaintenanceStart:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.depotID, "depotID"), 0);
            XMLCheckResult(extractAttribute(source, destination.maintenanceActivity, "maintActivity"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::WaitJunction:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.junctionID, "junctionID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::DepartLoadpoint:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.plannedTime, "plannedTime"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::EnterTrack:
        case TrainEventType::HeadLeaveTrack:
        case TrainEventType::TailLeaveTrack:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.direction, "direction"), 0);
            XMLCheckResult(extractAttribute(source, destination.sectionID, "sectionID"), 0);
            XMLCheckResult(extractAttribute(source, destination.speed, "speed"), 0);
            XMLCheckResult(extractAttribute(source, destination.trackID, "trackID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::DepartTerminal:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.plannedTime, "plannedTime"), 0);
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::ArrivedDumpstation:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.dumpStationID, "dumpstationID"), 0);
            XMLCheckResult(extractAttribute(source, destination.plannedTime, "plannedTime"), 0);
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
            break;
        case TrainEventType::MaintenanceAttempted:
        case TrainEventType::MaintenanceCompleted:
            XMLCheckResult(extractAttribute(source, destination.cycleID, "cycleID"), 0);
            XMLCheckResult(extractAttribute(source, destination.depotID, "depotID"), 0);
            XMLCheckResult(extractAttribute(source, destination.trainID, "trainID"), 0);
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

    XMLCheckResult(extractAttribute(source, destination.time, "time"), 0);
    XMLCheckResult(extractAttribute(source, destination.vesselID, "vesselID"), 0);

    switch(destination.type) {
        case VesselEventType::WaitEnter:
            XMLCheckResult(extractAttribute(source, destination.isTidal, "isTidal"), 0);
            break;
        case VesselEventType::AtAnchorage:
            XMLCheckResult(extractAttribute(source, destination.terminalID, "terminalID"), 0);
            break;
        case VesselEventType::ArriveTerminal:
            XMLCheckResult(extractAttribute(source, destination.meterMark, "meterMark"), 0);
            break;
        case VesselEventType::DepartTerminal:
        case VesselEventType::EnterChannel:
            XMLCheckResult(extractAttribute(source, destination.numberOfTugs, "tugs"), 0);
            break;
    }
    return tinyxml2::XML_SUCCESS;
}
    
tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple& destination) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLNode* root;
    tinyxml2::XMLElement* eachElement;

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
            if (entityTypeCode == "Ds") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<DumpStationEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Lp") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<LoadPointEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Rec") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<ReclaimerEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Sl") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<ShipLoaderEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Signal") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<SignalEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Stk") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<StackerEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Sp") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<StockpileEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Train") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<TrainEvent>>(destination), eventTypeCode), 0);    
            } else if (entityTypeCode == "Vessel") {
                XMLCheckResult(extractEvent(*eachElement, std::get<std::vector<VesselEvent>>(destination), eventTypeCode), 0);    
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