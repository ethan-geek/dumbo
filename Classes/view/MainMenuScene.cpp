///////////////////////////////////////////////////////////
//  MainMenuScene.cpp
//  Implementation of the Class MainMenuScene
//  Created on:      19-3-2014 ø¿¿¸ 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "MainMenuScene.h"
#include "AbilitiesScene.h"
#include "StageInfoPopup.h"
#include "StageMapScene.h"
#include "ClearPopup.h"
#include "../dao/HiHighDao.h"
#include "../common/HiHighConnector.h"
#include "../network/HHNetwork.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../fb/FacebookInterface.h"
#include "../network/HHNetworkReceiver.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../fb/FacebookInterfaceiOS.h"
#include "../network/HHNetworkReachability.h"
#endif

MainMenuScene* MainMenuScene::g_main = NULL;

MainMenuScene* MainMenuScene::GetInstance() {
	if (g_main == NULL)
	{
		g_main = new MainMenuScene();

	}

	return g_main;
};

CCScene* MainMenuScene::scene()
{

	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	MainMenuScene *layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene

	return scene;
}

CCControlButton* createButton(char* label = NULL) {

	CCScale9Sprite *pScale9Sprite = CCScale9Sprite::create("CloseSelected.png", cocos2d::CCRect(0.0f, 0.0f, 256.0f, 256.0f));



	CCControlButton *pControlButton = NULL;
	if(label != NULL) {

		pControlButton = CCControlButton::create(label, "BUTTON_FONT_BIG", 11);
	}
	else {
		pControlButton = CCControlButton::create(pScale9Sprite);
		pControlButton->setContentSize(pScale9Sprite->getContentSize());
	}

	pControlButton->setContentSize(pScale9Sprite->getContentSize());



	return pControlButton;
}

bool MainMenuScene::init()  {

	if ( !CCLayerColor::initWithColor(ccc4(1,112,180,255)) )
	{
		return false;
	}


	this->setKeypadEnabled(true);

	_pallaxManager.init(this);

	HiHighAudio::sharedAudio()->playMusic("menu_bgm");
	_backAlert = NULL;
	winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *bg = CCSprite::createWithSpriteFrameName("menu_bg.png");
	bg->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	this->addChild(bg);

	this->addJewel(80,650);
	this->addJewel(400,830);
	this->addJewel(510,580);

	CCMenuItemImage *settingBtn = CCMenuItemImage::create("button/icon_setting.png", "button/icon_setting.png", this, menu_selector(MainMenuScene::settingClickListener));
	settingBtn->setScale(1.3);

	CCMenu *settingMenu = CCMenu::create(settingBtn, NULL);
	settingMenu->setPosition(ccp(20 + settingBtn->getContentSize().width / 2, winSize.height - 20 - settingBtn->getContentSize().height / 2));
	this->addChild(settingMenu);

	CCLabelBMFont *title = CCLabelBMFont::create("D U M B O", "fonts/gil_sans_mt_big.fnt");
	title->setAnchorPoint(ccp(0.5, 1));
	title->setContentSize(CCSizeMake(title->getContentSize().width, 150));
	title->setPosition(ccp(winSize.width/2, winSize.height - 340));

	this->addChild(title);

	fbBtn = AGUtil::createLabelButton("CONNECT", TEXT_FONT_NORMAL, "btn_icon_facebook.png", "btn_bg_01.png", 50,
		this, menu_selector(MainMenuScene::facebookConnectBtnListener), BUTTON_TEXT_ALIGN_CENTER);
	guestBtn = AGUtil::createLabelButton("G U E S T", TEXT_FONT_NORMAL, "", "btn_bg_01.png", 0,
		this, menu_selector(MainMenuScene::guestBtnListener), BUTTON_TEXT_ALIGN_CENTER);
	playBtn = AGUtil::createLabelButton("P L A Y", TEXT_FONT_NORMAL, "", "btn_bg_01.png", 0,
		this, menu_selector(MainMenuScene::guestBtnListener), BUTTON_TEXT_ALIGN_CENTER);

	CCMenu *menu = CCMenu::create(fbBtn, guestBtn, playBtn, NULL);
	menu->setPosition(ccp(winSize.width / 2, 250));
	menu->alignItemsVerticallyWithPadding(60);

	this->addChild(menu);

	this->facebookStateChange();

	setAccelerometerEnabled(true);

	this->schedule(schedule_selector(MainMenuScene::tick));

	return true;
}



