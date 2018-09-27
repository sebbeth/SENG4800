#include "loadData.h"

#include <experimental/filesystem> // c++-standard header file name
#include <filesystem> // microsoft-specific implementation header file name  
#include <string> // memset()
#include <stdexcept>
#include <regex>
#include <iostream>

namespace fs = std::experimental::filesystem;

std::pair<EventVectorTuple, bool> getEventsFromXMLFolder(const std::string& xmlFolderPath) {
	EventVectorTuple result;
	tinyxml2::XMLError err = tinyxml2::XMLError::XML_ERROR_PARSING_UNKNOWN;
	for (const auto& each : fs::directory_iterator(xmlFolderPath)) {
		std::string pathToFile = each.path().string();

		//Use a regex to find out the name of the next file to extract from:
		std::regex r("^(.*)(\\\\)(.*)(.xml)");
		std::smatch match;
		std::regex_search(pathToFile, match, r);

		//Make sure the file/folder examined is an XML file, not a folder or other type of file
		//before attempting to extract data from it:
		if (match.size() > 0) {
			//Print out a notice which states which files will next have its data extracted:
			std::cout << "    Extracting data from " << match[3] << match[4] << std::endl;

			err = extractAll(pathToFile, result);
		}
	}
	return std::make_pair(result, err == tinyxml2::XMLError::XML_SUCCESS);
}

std::pair<StateMapTuple<AllEntities>, bool> loadXMLData(const std::string& srcPath) {
	StateMapTuple<AllEntities> result;

	//TODO: REFACTOR THIS TO ALSO RETURN A TUPLE WITH A SUCCESS VALUE
	auto xmlResultPair = getEventsFromXMLFolder(srcPath);
	if (xmlResultPair.second) {
		EventVectorTuple& allEvents = xmlResultPair.first;
		EventMapTuple<EntitiesWithEvents> organisedEventsTuple;
		forEachInTuple(allEvents, MapAndSortFunctor<EntitiesWithEvents>(organisedEventsTuple));

		forEachInTuple(organisedEventsTuple, ConvertFunctor<AllEntities>(result));

		//note that this isn't fully templated, but should never need other specialisations
		merge(result, std::get<StateMap<StackerReclaimer>>(result));
	}
	return std::make_pair(result, xmlResultPair.second);
}

std::pair<StateMapTuple<AllEntities>, bool> loadBinaryData(const std::string& srcPath) {
	StateMapTuple<AllEntities> result;
	//Deserialise the data from the binary data files into memory:
	bool success = deserialize(srcPath, result);
	return std::make_pair(result, success);
}