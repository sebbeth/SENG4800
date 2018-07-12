#pragma once

#ifndef KCTRELAIMERLOGEVENT_H
#define KCTRELAIMERLOGEVENT_H

#include <string>

using namespace std;

class KCTReclaimerLogEvent {
public:
	KCTReclaimerLogEvent();
	KCTReclaimerLogEvent(string eventName, string reclaimerID, double time, double pos);

	//Setters for the member variables:
	void setEventName(string eventName);
	void setReclaimerID(string reclaimerID);
	void setTime(double time);
	void setPos(double pos);
	void setStockpileID(string stockpileID);
	void setAmount(double amount);

	//Getters for the member variables:
	string getEventName();
	string getReclaimerID();
	double getTime();
	double getPos();
	string getStockpileID();
	double getAmount();

	//Lets Cereal know which variables to serialise:
	template<class Archive>
	void serialize(Archive & archive) {
		//Serlialise them by passing them to the archive:
		archive(_eventName, _reclaimerID, _time, _pos, _stockpileID, _amount);
	}
private:
	//Varibles that every event needs:
	string _eventName;
	string _reclaimerID;
	double _time;
	double _pos;

	//Variables only some events need:
	string _stockpileID;
	double _amount;
};

#endif