//
//  HeartChecker.h
//  HiHigh
//
//  Created by insanity on 2014. 4. 24..
//
//

#ifndef __HiHigh__HeartChecker__
#define __HiHigh__HeartChecker__

#include "HiHighCommon.h"

class HeartChecker : CCNode {
public:
    
    static HeartChecker * sharedHeartChecker();
    void setInterval(long interval, CCLabelTTF * count, CCLabelTTF * time);
    HeartChecker() {}
	~HeartChecker();
    void start();
    void stop();
    void update(float dt);
    
    void showTime();
    
    time_t _start;
    time_t _current;
    
    long _currentInterval;
    long _originInterval;
    
    int _minute;
    int _second;
    
    int _heartCount;
    
    CCLabelTTF * _heartLabel ;
    CCLabelTTF * _timeLabel ;
};

#endif /* defined(__HiHigh__HeartChecker__) */
