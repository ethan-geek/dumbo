//
//  HHNetworkReachability.cpp
//  HiHigh
//
//  Created by geek on 2014. 10. 30..
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "HHNetworkReachability.h"
#include "../../proj.ios/Reachability.h"

HHNetworkReachability* HHNetworkReachability::g_NetworkReachability = NULL;

HHNetworkReachability* HHNetworkReachability::GetInstance() {
	if (g_NetworkReachability == NULL)
	{
		g_NetworkReachability = new HHNetworkReachability();
	}
	
	return g_NetworkReachability;
};

HHNetworkReachability::HHNetworkReachability()
{
	Reachability* reachbility = [Reachability reachabilityWithHostname:@"hihigh.atgame.net"];
	
	NetworkStatus networkStatus = [reachbility currentReachabilityStatus];
	mReachabilityStatus = !(networkStatus == NotReachable);
	
	// Internet is reachable
	reachbility.reachableBlock = ^(Reachability*reach)
	{
		// Update the UI on the main thread
		dispatch_async(dispatch_get_main_queue(), ^{
			NSLog(@"Yayyy, we have the interwebs!");
			mReachabilityStatus = true;
		});
	};
	
	// Internet is not reachable
	reachbility.unreachableBlock = ^(Reachability*reach)
	{
		// Update the UI on the main thread
		dispatch_async(dispatch_get_main_queue(), ^{
			mReachabilityStatus = false;
		});
	};
	
	[reachbility startNotifier];
}
bool HHNetworkReachability::isReachability()
{
	return mReachabilityStatus;
}
#endif