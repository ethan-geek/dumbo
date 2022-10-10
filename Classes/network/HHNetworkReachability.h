//
//  HHNetworkReachability.h
//  HiHigh
//
//  Created by geek on 2014. 10. 30..
//
//

#ifndef __HiHigh__HHNetworkReachability__
#define __HiHigh__HHNetworkReachability__

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../common/HiHighCommon.h"

class HHNetworkReachability {
	
public:
	
	HHNetworkReachability();

	static HHNetworkReachability* g_NetworkReachability;
	
	static HHNetworkReachability* GetInstance();
	
	bool isReachability();
	
private:
	bool mReachabilityStatus;
};

#endif /* (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) end */
#endif /* defined(__HiHigh__HHNetworkReachability__) */
