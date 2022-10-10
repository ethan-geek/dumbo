//
//  HeartChecker.cpp
//  HiHigh
//
//  Created by insanity on 2014. 4. 24..
//
//

#include "HeartChecker.h"
#include "../dao/HiHighDao.h"

HeartChecker * g_instance = NULL;

struct cc_timeval now;

HeartChecker* HeartChecker::sharedHeartChecker() {
    
    if (g_instance == NULL) {
        g_instance = new HeartChecker();
    }
    return g_instance;
}

HeartChecker::~HeartChecker() {
	this->unschedule(schedule_selector(HeartChecker::update));
}

void HeartChecker::setInterval(long interval, CCLabelTTF * count, CCLabelTTF * time) {

	

    _originInterval = interval;
	_heartCount = AGApplication::GetInstance()->getUserInfo()->getHeartInfo()->getHeartCount();
    _heartLabel = count;
    _timeLabel = time;

}

void HeartChecker::start() {
    
	HeartInfo* info = AGApplication::GetInstance()->getUserInfo()->getHeartInfo();
	time_t lastTime = atol(info->getChargeHeartTime().c_str());
	
	
    time(&_start);
	
    

	long differTime = _start - lastTime ;
	_currentInterval = _originInterval - differTime % _originInterval;

	int plusHeartCount = differTime / _originInterval;
	_heartCount += plusHeartCount;
	if(_heartCount > 5) {
		_heartCount = 5;
	}
	info->setHeartCount(_heartCount);
	
	showTime();

	
	this->schedule(schedule_selector(HeartChecker::update),0.5);
	
}


void HeartChecker::showTime() {
    
    _minute = _currentInterval / 60;
    _second = _currentInterval % 60;
    
    static char temp[8];
    sprintf(temp, "%d",_heartCount);
    _heartLabel->setString(temp);
    
	if(_heartCount < 5 ) {
		sprintf(temp, "%d:%02d",_minute,_second);
		_timeLabel->setString(temp);
	}
	else {
		_timeLabel->setString(" full ");
	}

	
    
}

void HeartChecker::stop() {
    this->unschedule(schedule_selector(HeartChecker::update));
}


void HeartChecker::update(float dt) {
    
	_heartCount = AGApplication::GetInstance()->getUserInfo()->getHeartInfo()->getHeartCount();

	if(_heartCount >= 5) {
		_currentInterval = _originInterval;
		time(&_current);
		_start = _current;
		HeartInfo* info = AGApplication::GetInstance()->getUserInfo()->getHeartInfo();
		info->increaseHeart();
		return;
	}

    time(&_current);
    
	_currentInterval = _currentInterval - (_current - _start) ;
    _start = _current;
    
    if (_currentInterval <= 0) {
        _currentInterval = _originInterval;
        _heartCount++;

		HeartInfo* info = AGApplication::GetInstance()->getUserInfo()->getHeartInfo();
		info->increaseHeart(_heartCount);

        if (_heartCount == 5) {
            _heartCount = 5;
        }
    }
    showTime();
}
