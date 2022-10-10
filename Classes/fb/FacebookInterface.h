/*
 * FacebookInterface.h
 *
 *  Created on: 2014. 6. 30.
 *      Author: geek
 */

#if !defined(FACEBOOKINTERFACE_H_)
#define FACEBOOKINTERFACE_H_

#include "../common/HiHighCommon.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "../platform/android/jni/JniHelper.h"


USING_NS_CC;

class FacebookInterface {
public:

	static jboolean IsLoggedIn();

	static void login(Facebook::REQUEST_TYPE cbIndex, const char* scope);
	static void logout(Facebook::REQUEST_TYPE cbIndex, const char* scope);
	static void friends(Facebook::REQUEST_TYPE cbIndex, const char* scope);
	static void publishFeed(Facebook::REQUEST_TYPE cbIndex, const char* scope);
	static void photoFeedShared(Facebook::REQUEST_TYPE cbIndex, const char* scope);
	static void inviteFriends(Facebook::REQUEST_TYPE cbIndex, const char* scope);

	static void callFacebookConnect(Facebook::REQUEST_TYPE cbIndex,const char* scope, const char* callMethodName, const char* className);
};
#endif
#endif /* FACEBOOKINTERFACE_H_ */
