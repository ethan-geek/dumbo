/*
 * HHNetworkReceiver.h
 *
 *  Created on: 2014. 10. 30.
 *      Author: geek
 */

#ifndef HHNETWORKRECEIVER_H_
#define HHNETWORKRECEIVER_H_

#include "../common/HiHighCommon.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../platform/android/jni/JniHelper.h"

class HHNetworkReceiver: public CCObject{
public:
//	HHNetworkReceiver();
//	virtual ~HHNetworkReceiver();

	static void networkChangeCallback(int status);

	static void networkChangeCheck(NETWORK_STATUS_TYPE type);

	static bool isNetworkConnection();

	
private:
	static NETWORK_STATUS_TYPE getNetworkStatusType(int status);
};

#endif

#endif /* HHNETWORKRECEIVER_H_ */


