// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef DATAEXTRACTOR_H
#define DATAEXTRACTOR_H

#include "CoreMinimal.h"

#include <string>
#include <vector>
#include "tinyxml2.h"

//Our custom data storage classes:
#include "DataStorageClasses/CCTShipLoaderLogEvent.h"
#include "DataStorageClasses/KCTReclaimerLogEvent.h"

//The includes required for Cereal library serialization/deserialization:
#include <fstream>
#include "cereal/archives/binary.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"

using namespace std;
//using namespace tinyxml2;
using namespace cereal;

class HVCCC2_API DataExtractor
{
	public:

		DataExtractor(string projectSourceFolderDirectory);
		tinyxml2::XMLError extract(const char* newXMLDocName);

		//NOTE:
		//We've included the functionality inside serialize() and deserialize() inside this header file,
		//since functions which use templates require the functionality to be in the header file.

		//Serializes a vector of events to a binary file:
		//bool serialize(const char * fileName, vector<T> events) {
		template <typename T>
		bool serialize(const char * fileName, vector<T> events) {
			//Append the directory that the files will be stored in, in front of the file name passed in,
			//as well as a custom data type "BinaryDataFile" (which isn't a real data type).
			stringstream ss;
			ss << _projectSourceFolderDirectory << "/Deserialisation code/BinaryDataFiles/" << fileName << ".BinaryDataFile";
			string properDirectoryString = ss.str();

			ofstream outputFS(properDirectoryString, ios::binary);
			if (outputFS.is_open()) {
				try {
					BinaryOutputArchive outputArchive(outputFS);

					//Serialise the vector of events:
					outputArchive(events);

					outputFS.close();
					//Return true if the vector of events was successfully serialized:
					return true;
				}
				catch (runtime_error e) {
					//If anything goes wrong in the above lines, print out the exception and return false:
					cout << e.what() << endl;
					return false;
				}
			}

			//This will get executed if the filestream could not be opened for some reason:
			return false;
		}

		//Deserializes a vector of events from a binary file:
		template <typename T>
		vector<T> deserialize(const char * fileName) {
			//The vector of events to return:
			vector<T> events;

			//Append the directory that the files will be extracted from, in front of the file name passed in,
			//as well as a custom data type "BinaryDataFile" (which isn't a real data type).
			stringstream ss;
			ss << _projectSourceFolderDirectory << "/Deserialisation code/BinaryDataFiles/" << fileName << ".BinaryDataFile";
			string properDirectoryString = ss.str();

			ifstream inputFS(properDirectoryString, ios::binary);
			if (inputFS.is_open()) {
				try {
					BinaryInputArchive inputArchive(inputFS);

					//Deserialize the vector of events:
					inputArchive(events);
					return events;
				}
				catch (runtime_error e) {
					//If anything goes wrong in the above lines, print out the exception and return the vector of events of size 0:
					cout << e.what() << endl;
					return events;
				}
			}

			//This will get executed if the filestream could not be opened for some reason:
			return events;
		}
	private:
		//Private member variables:
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLNode* pRoot;
		tinyxml2::XMLElement* pElement;

		string _projectSourceFolderDirectory;

		//Private functions:
		tinyxml2::XMLError prepareToExtractFromXML(const char* newXMLDocName);
		tinyxml2::XMLError extractCCTShipLoaderLogData();
		tinyxml2::XMLError extractKCTReclaimerLogData();

		tinyxml2::XMLError checkXMLResult(tinyxml2::XMLError);
};

#endif