//
//  HHNetwork.cpp
//  HiHigh
//
//  Created by geek on 2014. 11. 3..
//
//

#include "HHNetwork.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "HHNetworkReachability.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "HHNetworkReceiver.h"
#endif
HHNetwork* HHNetwork::g_Network = NULL;

HHNetwork* HHNetwork::GetInstance() {
	if (g_Network == NULL)
	{
		g_Network = new HHNetwork();
	}
	
	return g_Network;
};

HHNetwork::HHNetwork()
{

}

bool HHNetwork::getNetworkStatus()
{
	bool returnBool = false;
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	returnBool = HHNetworkReachability::GetInstance()->isReachability();
#endif
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	returnBool = HHNetworkReceiver::isNetworkConnection();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
	returnBool = true;
#endif

	return returnBool;
}