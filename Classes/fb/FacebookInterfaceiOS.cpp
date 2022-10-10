//
//  FacebookInterfaceiOS.cpp
//  HiHigh
//
//  Created by geek on 2014. 7. 15..
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "FacebookInterfaceiOS.h"
#include "../../proj.ios/FacebookViewController.h"

#include "../view/MainMenuScene.h"
#include "../view/SettingPopup.h"
#include "../view/RankingView.h"

void FacebookInterfaceiOS::checkSession() {


	FacebookViewController* facebook = [FacebookViewController sharedFacebook];
	
	bool isLoged = facebook.isLogined;
	
	if (!isLoged) {
		CCUserDefault::sharedUserDefault()->setBoolForKey(FACEBOOK_CONNECT,false);
	}
}

FacebookInterfaceiOS::FacebookInterfaceiOS()
{
	
}
FacebookInterfaceiOS::~FacebookInterfaceiOS()
{
}

void FacebookInterfaceiOS::callbackFacebookiOS(string result)
{

    
	switch (mCbIndex) {
		case Facebook::LOGIN_REQUEST:
		{
			MainMenuScene::facebookCallback(Facebook::LOGIN_REQUEST, result);
		}
			break;
		case Facebook::FRIENDS_REQUEST:
		{
			MainMenuScene::facebookCallback(Facebook::FRIENDS_REQUEST, result);
		}
			break;
		case Facebook::LOGOUT_REQUEST:
		{
            SettingPopup::facebookCallback(Facebook::LOGOUT_REQUEST, "Logout");
		}
			break;
		case Facebook::INVITE_REQUEST:
		{
			RankingView::facebookCallback(mCbIndex, result);
		}
		case Facebook::SHARED_REQUEST:
		case Facebook::SHARED_CANCEL:
		{
			RankingView::facebookCallback(mCbIndex, result);
		}
			break;
		default:
			break;
	}
}

void FacebookInterfaceiOS::callbackFacebookError(string result)
{
	switch (mCbIndex) {
		case Facebook::LOGIN_REQUEST:
		{
			MainMenuScene::facebookErrorCallback(Facebook::LOGIN_REQUEST, result);
		}
			break;
		case Facebook::FRIENDS_REQUEST:
		{
			MainMenuScene::facebookErrorCallback(Facebook::FRIENDS_REQUEST, result);
		}
			break;
		case Facebook::LOGOUT_REQUEST:
		{
			SettingPopup::facebookErrorCallback(Facebook::LOGOUT_REQUEST, result);
		}
			break;
		case Facebook::INVITE_REQUEST:
		{
			RankingView::facebookErrorCallback(mCbIndex, result);
		}
		case Facebook::SHARED_REQUEST:
		case Facebook::SHARED_CANCEL:
		{
			RankingView::facebookErrorCallback(mCbIndex, result);
		}
			break;
		default:
			break;
	}
}
void FacebookInterfaceiOS::setIndex(Facebook::REQUEST_TYPE index)
{
	mCbIndex = index;
}

void FacebookInterfaceiOS::login(Facebook::REQUEST_TYPE cbIndex, CCString scope)
{
	mCbIndex = cbIndex;
	
	[[FacebookViewController sharedFacebook] login];
}

void FacebookInterfaceiOS::logOut(Facebook::REQUEST_TYPE cbIndex, CCString scope)
{
	mCbIndex = cbIndex;
	
	[[FacebookViewController sharedFacebook] logout];
}

void FacebookInterfaceiOS::friends(Facebook::REQUEST_TYPE cbIndex, CCString scope)
{
	mCbIndex = cbIndex;
	
	[[FacebookViewController sharedFacebook] friends];
}

void FacebookInterfaceiOS::publishFeed(Facebook::REQUEST_TYPE cbIndex, cocos2d::CCString scope)
{
	mCbIndex = cbIndex;
	const char * str = scope.getCString();
	
	NSString *score = [NSString stringWithUTF8String:str];
	
	[[FacebookViewController sharedFacebook] publishFeed:score];
}

void FacebookInterfaceiOS::inviteFriends(Facebook::REQUEST_TYPE cbIndex, cocos2d::CCString scope)
{
	mCbIndex = cbIndex;
//	const char * str = scope.getCString();
	
	[[FacebookViewController sharedFacebook] inviteFriends];
}
#endif
