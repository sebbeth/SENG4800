#pragma once
#include "extraction/extractData.h"
#include <map>
#include <vector>

EventVectorTuple getEventsFromXMLFolder(const std::string& xmlFolderPath);

std::map<Stacker::Id, std::vector<StackerEvent>> mapAndSort(const std::vector<StackerEvent>& source);