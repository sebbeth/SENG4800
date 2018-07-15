// Fill out your copyright notice in the Description page of Project Settings.

#include "DataExtractor.h"
#include "../stdafx.h"

//using namespace cereal;

DataExtractor::DataExtractor(string projectSourceFolderDirectory)
{
	_projectSourceFolderDirectory = projectSourceFolderDirectory;
}

tinyxml2::XMLError DataExtractor::prepareToExtractFromXML(const char* newXMLDocName) {
	//Adds the proper "XML/" prefix to the char pointer, so that the XML files can be found in their directory:
	string properDirectoryString = newXMLDocName;
	properDirectoryString = "XMLs/" + properDirectoryString;
	newXMLDocName = properDirectoryString.c_str();

	tinyxml2::XMLError eResult = xmlDoc.LoadFile(newXMLDocName);
	checkXMLResult(eResult);

	//Set the root pointer to point to the root element:
	pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr)
		return tinyxml2::XML_ERROR_FILE_READ_ERROR;

	//The following code is used to check if the root element is the XML declaration line (ie. "xml version="..."") line or not.
	//If it is the XML declaration line, the root pointer is moved to the first actual content XML element.
	const char* charPointer = pRoot->Value();
	string textContents = charPointer;

	//A size of 11 means that it will include at least "xml version" from the XML declaration line:
	if (textContents.size() > 11) {
		string firstElementSubstring = textContents.substr(0, 11);

		if (firstElementSubstring == "xml version")
			pRoot = pRoot->NextSibling();
	}

	//Set this XMLElement pointer to point to the first read content tag of the XML file:
	pElement = pRoot->FirstChildElement();
	if (pElement == nullptr)
		return tinyxml2::XML_ERROR_PARSING_ELEMENT;

	return tinyxml2::XML_SUCCESS;
}

tinyxml2::XMLError DataExtractor::extract(const char* newXMLDocName) {
	//Call the function to prepare to extract the data from the new XML file:
	prepareToExtractFromXML(newXMLDocName);

	//Call the matching function, to extract the data from the XML file properly:
	//if (newXMLDocName == "CCTShipLoaderLog.xml") {
	if (strcmp(newXMLDocName, "CCTShipLoaderLog.xml") != 0) {
		extractCCTShipLoaderLogData();
	}
	else {
		extractKCTReclaimerLogData();
	}

	return tinyxml2::XML_SUCCESS;
}

tinyxml2::XMLError DataExtractor::checkXMLResult(tinyxml2::XMLError result) {
	if (result != tinyxml2::XML_SUCCESS) {
		printf("Error: %i\n", result);
	}
	return result;
}