void MainMenuScene::addJewel(int width, int height) {

	CCSprite* bg = CCSprite::create();

	CCSprite* jewel = CCSprite::createWithSpriteFrameName("DynamicCoinSmall.png");
	CCSprite* shiny = CCSprite::createWithSpriteFrameName("DynamicCoinSmall_light.png");

	bg->addChild(shiny);
	bg->addChild(jewel);

	bg->setPosition(ccp(width, height));
	this->addChild(bg);

	CCScaleTo * scaleUp = CCScaleTo::create(0.7, 1.10);
	CCScaleTo * scaleDown = CCScaleTo::create(0.7, 0.8);
	CCSequence * seq = CCSequence::create(scaleUp, scaleDown, NULL);
	CCRepeatForever * r = CCRepeatForever::create(seq);

	shiny->runAction(r);
}




void MainMenuScene::tick(float dt) {


	_pallaxManager.tick(dt);
	facebookStateChange();
}


void MainMenuScene::facebookStateChange()
{
	if(CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {

		fbBtn->setVisible(false);
		guestBtn->setVisible(false);
		playBtn->setVisible(true);
		playBtn->setPosition(fbBtn->getPosition());
	}else {
		fbBtn->setVisible(true);
		guestBtn->setVisible(true);
		playBtn->setVisible(false);
		playBtn->setPosition(ccp(winSize.width / 2, 580 - playBtn->getContentSize().height / 2));
	}
}
#include "../common/HiHighConnector.h"

void MainMenuScene::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	HiHighConnector* conn = HiHighConnector::sharedConnector();

	CCLog("mainmenuScene getMember callBack");

	if(conn->checkRespose(response) == false) {
		return;
	}

	if(client != NULL) {
		CCSprite* sprite = (CCSprite*)(response->getHttpRequest()->getUserData());
		sprite->removeFromParentAndCleanup(true);
	}


	string resStr;
	conn->convertString(response, resStr);

	CCLog("mainmenuScene getMember data |%s|", resStr.c_str());

	if(resStr.empty()) {
		CCLog("resStr.compare() == 0 ");
		conn->sendUserInfo(AGApplication::GetInstance()->getUserInfo(), NULL, httpresponse_selector(AGUtil::onVoidCompleted));
		return;
	}

	UserInfo* serverInfo = HiHighJsonConvecter::sharedJsonConverter()->convertUserInfo(resStr);

	UserInfo* localInfo = AGApplication::GetInstance()->getUserInfo();

	if(localInfo->getTotalGold() > serverInfo->getTotalGold() ) {
		localInfo->setId(serverInfo->getId());
		delete serverInfo;
		// 서버에 다시 보내기

		CCLog("localInfo->getTotalGold() > serverInfo->getTotalGold()");
		conn->sendUserInfo(localInfo, NULL, httpresponse_selector(AGUtil::onVoidCompleted));
	}
	else if(localInfo->getTotalGold() == serverInfo->getTotalGold() ) {
		if(localInfo->getGold() > serverInfo->getGold()) {
			serverInfo->setProfileUrl(localInfo->getProfileUrl());
			serverInfo->setName(localInfo->getName());
			delete localInfo;
			AGApplication::GetInstance()->setUserInfo(serverInfo);
		}
		else {
			localInfo->setId(serverInfo->getId());
			delete serverInfo;
			conn->sendUserInfo(localInfo, NULL, httpresponse_selector(AGUtil::onVoidCompleted));
		}
	}
	else {
		CCLog("localInfo->getTotalGold() <= serverInfo->getTotalGold()");
		serverInfo->setProfileUrl(localInfo->getProfileUrl());
		serverInfo->setName(localInfo->getName());
		delete localInfo;
		AGApplication::GetInstance()->setUserInfo(serverInfo);
	}

	HiHighDao* dao = AGApplication::GetInstance()->getHiHighDao();
	dao->updateUserInfo(AGApplication::GetInstance()->getUserInfo());

}

#include "../helper/AndroidHelper.h"

