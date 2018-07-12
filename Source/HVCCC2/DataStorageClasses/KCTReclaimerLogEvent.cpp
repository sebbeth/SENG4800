#include "KCTReclaimerLogEvent.h"
#include "stdafx.h"

KCTReclaimerLogEvent::KCTReclaimerLogEvent() {

}

KCTReclaimerLogEvent::KCTReclaimerLogEvent(string eventName, string reclaimerID, double time, double pos) {
	_eventName = eventName;
	_reclaimerID = reclaimerID;
	_time = time;
	_pos = pos;
}

void KCTReclaimerLogEvent::setEventName(string eventName) {
	_eventName = eventName;
}

string KCTReclaimerLogEvent::getEventName() {
	return _eventName;
}

void KCTReclaimerLogEvent::setReclaimerID(string reclaimerID) {
	_reclaimerID = reclaimerID;
}

string KCTReclaimerLogEvent::getReclaimerID() {
	return _reclaimerID;
}

void KCTReclaimerLogEvent::setTime(double time) {
	_time = time;
}

double KCTReclaimerLogEvent::getTime() {
	return _time;
}

void KCTReclaimerLogEvent::setPos(double pos) {
	_pos = pos;
}

double KCTReclaimerLogEvent::getPos() {
	return _pos;
}

void KCTReclaimerLogEvent::setStockpileID(string stockpileID) {
	_stockpileID = stockpileID;
}

string KCTReclaimerLogEvent::getStockpileID() {
	return _stockpileID;
}

void KCTReclaimerLogEvent::setAmount(double amount) {
	_amount = amount;
}

double KCTReclaimerLogEvent::getAmount() {
	return _amount;
}