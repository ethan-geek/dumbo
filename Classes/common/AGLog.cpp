//
//  AGLog.c
//  HiHigh
//
//  Created by Jackdaw on 2014. 8. 21..
//
//

#include "AGLog.h"
#include "../model/AGDeviceInfo.h"
#include "./DeviceInfoIOSBridge.h"
const char * fileName = "/crash.txt";
#include "../helper/AndroidHelper.h"
#include "./HiHighConnector.h"

void AGLog::readLog(CCObject* object, SEL_HttpResponse pSelector) {
    
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + fileName;
    ifstream input;
    
    input.open(path.c_str(),ios::in);
    
    char buffer[1024];
    string buf = "";

    input.getline(buffer, 1024);
    buf+=buffer;
    
    CCLog("crash??? %s",buf.c_str());
    
    if(buf != "ok" && buf != "") {
       sendLog(buf,object, pSelector);
    } else {
        
    }
    
    input.close();
}

void AGLog::sendLog(string log, CCObject* object, SEL_HttpResponse pSelector) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AGDeviceInfo d = getDeviceInfoAndroid();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    AGDeviceInfo d = getDeviceInfoIOS();

#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	d.log = log;
    HiHighConnector::sharedConnector()->sendCrashLog(d,object,pSelector);
#endif

    
}


