///////////////////////////////////////////////////////////
//  HeartInfo.cpp
//  Implementation of the Class HeartInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "HeartInfo.h"
#include "../dao/HiHighDao.h"

HeartInfo::HeartInfo() : _heartCount(4){

	time_t now;
	time(&now);
    
	setChargeHeartTime(now);

}



HeartInfo::~HeartInfo(){

}

void HeartInfo::setChargeHeartTime(string time)
{
	this->_chargeHeartTime = time;
}

void HeartInfo::setChargeHeartTime(long time)
{
	ostringstream os;
	os << time;
	this->_chargeHeartTime = os.str();
	os.clear();

}




void HeartInfo::setHeartCount(int heartCount)
{
	this->_heartCount = heartCount;
}

string HeartInfo::getChargeHeartTime()
{
	return this->_chargeHeartTime;
}

long HeartInfo::getChargeHeartTimeLong() {
	return atol(_chargeHeartTime.c_str());
}


int HeartInfo::getHeartCount()
{
	return this->_heartCount;
}


void HeartInfo::increaseHeart() {

	if(_heartCount < 5) {
		++_heartCount;
	}

	
	saveXml();
}
void HeartInfo::increaseHeart(int heartCount) {

	_heartCount = heartCount;

	saveXml();
}
bool HeartInfo::decreaseHeart() {

	if(_heartCount <=0 ) {
		return false;
	}

	--_heartCount;

	saveXml();

	return true;

}


void HeartInfo::saveXml() {
	
	time_t now;
	time(&now);
    
	setChargeHeartTime(now);
	AGApplication::GetInstance()->getHiHighDao()->updateHeartInfo(this);
}
