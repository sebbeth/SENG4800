#pragma once

#ifndef CCTSHIPLOADERLOGEVENT_H
#define CCTSHIPLOADERLOGEVENT_H

#include <string>

using namespace std;

class CCTShipLoaderLogEvent{
	public:
		CCTShipLoaderLogEvent();
		CCTShipLoaderLogEvent(string eventName, string shiploaderID, double time, double pos);

		//Setters for the member variables:
		void setEventName(string eventName);
		void setShiploaderID(string shiploaderID);
		void setTime(double time);
		void setPos(double pos);
		void setVesselID(int vesselID);
		void setStockpileID(string stockpileID);
		void setAmount(double amount);

		//Getters for the member variables:
		string getEventName();
		string getShiploaderID();
		double getTime();
		double getPos();
		int getVesselID();
		string getStockpileID();
		double getAmount();

		//Lets Cereal know which variables to serialise:
		template<class Archive>
		void serialize(Archive & archive) {
			//Serlialise them by passing them to the archive:
			archive(_eventName, _shiploaderID, _time, _pos, _vesselID, _stockpileID, _amount);
		}
	private:
		//Varibles that every event needs:
		string _eventName;
		string _shiploaderID;
		double _time;
		double _pos;

		//Variables only some events need:
		int _vesselID;
		string _stockpileID;
		double _amount;
};

#endif