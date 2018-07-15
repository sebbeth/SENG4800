#include "CCTShipLoaderLogEvent.h"
#include "stdafx.h"

CCTShipLoaderLogEvent::CCTShipLoaderLogEvent() {

}

CCTShipLoaderLogEvent::CCTShipLoaderLogEvent(string eventName, string shiploaderID, double time, double pos) {
	_eventName = eventName;
	_shiploaderID = shiploaderID;
	_time = time;
	_pos = pos;
}

void CCTShipLoaderLogEvent::setEventName(string eventName) {
	_eventName = eventName;
}

string CCTShipLoaderLogEvent::getEventName() {
	return _eventName;
}

void CCTShipLoaderLogEvent::setShiploaderID(string shiploaderID) {
	_shiploaderID = shiploaderID;
}

string CCTShipLoaderLogEvent::getShiploaderID() {
	return _shiploaderID;
}

void CCTShipLoaderLogEvent::setTime(double time) {
	_time = time;
}

double CCTShipLoaderLogEvent::getTime() {
	return _time;
}

void CCTShipLoaderLogEvent::setPos(double pos) {
	_pos = pos;
}

double CCTShipLoaderLogEvent::getPos() {
	return _pos;
}

void CCTShipLoaderLogEvent::setVesselID(int vesselID) {
	_vesselID = vesselID;
}

int CCTShipLoaderLogEvent::getVesselID() {
	return _vesselID;
}

void CCTShipLoaderLogEvent::setStockpileID(string stockpileID) {
	_stockpileID = stockpileID;
}

string CCTShipLoaderLogEvent::getStockpileID() {
	return _stockpileID;
}

void CCTShipLoaderLogEvent::setAmount(double amount) {
	_amount = amount;
}

double CCTShipLoaderLogEvent::getAmount() {
	return _amount;
}