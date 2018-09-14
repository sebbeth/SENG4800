#define DEBUG
#include "extraction/extractData.h"
#include <iostream>

#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
#include <string.h> // memset()
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>

#include "loadData.h"
#include "convertData.h"
#include "serialization.h"
#include <iostream>

#include <experimental/filesystem> // c++-standard header file name
#include <filesystem> // microsoft-specific implementation header file name  
#include <string> // memset()
#include <stdexcept>

namespace fs = std::experimental::filesystem;

#include "extraction/implementedEntities.h"

//This is the file which holds the machine-dependent filepaths
//to both the XML files directory and binary files directory.
	//1. Please delete the current copy of env_config.h in Solution Explorer
	//2. In Solution Explorer, create a new item called env_config.h
	//3. Copy the contents of env_configEXAMPLE.h into the newly created env_config.h
	//4. Change the "PROJECT_PATH" value, as well as having the following folders in that directory:
		//"XMLs" for the XML files and "BinaryDaraFiles" for the binary data files.
#include "env_config.h"

int main() {
	//Extraction of all of the data inside each XML file:
	std::cout << "Now starting the data extraction process." << std::endl;
	
	EventVectorTuple allEvents = getEventsFromXMLFolder(XML_PATH);
	
	EventMapTuple<EntitiesWithEvents> organisedEventsTuple;
	forEachInTuple(allEvents, MapAndSortFunctor<EntitiesWithEvents>(organisedEventsTuple));

	StateMapTuple<AllEntities> statesTuple;
	forEachInTuple(organisedEventsTuple, ConvertFunctor<AllEntities> (statesTuple));

	//note that this isn't fully templated, but should never need other specialisations
	merge(statesTuple, std::get<StateMap<StackerReclaimer>>(statesTuple));

	////Serialise all of the extracted data into binary files:
	//bool could_ser = serialize(statesTuple, BINARY_PATH);
	//std::cout << "Serialised the data into binary files.\n" << std::endl;

	////Deserialise the data from the binary data files into memory:
	//std::tuple<std::map<Stacker::Id, std::vector<StackerState>>> deserializedStates;
	//bool could_deser = deserialize(BINARY_PATH, deserializedStates);
	//std::cout << "Data deserialised from binary files into memory." << std::endl;
	return 0;
}