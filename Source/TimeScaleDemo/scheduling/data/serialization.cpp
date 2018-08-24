#include "serialization.h"
bool serialize(const StateMapTuple& source, const std::string& destinationPath) {
	return
		serialize(std::get<std::map<std::string, std::vector<DumpStationState>>>(source), destinationPath + "/DumpStation")
		&& serialize(std::get<std::map<std::string, std::vector<LoadPointState>>>(source), destinationPath + "/LoadPoint")
		&& serialize(std::get<std::map<std::string, std::vector<ShipLoaderState>>>(source), destinationPath + "/ShipLoader")
		&& serialize(std::get<std::map<std::string, std::vector<SignalState>>>(source), destinationPath + "/Signal")
		&& serialize(std::get<std::map<std::string, std::vector<StockpileState>>>(source), destinationPath + "/Stockpile")
		&& serialize(std::get<std::map<std::string, std::vector<TrainState>>>(source), destinationPath + "/Train")
		&& serialize(std::get<std::map<std::string, std::vector<StackerState>>>(source), destinationPath + "/StackerReclaimer")
		&& serialize(std::get<std::map<int, std::vector<VesselState>>>(source), destinationPath + "/Vessel")
	;
}

bool deserialize(const std::string& sourcePath, StateMapTuple& destination) {
	return
	   deserialize(sourcePath + "/DumpStation", std::get<std::map<std::string, std::vector<DumpStationState>>>(destination))
	&& deserialize(sourcePath + "/LoadPoint", std::get<std::map<std::string, std::vector<LoadPointState>>>(destination))
	&& deserialize(sourcePath + "/ShipLoader", std::get<std::map<std::string, std::vector<ShipLoaderState>>>(destination))
	&& deserialize(sourcePath + "/Signal", std::get<std::map<std::string, std::vector<SignalState>>>(destination))
	&& deserialize(sourcePath + "/Stockpile", std::get<std::map<std::string, std::vector<StockpileState>>>(destination))
	&& deserialize(sourcePath + "/Train", std::get<std::map<std::string, std::vector<TrainState>>>(destination))
	&& deserialize(sourcePath + "/Vessel", std::get<std::map<int, std::vector<VesselState>>>(destination))
	&& deserialize(sourcePath + "/StackerReclaimer", std::get<std::map<std::string, std::vector<StackerState>>>(destination));
}