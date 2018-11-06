/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-11-06 18:17:17.164006
 **/
#include "logStates.h"
#include <string>
#include <ostream>
#include <vector>

//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<DumpstationState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "time" , "trainID" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeDumpstationStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.time), eachState.trainID.nameForBinaryFile() }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<LoadpointsState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "loadpointName" , "time" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeLoadpointsStateType(eachState.type), std::to_string(eachState.amount), eachState.loadpointName, std::to_string(eachState.time) }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<ReclaimerState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "position" , "stockpileID" , "time" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeReclaimerStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.position), eachState.stockpileID.nameForBinaryFile(), std::to_string(eachState.time) }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<ShiploaderState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "position" , "stockpileID" , "time" , "vesselID" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeShiploaderStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.position), eachState.stockpileID.nameForBinaryFile(), std::to_string(eachState.time), eachState.vesselID.nameForBinaryFile() }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<StackerState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "position" , "stockpileID" , "time" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeStackerStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.position), eachState.stockpileID.nameForBinaryFile(), std::to_string(eachState.time) }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<StackerReclaimerState>& data) {
	for (const std::string& eachHeader : { "StateType", "amount" , "position" , "stockpileID" , "time" }) {
		outlet << eachHeader;
		outlet << std::string(std::max(0, 18 - (int)eachHeader.size()), ' ');
		outlet << "\t";
	}
	outlet << "\n";
	for (auto& eachState : data) {
		for (std::string eachAttr : { encodeStackerReclaimerStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.position), eachState.stockpileID.nameForBinaryFile(), std::to_string(eachState.time) }) {
			outlet << eachAttr;
			outlet << std::string(std::max(0, 18 - (int)eachAttr.size()), ' ');
			outlet << "\t";
		}
		outlet << "\n";
	}
	outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<StockpileState>& data) {
    for(const std::string& eachHeader : { "StateType", "amount" , "length" , "machineID" , "padID" , "position" , "time" , "vesselID" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeStockpileStateType(eachState.type), std::to_string(eachState.amount), std::to_string(eachState.length), eachState.machineID.nameForBinaryFile(), eachState.padID, std::to_string(eachState.position), std::to_string(eachState.time), eachState.vesselID.nameForBinaryFile() }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<TrainMovementState>& data) {
    for(const std::string& eachHeader : { "StateType", "cycleID" , "direction" , "sectionID" , "speed" , "time" , "trackID" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeTrainMovementStateType(eachState.type), std::to_string(eachState.cycleID), eachState.direction, eachState.sectionID, std::to_string(eachState.speed), std::to_string(eachState.time), eachState.trackID }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}


//this prints in a fairly neatly tabulated format, with padding designed for doubles
void logStates(std::ostream& outlet, const std::vector<VesselState>& data) {
    for(const std::string& eachHeader : { "StateType", "isTidal" , "metermark" , "terminalID" , "time" , "tugs" }) {
        outlet << eachHeader;
        outlet << std::string(std::max(0, 30-(int)eachHeader.size()), ' ');
        outlet << "\t";
    }
    outlet << '\n';
    for(auto& eachState : data) {
        for(std::string eachAttr : { encodeVesselStateType(eachState.type), std::to_string(eachState.isTidal), std::to_string(eachState.metermark), eachState.terminalID, std::to_string(eachState.time), std::to_string(eachState.tugs) }) {
            outlet << eachAttr;
            outlet << std::string(std::max(0, 30-(int)eachAttr.size()), ' ');
            outlet << "\t";
        }
        outlet << "\n";
    }
    outlet << "\n";
}