#include "loadData.h"

#include <experimental/filesystem> // c++-standard header file name
#include <filesystem> // microsoft-specific implementation header file name  
#include <string> // memset()
#include <stdexcept>
#include <regex>
#include <iostream>

namespace fs = std::experimental::filesystem;


EventVectorTuple getEventsFromXMLFolder(const std::string& xmlFolderPath) {
	EventVectorTuple result;
	for (const auto& each : fs::directory_iterator(xmlFolderPath)) {
		std::string pathToFile = each.path().string();

		//Use a regex to find out the name of the next file to extract from:
		std::regex r("^(.*)(\\\\)(.*)(.xml)");
		std::smatch match;
		std::regex_search(pathToFile, match, r);

		//Print out a notice which states which files will next have its data extracted:
		std::cout << "    Extracting data from " << match[3] << match[4] << std::endl;

		auto err = extractAll(pathToFile, result);
	}
	return result;
}

std::map<Stacker::Id, std::vector<StackerEvent>> mapAndSort(const std::vector<StackerEvent>& source) {
	std::map<Stacker::Id, std::vector<StackerEvent>> result;
	for (auto eachEvent : source) {
		auto eachId = eachEvent.id;
		//This variable is used to find out whether the std::pair for the
		//currently examined object (eg. stockpile with stockpileID "CCT1392.1")
		//has been created or not:
		auto entryIterator = result.find(eachId);

		if (entryIterator == result.end()) {
			//If the std::pair for the currently examined object has not been created,
			//create entryIterator and place the initial creation state at the front of the vector
			//of states:
			entryIterator = result.emplace(std::piecewise_construct, std::make_tuple(eachId), std::make_tuple()).first;
		}
		(*entryIterator).second.push_back(eachEvent);
	}

	//now do the sort
	for (auto eachEntry : result) {
		std::sort(eachEntry.second.begin(), eachEntry.second.end(), [](const StackerEvent& a, const StackerEvent& b) {return a.time < b.time; });
	}
	return result;
}