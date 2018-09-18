/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-09-18 20:48:43.204362
 **/
#pragma once
#include <string>

enum class TrainCoalTransportationEventType {
    ArrivedDumpstation,
    ArrivedLoadpoint,
    Created,
    DepartLoadpoint,
    DepartTerminal,
    DumpComplete,
    DumpStart,
    LoadComplete,
    LoadStart,
    Invalid
};

TrainCoalTransportationEventType decodeTrainCoalTransportationEventType(const std::string& enumeratorString);
std::string encodeTrainCoalTransportationEventType(const TrainCoalTransportationEventType& value);