void MainMenuScene::guestBtnListener(CCObject* obj) {

	HiHighAudio::sharedAudio()->playEffect("button");

	/*for(int indexI = 0 ; indexI < 30000; ++indexI ) {
		UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
		StageScoreInfo& score = userInfo->getEndlessScoreInfo();

		int max = rand() % 500;
		int meter = rand() % 3000;
		score.setMaxCombo(max);
		score.setMiter(meter);


		HiHighConnector::sharedConnector()->registGuestMember(AGApplication::GetInstance()->getUserInfo(), this, httpresponse_selector(AGUtil::onVoidCompleted));
		CCLog("insert %d", indexI);
	}

	
	return;*/

	if(AGApplication::GetInstance()->checkFacebook() ){
		SceneManager::replaceScene("AbilitiesScene");
		return;
	}


	if(AGApplication::GetInstance()->getUserInfo()->getGuestId().compare("") == 0 && HHNetwork::GetInstance()->getNetworkStatus()) {
		HiHighConnector::sharedConnector()->registGuestMember(AGApplication::GetInstance()->getUserInfo(), this, httpresponse_selector(MainMenuScene::onRegistGuestCompleted));
	}
	else {

		SceneManager::replaceScene("AbilitiesScene");

		/*CCScene* main = AbilitiesScene::scene();
		CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
		CCDirector::sharedDirector()->replaceScene(transition);*/
	}
}

void MainMenuScene::facebookConnectBtnListener(CCObject* obj)
{
	UserInfo *user = AGApplication::GetInstance()->getUserInfo();

	if (!HHNetwork::GetInstance()->getNetworkStatus()) {
		string message = "Please retry later";
		HHAlert* alert = HHAlert::create("Network Error", message.c_str(), NULL, "OK");
		alert->show();
		return;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	FacebookInterface::login(Facebook::LOGIN_REQUEST,"login" );
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	FacebookInterfaceiOS::sharedFacebookiOS().login(Facebook::LOGIN_REQUEST,"login");
#endif



}
void MainMenuScene::facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message)
{
	CCLog("facebookErrorCallback index = %d", requestType);
	CCLog("Error message = %s",message.c_str());
	
	switch (requestType) {
	case Facebook::LOGIN_REQUEST :
		{
		
		}
		break;
	case Facebook::FRIENDS_REQUEST:
		{
		
		}
		break;
	case Facebook::LOGOUT_REQUEST:
		{
			
		}
		break;
	default:
		break;
	}
	
//	CCUserDefault::sharedUserDefault()->setBoolForKey(FACEBOOK_CONNECT, false);
	
	HHAlert* alert = HHAlert::create(NULL, message.c_str(), NULL, "OK");
	alert->show();
}
void MainMenuScene::facebookCallback(Facebook::REQUEST_TYPE requestType, string params)
{
	CCLog("facebookCallback index = %d", requestType);
	CCLog("paramss = %s",params.c_str());


	switch (requestType) {
	case Facebook::LOGIN_REQUEST :
		{
			Value userJson;
			Reader reader;
			bool parsingSuccess = reader.parse(params, userJson);

			if (!parsingSuccess) {
				CCLog("parser failed : \n %s", params.c_str());
			}

			bool isConnect = CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT);
			if(isConnect == false) {
				UserInfo *user = AGApplication::GetInstance()->getUserInfo();

				string facebookId = userJson.get("id",0).asString();
				string username = userJson.get("name",0).asString();
				string url = AGUtil::createFBProfileUrl(facebookId.c_str());

				if( user->getFacebookId().compare("") != 0 && user->getFacebookId().compare(facebookId) != 0) {
					AGApplication::GetInstance()->changedFacebookUser();
					user = AGApplication::GetInstance()->getUserInfo();
				}

				user->setFacebookId(facebookId);
				user->setName(username);
				user->setProfileUrl(url);

				// 로걸 저장

				HiHighDao* dao = AGApplication::GetInstance()->getHiHighDao();
				dao->updateUserInfo(user);

				CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
				CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
				layer->scheduleOnce(schedule_selector(MainMenuScene::authServerAfter), 0.5);

				CCUserDefault::sharedUserDefault()->setBoolForKey(FACEBOOK_CONNECT, true);


			}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			FacebookInterface::friends(Facebook::FRIENDS_REQUEST,"");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			FacebookInterfaceiOS::sharedFacebookiOS().friends(Facebook::FRIENDS_REQUEST,"friends");
#endif
		}
		break;
	case Facebook::FRIENDS_REQUEST:
		{
			HiHighConnector* connector = HiHighConnector::sharedConnector();
			string tempstring = connector->convertJsonForFbFriends(params);
			CCLog("convertJsonForFbFriends : %s", tempstring.c_str());
		}
		break;
	case Facebook::LOGOUT_REQUEST:
		{
			AGApplication::GetInstance()->getUserInfo()->setFacebookId("");
			AGApplication::GetInstance()->getHiHighDao()->updateUserInfo(AGApplication::GetInstance()->getUserInfo());

			/*CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
			CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
			layer->scheduleOnce(schedule_selector(MainMenuScene::authServerAfter), 0.5);*/

		}
		break;
	default:
		break;
	}



}

