//
//  FacebookInterfaceiOS.h
//  HiHigh
//
//  Created by geek on 2014. 7. 15..
//
//

#ifndef __HiHigh__FacebookInterfaceiOS__
#define __HiHigh__FacebookInterfaceiOS__



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "../common/HiHighCommon.h"

USING_NS_CC;

class FacebookInterfaceiOS
{
public:
	
	virtual ~FacebookInterfaceiOS();
	//Instance using lazy initialization
    static FacebookInterfaceiOS& sharedFacebookiOS()
    {
        static FacebookInterfaceiOS instance;
        return instance;
    }
	
    
    static void checkSession();
    
    
	void callbackFacebookiOS(string result);
	void callbackFacebookError(string result);
	
	
	void setSessionState(int state);
	int getSessionState();
	
	void login(Facebook::REQUEST_TYPE cbIndex, CCString scope);
	
	void logOut(Facebook::REQUEST_TYPE cbIndex, CCString scope);
	
	void friends(Facebook::REQUEST_TYPE cbIndex, CCString scope);
	
	void publishFeed(Facebook::REQUEST_TYPE cbIndex, CCString scope);
	
	void inviteFriends(Facebook::REQUEST_TYPE cbIndex, CCString scope);
	bool isLoggedIn();
	
	void setIndex(Facebook::REQUEST_TYPE index);
	

private:
	
	Facebook::REQUEST_TYPE mCbIndex;
	
	FacebookInterfaceiOS();
};

#endif
#endif /* defined(__HiHigh__FacebookInterfaceiOS__) */
