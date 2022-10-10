/*
 * HHNetworkReceiver.cpp
 *
 *  Created on: 2014. 10. 30.
 *      Author: geek
 */

#include "HHNetworkReceiver.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>


void HHNetworkReceiver::networkChangeCallback(int status)
{
	//	CCLOG("networkCallback Code = %d",status);



	//	CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
	//	CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
	//
	//	//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//	layer->scheduleOnce(schedule_selector(HHNetworkReceiver::networkChangeCheck), 0.1);
	//	//#endif
	//	CCLOG("valueStatus = %d", HHNetworkReceiver::getNetworkStatusType());
	HHNetworkReceiver::networkChangeCheck(getNetworkStatusType(status));

}

NETWORK_STATUS_TYPE HHNetworkReceiver::getNetworkStatusType(int status)
{
	NETWORK_STATUS_TYPE mStatusType = TYPE_NOT_CONNECTED;

	switch (status) {
	case 0:
		mStatusType = TYPE_NOT_CONNECTED;
		break;
	case 1:
		mStatusType = TYPE_WIFI;
		break;
	case 2:
		mStatusType = TYPE_MOBILE;
		break;
	default:
		mStatusType = TYPE_NOT_CONNECTED;
		break;
	}

	return mStatusType;
}

void HHNetworkReceiver::networkChangeCheck(NETWORK_STATUS_TYPE type)
{
	CCLOG("###################################################################");
	CCLOG("networkChange statusType = %d " , type);
	CCLOG("###################################################################");
}





bool HHNetworkReceiver::isNetworkConnection()
{
	bool returnValue;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
			, "net/atgame/dumbo/NetworkConnetionCheck"
			, "isNetworkConnection"
			, "()Z"))
	{
		jboolean retV = t.env->CallStaticBooleanMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);
		
		returnValue = retV;
		return returnValue;
	}
#endif
	return returnValue;
}

extern "C"
{
void Java_net_atgame_dumbo_NetworkChangeReceiver_nativeNetworkChangeCallback(JNIEnv*  env, jobject thiz, jint statusCode)
{
	HHNetworkReceiver::networkChangeCallback(statusCode);
}
};
#endif

