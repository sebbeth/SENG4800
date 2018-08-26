#include "convertData.h"
#include <algorithm>

StateMapTuple convertAll(const EventVectorTuple& source) {
	StateMapTuple destination;
	convertEvents(source,destination, &DumpStationEvent::dumpStationID);
	convertEvents(source, destination, &LoadPointEvent::loadPointID);
	convertEvents(source, destination, &ShipLoaderEvent::shipLoaderID);
	convertEvents(source, destination, &SignalEvent::signalID);
	convertEvents(source, destination, &StockpileEvent::stockpileID);
	convertEvents(source, destination, &TrainEvent::trainID);
	convertEvents(source, destination, &VesselEvent::vesselID);

	//bit of a hack
	EventVectorTuple mergedEventsTuple;
	std::vector<StackerEvent>& mergedEventsVector = std::get<std::vector<StackerEvent>>(mergedEventsTuple);
	mergedEventsVector = std::get<std::vector<StackerEvent>>(source);

	for (ReclaimerEvent eachSrc : std::get<std::vector<ReclaimerEvent>>(source)) {
		StackerEvent eachDest;
		eachDest.type = static_cast<StackerEventType>(eachSrc.type);
		eachDest.amount = eachSrc.amount;
		eachDest.machineID = eachSrc.machineID;
		eachDest.position = eachSrc.position;
		eachDest.stockpileID = eachSrc.stockpileID;
		eachDest.time = eachSrc.time;
		mergedEventsVector.push_back(eachDest);
	}
	
	//sort by time now that they are merged
	std::sort(mergedEventsVector.begin(), mergedEventsVector.end(), [](const StackerEvent& a, const StackerEvent& b) {return a.time < b.time; });
	
	convertEvents(mergedEventsTuple, destination, &StackerEvent::machineID);

	return destination;
}