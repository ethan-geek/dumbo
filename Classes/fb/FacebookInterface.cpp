/*
 * FacebookInterface.cpp
 *
 *  Created on: 2014. 6. 30.
 *      Author: geek
 */






#include "./FacebookInterface.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#endif
#include "../view/MainMenuScene.h"
#include "../view/SettingPopup.h"
#include "../view/ClearPopup.h"
#include "../view/RankingView.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

extern "C"
{
void Java_net_atgame_dumbo_FacebookConnectPlugin_nativeCallback(JNIEnv*  env, jobject thiz, jint cbIndex,jstring params)
{
	if (params != NULL)
	{
		const char* str;
		str = env->GetStringUTFChars(params, 0);
		string tstr(str);

		switch (cbIndex) {
		case 0:
		{
			MainMenuScene::facebookCallback(Facebook::LOGIN_REQUEST, tstr);
		}
			break;

		case 1:
		{
			MainMenuScene::facebookCallback(Facebook::FRIENDS_REQUEST, tstr);
		}
			break;
		case 2:
		{
			SettingPopup::facebookCallback(Facebook::LOGOUT_REQUEST, tstr);
		}
			break;
		case 3:
		{
			RankingView::facebookCallback(Facebook::INVITE_REQUEST, tstr);
		}
			break;
		case 4:
		{
			RankingView::facebookCallback(Facebook::SHARED_REQUEST, tstr);
		}
			break;
		case 5:
		{
			SettingPopup::facebookCallback(Facebook::SETTING_LOGIN_REQUEST, tstr);
		}
			break;
		case 7:
		{
			RankingView::facebookCallback(Facebook::SHARED_CANCEL, tstr);
		}
			break;
		default:
			break;
		}

	}
	else
	{
		CCLog("params == NULL");
		std::string tstr = "";

	}
}
void Java_net_atgame_dumbo_FacebookConnectPlugin_nativeErrorCallback(JNIEnv*  env, jobject thiz, jint cbIndex,jstring params)
{
	if (params != NULL)
		{
			const char* str;
			str = env->GetStringUTFChars(params, 0);
			string tstr(str);

			switch (cbIndex) {
			case 0:
			{
				MainMenuScene::facebookErrorCallback(Facebook::LOGIN_REQUEST, tstr);
			}
			break;

			case 1:
			{
				MainMenuScene::facebookErrorCallback(Facebook::FRIENDS_REQUEST, tstr);
			}
			break;
			case 2:
			{
				SettingPopup::facebookErrorCallback(Facebook::LOGOUT_REQUEST, tstr);
			}
			break;
			case 3:
			{
				RankingView::facebookErrorCallback(Facebook::INVITE_REQUEST, tstr);
			}
			break;
			case 4:
			{
				RankingView::facebookErrorCallback(Facebook::SHARED_REQUEST, tstr);
			}
			break;
			case 5:
			{
				SettingPopup::facebookErrorCallback(Facebook::SETTING_LOGIN_REQUEST, tstr);
			}
				break;
			default:
				break;
			}

		}
		else
		{
			CCLog("params == NULL");
			std::string tstr = "";

		}
}
};

jboolean FacebookInterface::IsLoggedIn()
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
			, "net/atgame/dumbo/FacebookConnectPlugin"
			, "IsLoggedIn"
			, "()Z"))
	{
		jboolean retV = t.env->CallStaticBooleanMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);

		return retV;
	}
}

void FacebookInterface::login(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"login","net/atgame/dumbo/FacebookConnectPlugin");
}

void FacebookInterface::logout(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"logout","net/atgame/dumbo/FacebookConnectPlugin");
}
void FacebookInterface::friends(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"getFriends","net/atgame/dumbo/FacebookConnectPlugin");
}

void FacebookInterface::publishFeed(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"postStatus","net/atgame/dumbo/FacebookPostPlugin");
}

void FacebookInterface::photoFeedShared(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"photoFeedShared","net/atgame/dumbo/FacebookConnectPlugin");
}

void FacebookInterface::inviteFriends(Facebook::REQUEST_TYPE cbIndex, const char* scope)
{
	FacebookInterface::callFacebookConnect(cbIndex,scope,"inviteFriends","net/atgame/dumbo/FacebookConnectPlugin");
}


void FacebookInterface::callFacebookConnect(Facebook::REQUEST_TYPE cbIndex,const char* scope, const char* callMethodName, const char* className)
{
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t
			, className
			, callMethodName
			, "(ILjava/lang/String;)V"))
	{
		if (scope)
		{
			jstring jeventId = t.env->NewStringUTF(scope);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,jeventId);
			t.env->DeleteLocalRef(jeventId);
		}
		else
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, cbIndex,NULL);
		}
		t.env->DeleteLocalRef(t.classID);
	}
}

#endif
