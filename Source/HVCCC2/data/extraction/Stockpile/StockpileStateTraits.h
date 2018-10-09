/**
 * This file contains code generated from/to be compatible with available XML data as at 2018-10-07 18:18:44.676555
 **/
#pragma once
#include "../StateTraits.h"
#include "StockpileState.h"
template<>
class StateTraits<StockpileState> {
public:
    static StockpileState initializeFromEvent(const StockpileEvent& src) {
		//see if the initial event is something that leaves the initial state; (addresses issue where some entities don't have their own creation event in the xml); still just a quickfix stub though:
        auto tentativeState = StockpileState::determineNextType(StockpileStateType::Idle, src.type);

        return {src.id, tentativeState != StockpileStateType::Invalid ? tentativeState : StockpileStateType::Idle, src.hasAmount() ? src.amount : 0, src.length, src.machineID, src.padID, src.position, src.time, src.vesselID};
    }

    static StockpileState generateNextState(const StockpileState& current, const StockpileEvent& event) {
		StockpileState result = current;
		result.type = StockpileState::determineNextType(current.type, event.type);

        if(event.hasAmount()) {
			switch(event.type) {
				case StockpileEventType::StackComplete:
				case StockpileEventType::StackTransferComplete:
					result.amount += event.amount;
					break;
				case StockpileEventType::ReclaimComplete:
				case StockpileEventType::ReclaimTransferComplete:
					result.amount -= event.amount;
					break;
			}
		}
		else {
			result.amount = current.amount;
		}

        if(event.hasLength()) {
			result.length = event.length;
		}
		else {
			result.length = current.length;
		}

        if(event.hasMachineID()) {
			result.machineID = event.machineID;
        }

        if(event.hasPadID()) {
			result.padID = event.padID;
        }

        if(event.hasPosition()) {
			result.position = event.position;
        }

        if(event.hasTime()) {
			result.time = event.time;
        }

        if(event.hasVesselID()) {
			result.vesselID = event.vesselID;
        }

        return result;
    }
};