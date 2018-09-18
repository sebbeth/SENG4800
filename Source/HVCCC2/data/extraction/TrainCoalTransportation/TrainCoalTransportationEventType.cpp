/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 21:27:51.338785
 **/
#include "TrainCoalTransportationEventType.h"
        
TrainCoalTransportationEventType decodeTrainCoalTransportationEventType(const std::string& enumeratorString) {
    if (enumeratorString == "ArrivedDumpstation") {
        return TrainCoalTransportationEventType::ArrivedDumpstation;
    } else if (enumeratorString == "ArrivedLoadpoint") {
        return TrainCoalTransportationEventType::ArrivedLoadpoint;
    } else if (enumeratorString == "Created") {
        return TrainCoalTransportationEventType::Created;
    } else if (enumeratorString == "DepartLoadpoint") {
        return TrainCoalTransportationEventType::DepartLoadpoint;
    } else if (enumeratorString == "DepartTerminal") {
        return TrainCoalTransportationEventType::DepartTerminal;
    } else if (enumeratorString == "DumpComp") {
        return TrainCoalTransportationEventType::DumpComplete;
    } else if (enumeratorString == "DumpStart") {
        return TrainCoalTransportationEventType::DumpStart;
    } else if (enumeratorString == "LoadComp") {
        return TrainCoalTransportationEventType::LoadComplete;
    } else if (enumeratorString == "LoadStart") {
        return TrainCoalTransportationEventType::LoadStart;
    } else {
        return TrainCoalTransportationEventType::Invalid;
    }
}
std::string encodeTrainCoalTransportationEventType(const TrainCoalTransportationEventType& value) {
    switch(value) {
        case TrainCoalTransportationEventType::Created:
            return "Created";
            break;

        case TrainCoalTransportationEventType::DepartTerminal:
            return "DepartTerminal";
            break;

        case TrainCoalTransportationEventType::ArrivedLoadpoint:
            return "ArrivedLoadpoint";
            break;

        case TrainCoalTransportationEventType::LoadStart:
            return "LoadStart";
            break;

        case TrainCoalTransportationEventType::LoadComplete:
            return "LoadComp";
            break;

        case TrainCoalTransportationEventType::DepartLoadpoint:
            return "DepartLoadpoint";
            break;

        case TrainCoalTransportationEventType::ArrivedDumpstation:
            return "ArrivedDumpstation";
            break;

        case TrainCoalTransportationEventType::DumpStart:
            return "DumpStart";
            break;

        case TrainCoalTransportationEventType::DumpComplete:
            return "DumpComp";
            break;

        default:
            return "Invalid";
    }
}