//Data extraction for the CCTShipLoaderLog XML file:
tinyxml2::XMLError DataExtractor::extractCCTShipLoaderLogData() {
	//The vector which will hold all of the events from the one XML file:
	vector<CCTShipLoaderLogEvent> events;

	//The program keeps looping until all of the elements have been read:
	while (pElement != nullptr) {
		//This carries out the extraction for the bits of data that need to be extracted from every element:

		//Extracts the "shiploaderID" attribute value from the current element:
		const char * iShiploaderID = nullptr;
		iShiploaderID = pElement->Attribute("shiploaderID");
		if (iShiploaderID == nullptr)
			return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
		string shiploaderID = iShiploaderID;

		//Extracts the "time" attribute value from the current element:
		double time = 0.0; //I'm not sure if we should use doubles. We might be better off using floats, since we're going to be extracting a LOT of data.
		tinyxml2::XMLError eResult = pElement->QueryDoubleAttribute("time", &time);
		checkXMLResult(eResult);

		//Extracts the "pos" attribute value from the current element:
		double pos = 0.0; //Same potential issue as with the "time" attribute
		eResult = pElement->QueryDoubleAttribute("pos", &pos);
		checkXMLResult(eResult);

		string elementName = pElement->Value();

		//This is to extract the above information into an object:
		CCTShipLoaderLogEvent * nextEvent = new CCTShipLoaderLogEvent(elementName, shiploaderID, time, pos);

		if (elementName != "SlOnMove" && elementName != "SlOnStopMove" && elementName != "SlWrapUp") {
			//This carries out information extraction for the bits of information
			//that only need to be used for some elements:
			if (elementName == "SlStartVesselLoad") {
				int vesselID = -1;
				eResult = pElement->QueryIntAttribute("vesselID", &vesselID);
				checkXMLResult(eResult);

				nextEvent->setVesselID(vesselID);
			}
			else {
				//This is for when the event is either a "SlLoadOpStart", "SlLoadStart", "SlLoadComp" or "SlLoadOpComp":
				const char * iStockpileID = nullptr;
				iStockpileID = pElement->Attribute("stockpileID");
				if (iStockpileID == nullptr)
					return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
				string stockpileID = iStockpileID;

				nextEvent->setStockpileID(stockpileID);

				if (elementName == "SlLoadComp" || elementName == "SlLoadOpComp") {
					double amount = 0.0;
					eResult = pElement->QueryDoubleAttribute("amount", &amount);
					checkXMLResult(eResult);

					nextEvent->setAmount(amount);
				}
			}
		}

		//This places the event into the vector:
		events.push_back(*nextEvent);

		//Moves the element pointer to the next event element:
		pElement = pElement->NextSiblingElement();
	}


	//Serialize the vector of events to a binary file:
	//serialize("CCTShipLoaderLog", events);
	serialize("CCTShipLoaderLog", events);

	return tinyxml2::XML_SUCCESS;
}

//Data extraction for the CCTShipLoaderLog XML file:
tinyxml2::XMLError DataExtractor::extractKCTReclaimerLogData() {
	//The vector which will hold all of the events from the one XML file:
	vector<KCTReclaimerLogEvent> events;

	while (pElement != nullptr) {
		//This carries out the extraction for the bits of data that need to be extracted from every element:

		//Extracts the "reclaimerID" attribute value from the current element:
		const char * iReclaimerID = nullptr;
		iReclaimerID = pElement->Attribute("reclaimerID");
		if (iReclaimerID == nullptr)
			return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
		string reclaimerID = iReclaimerID;

		//Extracts the "time" attribute value from the current element:
		double time = 0.0;
		tinyxml2::XMLError eResult = pElement->QueryDoubleAttribute("time", &time);
		checkXMLResult(eResult);

		//Extracts the "pos" attribute value from the current element:
		double pos = 0.0;
		eResult = pElement->QueryDoubleAttribute("pos", &pos);
		checkXMLResult(eResult);

		string elementName = pElement->Value();

		//This is to extract the above information into an object:
		KCTReclaimerLogEvent * nextEvent = new KCTReclaimerLogEvent(elementName, reclaimerID, time, pos);

		if (elementName != "RecOnMove" && elementName != "RecOnStopMove" && elementName != "RecMaintStart" && elementName != "RecMaintComp" && elementName != "RecWrapUp") {
			//This carries out information extraction for the bits of information
			//that only need to be used for some elements:
			const char * iStockpileID = nullptr;
			iStockpileID = pElement->Attribute("stockpileID");
			if (iStockpileID == nullptr)
				return tinyxml2::XML_ERROR_PARSING_ATTRIBUTE;
			string stockpileID = iStockpileID;

			nextEvent->setStockpileID(stockpileID);

			if (elementName == "RecComp" || elementName == "RecOpComp" || elementName == "RecDoubleHandleComp" || elementName == "RecDoubleHandleOpComp") {
				double amount = 0.0;
				eResult = pElement->QueryDoubleAttribute("amount", &amount);
				checkXMLResult(eResult);

				nextEvent->setAmount(amount);
			}
		}

		//This places the event into the vector:
		events.push_back(*nextEvent);

		//Moves the element pointer to the next event element:
		pElement = pElement->NextSiblingElement();
	}

	//Serialize the vector of events to a binary file:
	serialize("KCTReclaimerLog", events);

	return tinyxml2::XML_SUCCESS;
}