void MainMenuScene::abilityClickListener(CCObject* pSender, CCControlEvent event) {

	HiHighAudio::sharedAudio()->playEffect("button");

	CCScene* main = AbilitiesScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
	CCDirector::sharedDirector()->replaceScene(transition);


}

void MainMenuScene::settingClickListener(CCObject* pSender) {


	HiHighAudio::sharedAudio()->playEffect("popup");

	SettingPopup *popup = SettingPopup::createWithType(SETTING_POPUP_TYPE_MAIN_MENU);

	popup->show();


}

void MainMenuScene::authServerAfter(float dt) {

	if(HHNetwork::GetInstance()->getNetworkStatus() == false) {
		return;
	}

	HiHighConnector* conn = HiHighConnector::sharedConnector();
	if(AGApplication::GetInstance()->getUserInfo()->getGuestId().compare("") == 0) {
		CCLog("authServerAfter requestUserInfo");
		conn->requestUserInfo(AGApplication::GetInstance()->getUserInfo()->getFacebookId(), NULL, httpresponse_selector(MainMenuScene::onHttpRequestCompleted));
	}
	else {
		//콜백이 기존 연동로직 태우면 되지 않을까
		CCLog("authServerAfter modifyMember");
		conn->modifyMember(AGApplication::GetInstance()->getUserInfo(), NULL, httpresponse_selector(MainMenuScene::onModifyGuestCompleted));
	}
}


void MainMenuScene::keyBackClicked() {

	if(_backAlert != NULL && _backAlert->isShow()) {
		_backAlert->close(NULL);

	}
	_backAlert = HHAlert::create(NULL, "Will you quit now?", "OK", "Cancel");

	_backAlert->okayBtn->setTarget(this, menu_selector(MainMenuScene::backBtnOkListener));

	_backAlert->show();


}


void MainMenuScene::backBtnOkListener(CCObject* obj) {

	CCDirector::sharedDirector()->end();
}

void MainMenuScene::onRegistGuestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		SceneManager::replaceScene("AbilitiesScene");
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr.compare("") == 0) {
		SceneManager::replaceScene("AbilitiesScene");
		return;
	}



	UserInfo* serverUserInfo = HiHighJsonConvecter::sharedJsonConverter()->convertUserInfo(resStr);

	UserInfo* localUserInfo = AGApplication::GetInstance()->getUserInfo();

	CCLog("guest id : %s", serverUserInfo->getGuestId().c_str());
	char temp[100];
	sprintf(temp , "guest_%d",serverUserInfo->getId());
	localUserInfo->setName(temp);
	localUserInfo->setGuestId(serverUserInfo->getGuestId());
	localUserInfo->setId(serverUserInfo->getId());

	AGApplication::GetInstance()->getHiHighDao()->updateUserInfo(localUserInfo);

	delete serverUserInfo;

	SceneManager::replaceScene("AbilitiesScene");

}
void MainMenuScene::onModifyGuestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {

		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr.compare("") == 0) {
		return;
	}
	CCLog("modify %s", resStr.c_str());
	UserInfo* serverUserInfo = HiHighJsonConvecter::sharedJsonConverter()->convertUserInfo(resStr);

	UserInfo* localUserInfo = AGApplication::GetInstance()->getUserInfo();


	//과거 페이스북 계정 인증했던 사람
	if(serverUserInfo->getId() != localUserInfo->getId() ) {
		CCLog("maodify past %f", serverUserInfo->getId());
		serverUserInfo->setGuestId("");
		serverUserInfo->setProfileUrl(localUserInfo->getProfileUrl());
		serverUserInfo->setName(localUserInfo->getName());
		delete localUserInfo;
		AGApplication::GetInstance()->setUserInfo(serverUserInfo);
		AGApplication::GetInstance()->getHiHighDao()->updateUserInfo(serverUserInfo);

	}
	//새로 등록된사람
	else {
		CCLog("maodify new");
		localUserInfo->setId(serverUserInfo->getId());
		localUserInfo->setGuestId("");
		delete serverUserInfo;
		AGApplication::GetInstance()->setUserInfo(localUserInfo);
		AGApplication::GetInstance()->getHiHighDao()->updateUserInfo(localUserInfo);
	}


}
