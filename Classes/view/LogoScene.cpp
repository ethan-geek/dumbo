///////////////////////////////////////////////////////////
//  LogoScene.cpp
//  Implementation of the Class LogoScene
//  Created on:      19-3-2014 ���� 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "LogoScene.h"
#include "../Common/XmlLoader.h"
#include "../dao/HiHighDao.h"
#include "../common/HiHighConnector.h"
#include "MainMenuScene.h"
#include "../network/HHNetwork.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../fb/FacebookInterface.h"
#include "../helper/AndroidHelper.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../network/HHNetworkReachability.h"
#include "../fb/FacebookInterfaceiOS.h"
#import "AdViewController.h"
#endif

//
//#define DEBUG_LOG_NO		
//
//#ifdef DEBUG_LOG
//#define CCLog	AGUtil::Log
//#endif

bool LogoScene::init() {
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0), visibleSize.width, visibleSize.height))
    {
        return false;
    }

	CCSprite* logo = CCSprite::create("parts/atgame_logo.png");
    
    logo->setPosition(ccp(visibleSize.width / 2 - logo->getContentSize().width / 2,
                                visibleSize.height / 2 - logo->getContentSize().height / 2));
    logo->setAnchorPoint(ccp(0,0));
    this->addChild(logo);
    this->scheduleOnce(schedule_selector(LogoScene::loadResourcesStart), 1);
    return true;
}

CCScene* LogoScene::scene() {
    CCScene *scene = CCScene::create();
    LogoScene *layer = LogoScene::create();
    scene->addChild(layer);
    return scene;
}

void LogoScene::loadResourcesStart(float dt) {
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    FacebookInterfaceiOS::checkSession();
    
    AdViewController *adVC = [AdViewController sharedInstance];
    [adVC loadAdView];
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    android_initBanner();

#endif
	AGApplication::GetInstance()->initRand();
	loadMusic();
    loadSound();
	loadResource();
    //loadResourcesEnded();
	loadUserInfo();
}

#include "../common/XmlCreator.h"

void LogoScene::loadResourcesEnded() {
    
	CCLog("loadResourcesEnded %s", XmlCreator::getInstance()->convertString(AGApplication::GetInstance()->getUserInfo()).c_str());

	SceneManager::replaceScene("MainMenuScene");

    /*CCScene* main = MainMenuScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
    CCDirector::sharedDirector()->replaceScene(transition);*/
    
    
}

void LogoScene::loadUserInfo()
{
    
	AGApplication::GetInstance()->getHiHighDao()->init();

	if(AGApplication::GetInstance()->checkFacebook() == false || HHNetwork::GetInstance()->getNetworkStatus() == false) {
		loadResourcesEnded();
		return;
	}

	HiHighConnector::sharedConnector()->requestUserInfo(AGApplication::GetInstance()->getUserInfo()->getFacebookId(), this, httpresponse_selector(LogoScene::onHttpRequestCompleted));

}
void LogoScene::loadMusic() {
    
    
    HiHighAudio::sharedAudio()->musics["game_bgm"] = "audio/music/bgm_140404_1537.mp3";
    HiHighAudio::sharedAudio()->musics["menu_bgm"] = "audio/music/menu_bgm.mp3";
    HiHighAudio::sharedAudio()->musics["ending_bgm"] = "audio/music/ending_bgm.mp3";
    
    
}

void LogoScene::loadSound() {
    
    
    
    HiHighAudio::sharedAudio()->sounds["trap"] = "audio/sound/trap.mp3";
    HiHighAudio::sharedAudio()->sounds["button"] = "audio/sound/btn_touch.mp3";
	HiHighAudio::sharedAudio()->sounds["coin"] = "audio/sound/coin.mp3";
  	HiHighAudio::sharedAudio()->sounds["footbar"] = "audio/sound/footbar.mp3";
  	HiHighAudio::sharedAudio()->sounds["fakefootbar"] = "audio/sound/fakefootbar.mp3";
   	HiHighAudio::sharedAudio()->sounds["fullcoin"] = "audio/sound/fullcoin.mp3";
    HiHighAudio::sharedAudio()->sounds["popup"] = "audio/sound/popup.mp3";
	HiHighAudio::sharedAudio()->sounds["superitem"] = "audio/sound/superitem.mp3";
    
    HiHighAudio::sharedAudio()->sounds["starfish"] = "audio/sound/starfish.mp3";
    HiHighAudio::sharedAudio()->sounds["weight"] = "audio/sound/weight.mp3";
    HiHighAudio::sharedAudio()->sounds["shield"] = "audio/sound/shield.mp3";
    HiHighAudio::sharedAudio()->sounds["magnet"] = "audio/sound/magnet.mp3";
    HiHighAudio::sharedAudio()->sounds["score"] = "audio/sound/score.mp3";    
    HiHighAudio::sharedAudio()->sounds["ink"] = "audio/sound/ink.mp3";
    HiHighAudio::sharedAudio()->sounds["scream"] = "audio/sound/scream.mp3";
    
    
}

void LogoScene::loadResource() {

    
    
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background/bg_fill.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background/bg_parts.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("button/button.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("effect/effect.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("icon/icon.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("parts/parts.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("interaction/interaction.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("background/background.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("parallax/pallax.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("interaction/interaction_ani.plist");
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("character/character_ani.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("character/character_ani_dumbo.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("silhouette_resource.plist");
	
	
}


void LogoScene::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	   
    
    HiHighConnector* conn = HiHighConnector::sharedConnector();

	CCLog("logo Scene onHttpRequestCompleted");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCLOG("HttpClient TimeOut = %d",client->getTimeoutForConnect());
#endif

	if(conn->checkRespose(response) == false) {
		loadResourcesEnded();
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	CCLog("logo Scene |%s|", resStr.c_str());

	if(resStr.compare("") == 0) {
		conn->sendUserInfo(AGApplication::GetInstance()->getUserInfo(), NULL, httpresponse_selector(AGUtil::onVoidCompleted));
		loadResourcesEnded();
		return;
	}

	UserInfo* serverUserInfo = HiHighJsonConvecter::sharedJsonConverter()->convertUserInfo(resStr);

	UserInfo* localUserInfo = AGApplication::GetInstance()->getUserInfo();

	if(localUserInfo->getTotalGold() <= serverUserInfo->getTotalGold() ) {
		
		serverUserInfo->setProfileUrl(localUserInfo->getProfileUrl());
		serverUserInfo->setName(localUserInfo->getName());
		delete localUserInfo;
		AGApplication::GetInstance()->setUserInfo(serverUserInfo);
		AGApplication::GetInstance()->getHiHighDao()->updateCurrentStage(1);
	}
	else {
		delete serverUserInfo;
	}


	loadResourcesEnded();
        
}
