/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-11 15:53:43.172985
 **/
#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <cstdio>

#include "../tinyxml2/tinyxml2.h"
#include "Dumpstation/DumpstationEvent.h"
#include "Loadpoints/LoadpointsEvent.h"
#include "Reclaimer/ReclaimerEvent.h"
#include "Shiploader/ShiploaderEvent.h"
#include "Signal/SignalEvent.h"
#include "Stacker/StackerEvent.h"
#include "Stockpile/StockpileEvent.h"
#include "Vessel/VesselEvent.h"

//This macro prints out an error message if the XMLError holds anything that isn't an tinyxml2::XML_SUCCESS
#ifndef XMLCheckResult
    //#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS){ std::printf("Error: %i\n", a_eResult); return a_eResult;}

    #define XMLCheckResult(a_eResult, doPrint) if (a_eResult != tinyxml2::XML_SUCCESS){ if (doPrint) {std::printf("Error: %i\n", a_eResult); } return a_eResult;}
#endif    

typedef std::tuple<
    std::vector<DumpstationEvent>, 
    std::vector<LoadpointsEvent>, 
    std::vector<ReclaimerEvent>, 
    std::vector<ShiploaderEvent>, 
    std::vector<SignalEvent>, 
    std::vector<StackerEvent>, 
    std::vector<StockpileEvent>, 
    std::vector<VesselEvent>
> EventVectorTuple;

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode) {
    Event event;
    tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode);
    XMLCheckResult(result, 1);
    destination.push_back(event);
    return result; 
}

/* uses the extractEvent for the associated Event type to get a single event from the tag, and then adds it to the destination vector*/
template<typename Event>
inline tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, std::vector<Event>& destination, const std::string& eventTypeCode, TerminalId theTerminal) {
    Event event;
    tinyxml2::XMLError result = extractEvent(source, event, eventTypeCode, theTerminal);
    XMLCheckResult(result, 1);
    destination.push_back(event);
    return result; 
}

template<typename T>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, T& destination, const std::string& attributeName) {
    //hack to get around the bug where QueryAttribute returns an int instead of the enum instance
    tinyxml2::XMLError result = static_cast<tinyxml2::XMLError>(source.QueryAttribute(attributeName.c_str(), &destination));
    XMLCheckResult(result, 1);
    return result;
}


template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, std::string& destination, const std::string& attributeName) {
    const char* tmp;
    tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
    XMLCheckResult(result, 1);
    destination = tmp;
    return result;
}

template<>
inline tinyxml2::XMLError extractAttribute(const tinyxml2::XMLElement& source, SignalStateType& destination, const std::string& attributeName) {
    const char* tmp;
    tinyxml2::XMLError result = source.QueryStringAttribute(attributeName.c_str(), &tmp);
    XMLCheckResult(result, 1);
    destination = decodeSignalStateType(tmp);
    return result;
}

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, DumpstationEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, LoadpointsEvent& destination, const std::string& eventTypeCode);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ReclaimerEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, ShiploaderEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, SignalEvent& destination, const std::string& eventTypeCode);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StackerEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, StockpileEvent& destination, const std::string& eventTypeCode, TerminalId theTerminal);

tinyxml2::XMLError extractEvent(const tinyxml2::XMLElement& source, VesselEvent& destination, const std::string& eventTypeCode);

tinyxml2::XMLError extractAll(const std::string& srcFilePath, EventVectorTuple& destination);