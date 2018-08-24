#include "loadData.h"

#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
#include <string> // memset()
#include <stdexcept>
#include <regex>
#include <iostream>

namespace fs = std::experimental::filesystem;


EventVectorTuple getEventsFromXMLFolder(std::string xmlFolderPath) {
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