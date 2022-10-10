//
//  HHNetwork.h
//  HiHigh
//
//  Created by geek on 2014. 11. 3..
//
//

#ifndef __HiHigh__HHNetwork__
#define __HiHigh__HHNetwork__

#include "../common/HiHighCommon.h"
class HHNetwork {
	
public:
	static HHNetwork* g_Network;
	static HHNetwork* GetInstance();
	
	HHNetwork();
	
	bool getNetworkStatus();
};

#endif /* defined(__HiHigh__HHNetwork__) */
