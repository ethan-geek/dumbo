///////////////////////////////////////////////////////////
//  SettingPopup.cpp
//  Implementation of the Class SettingPopup
//  Created on:      19-3-2014 ø¿¿¸ 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "SettingPopup.h"
#include "../common/HiHighAudio.h"
#include "MainMenuScene.h"
#include "../common/HHButton.h"
#include "../common/HHAlert.h"
#include "../network/HHNetwork.h"
#include "../dao/HiHighDao.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../fb/FacebookInterface.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../fb/FacebookInterfaceiOS.h"
#endif

using namespace CocosDenshion;

SettingPopup::SettingPopup()
{

}



SettingPopup::~SettingPopup()
{

}

SettingPopup* SettingPopup::createWithType(SETTING_POPUP_TYPE type)
{
	SettingPopup *pRet = new SettingPopup();
	pRet->autorelease();
	//pRet->initPopup(CCSizeMake(500, 600));
	pRet->initPopup();
	pRet->popupType = type;
	pRet->initSettingPopup();
	return pRet;
}

void SettingPopup::initSettingPopup()
{
	CCLabelBMFont *soundLabel = CCLabelBMFont::create("S O U N D", TEXT_FONT_NORMAL);
	HHButton *soundBtn = HHButton::create(soundLabel, this, menu_selector(SettingPopup::menuSelected));
	soundBtn->setSize(400, 90);
	soundBtn->setIcon("icon_setting_sound.png", true);
	soundBtn->setTag(SETTING_POPUP_TAG_SOUND);
	soundBtn->setBorder();

	CCLabelBMFont *musicLabel = CCLabelBMFont::create("M U S I C", TEXT_FONT_NORMAL);
	HHButton *musicBtn = HHButton::create(musicLabel, this, menu_selector(SettingPopup::menuSelected));
	musicBtn->setSize(400, 90);
	musicBtn->setIcon("icon_setting_music.png", true);
	musicBtn->setTag(SETTING_POPUP_TAG_MUSIC);
	musicBtn->setBorder();

	CCLabelBMFont *vibeLabel = CCLabelBMFont::create("V I B R A T E", TEXT_FONT_NORMAL);
	HHButton *vibeBtn = HHButton::create(vibeLabel, this, menu_selector(SettingPopup::menuSelected));
	vibeBtn->setSize(400, 90);
	vibeBtn->setIcon("icon_setting_vibration.png", true);
	vibeBtn->setTag(SETTING_POPUP_TAG_VIBRATE);
	vibeBtn->setBorder();

	//    CCLabelBMFont *aboutLabel = CCLabelBMFont::create("A B O U T", TEXT_FONT_NORMAL);
	//    HHButton *aboutBtn = HHButton::create(aboutLabel, this, menu_selector(SettingPopup::menuSelected));
	//    aboutBtn->setSize(400, 90);
	//    aboutBtn->setIcon("icon_setting_about.png", false);
	//    aboutBtn->setTag(SETTING_POPUP_TAG_ABOUT);
	//aboutBtn->setBorder();

	CCLabelBMFont *facebookLabel = CCLabelBMFont::create("L O G I N", TEXT_FONT_NORMAL);
	HHButton *facebookBtn = HHButton::create(facebookLabel, this, menu_selector(SettingPopup::menuSelected));
	facebookBtn->setSize(400, 90);
	facebookBtn->setIcon("icon_setting_facebook.png", true);
	facebookBtn->setTag(SETTING_POPUP_TAG_FACEBOOK);
	facebookBtn->setBorder();

	CCLabelBMFont *backLabel = CCLabelBMFont::create("B A C K", TEXT_FONT_NORMAL);
	HHButton *backBtn = HHButton::create(backLabel, this, menu_selector(SettingPopup::menuCloseCallback));
	backBtn->setSize(400, 90);
	backBtn->setIcon("icon_setting_out.png", true);
	backBtn->setTag(SETTING_POPUP_TAG_FACEBOOK);
	backBtn->setBorder();


	menu = CCMenu::create(soundBtn, musicBtn, vibeBtn,facebookBtn, backBtn, NULL);
	menu->alignItemsVerticallyWithPadding(50);
	mainLayer->addChild(menu);


	if(CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {
		//CCLabelBMFont* label = (CCLabelBMFont*) facebookBtn->getChildByTag(10001);
		facebookBtn->setString("L O G O U T");
	}
	else {
		//CCLabelBMFont* label = (CCLabelBMFont*) facebookBtn->getChildByTag(10001);
		facebookBtn->setString("L O G I N");
	}

	//	if (this->popupType == SETTING_POPUP_TYPE_STAGE_MAP) {
	//		CCControlButton * mainMenuBtn = AGUtil::createTextWithIconButton("MENU", 0.9, "btn_bg_02",
	//				"icon_setting_out", this, cccontrol_selector(SettingPopup::menuSelected), TEXT_FONT_SMALL);
	//		mainMenuBtn->setPosition(ccp(mainLayer->getContentSize().width/2, mainLayer->getContentSize().height/2 - SETTING_BTN_INTERVAL_LENGTH * 3 + offsetY));
	//		mainMenuBtn->setTouchPriority(-200);
	//		mainMenuBtn->setTag(SETTING_POPUP_TAG_MAINMENU);
	//		mainLayer->addChild(mainMenuBtn);
	//	}


	loadConfig();
	closeMenu->setVisible(false);

	this->schedule(schedule_selector(SettingPopup::tick));

}

void SettingPopup::loadConfig()
{
	bool isSoundOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF, false);
	bool isMusicOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_MUSIC_OFF, false);
	bool isVibeOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_VIBE_OFF, false);

	changeVisibleSettingXIcon(SETTING_POPUP_TAG_SOUND,isSoundOff);
	changeVisibleSettingXIcon(SETTING_POPUP_TAG_MUSIC,isMusicOff);
	changeVisibleSettingXIcon(SETTING_POPUP_TAG_VIBRATE,isVibeOff);

}

void SettingPopup::changeVisibleSettingXIcon(int tag, bool b) {

	HHButton * btn = (HHButton *)menu->getChildByTag(tag);
	CCSprite * xIcon = (CCSprite *)btn->getChildByTag(SETTING_BTN_IGNORE_TAG);
	CCSprite *icon = (CCSprite*)btn->getChildByTag(80);


	if (xIcon != NULL) {
		if (b == false) {
			icon->setOpacity(255);
			xIcon->setVisible(false);
		}
		else {
			icon->setOpacity(255 * 0.6);
			xIcon->setVisible(true);
		}
	}

}


void SettingPopup::menuSelected(CCObject* obj)
{
	CCNode *node = (CCNode*)obj;
	switch (node->getTag()) {
	case SETTING_POPUP_TAG_SOUND:
	{
		onOffSound();
	}
	break;
	case SETTING_POPUP_TAG_MUSIC:
	{
		onOffMusic();
	}
	break;
	case SETTING_POPUP_TAG_VIBRATE:
	{
		onOffVibe();
	}
	break;
	case SETTING_POPUP_TAG_ABOUT:
	{
		//		addAboutView();

	}
	break;
	case SETTING_POPUP_TAG_FACEBOOK:
	{

		if (!HHNetwork::GetInstance()->getNetworkStatus()) {
			string message = "Please retry later";
			HHAlert* alert = HHAlert::create("Network Error", message.c_str(), NULL, "OK");
			alert->show();
			return;
		}

		if(CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			FacebookInterface::logout(Facebook::LOGOUT_REQUEST,"logout");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			FacebookInterfaceiOS::sharedFacebookiOS().logOut(Facebook::LOGOUT_REQUEST, "logout");
#endif
		}
		else {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			//	bool fff = FacebookInterface::IsLoggedIn();
			FacebookInterface::login(Facebook::LOGIN_REQUEST,"login" );
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			FacebookInterfaceiOS::sharedFacebookiOS().login(Facebook::LOGIN_REQUEST,"login");
#endif
		}

	}
	break;
	case SETTING_POPUP_TAG_MAINMENU:
	{
		goPreviousScene();
	}
	break;
	default:
		break;
	}
}

void SettingPopup::facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message)
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

	HHAlert* alert = HHAlert::create(NULL, message.c_str(), NULL, "OK");
	alert->show();
}

void SettingPopup::facebookCallback(Facebook::REQUEST_TYPE cbIndex, string params)
{

	switch (cbIndex) {
	case Facebook::LOGOUT_REQUEST:
	{
		CCLog("SettingPopup Logout");
		CCUserDefault::sharedUserDefault()->setBoolForKey(FACEBOOK_CONNECT, false);
		AGApplication::GetInstance()->getUserInfo()->setFacebookId("");
		AGApplication::GetInstance()->getHiHighDao()->updateUserInfo(AGApplication::GetInstance()->getUserInfo());
	}
	break;
	case Facebook::SETTING_LOGIN_REQUEST:
	{
		CCLog("SettingPopup Login");
		CCUserDefault::sharedUserDefault()->setBoolForKey(FACEBOOK_CONNECT, true);
	}
	break;
	default:
		break;
	}

	//	isLogout = true;
	//

}

void SettingPopup::menuCloseCallback(cocos2d::CCObject *pSender)
{
	CCLog("menuCloseCallback");
	BasicPopup::menuCloseCallback(pSender);

	//	if (isLogout) {
	//		MainMenuScene::facebookCallback(2, "LOGOUT");
	//	}

}
void setVisibleButton(CCNode * obj, int tag, bool b) {
	CCControlButton * btn =  (CCControlButton *)obj->getChildByTag(tag);
	btn->setVisible(b);
}

void SettingPopup::setVisibleButtons(bool b) {

	setVisibleButton(mainLayer, 1, b);
	setVisibleButton(mainLayer, 2, b);
	setVisibleButton(mainLayer, 3, b);
	setVisibleButton(mainLayer, 4, b);
	setVisibleButton(mainLayer, 5, b);

}

void SettingPopup::addAboutView()
{
	setVisibleButtons(false);

	aboutLayer = CCLayer::create();
	aboutLayer->setContentSize(mainLayer->getContentSize());

	UserInfo* info = AGApplication::GetInstance()->getUserInfo();
	info->setGold(info->getGold() + 50);
	info->setTotalGold(info->getTotalGold() + 50);

	CCLabelBMFont *copyright = CCLabelBMFont::create("Copyright 2014.", TEXT_FONT_SMALL);
	copyright->setPosition(ccp(aboutLayer->getContentSize().width/2, aboutLayer->getContentSize().height*(0.6)));

	CCLabelBMFont *atGame = CCLabelBMFont::create("atGame", TEXT_FONT_SMALL);
	atGame->setPosition(ccp(aboutLayer->getContentSize().width/2, aboutLayer->getContentSize().height*(0.5)));

	CCLabelBMFont *allRightReserved = CCLabelBMFont::create("all right reserved.", TEXT_FONT_SMALL);
	allRightReserved->setPosition(ccp(aboutLayer->getContentSize().width/2, aboutLayer->getContentSize().height*(0.4)));


	aboutLayer->addChild(copyright);
	aboutLayer->addChild(atGame);
	aboutLayer->addChild(allRightReserved);



	mainLayer->addChild(aboutLayer);
}

#include "../common/HiHighConnector.h"


void SettingPopup::testMenuSelectedListener(CCObject* obj) {
	CCNode* node = (CCNode*)obj;

	HiHighConnector* conn = HiHighConnector::sharedConnector();

	switch(node->getTag()) {
	case 1:
	{
		/*string faceList = "[{\"fbId\" : \"localUser\"}, {   \"friendList\": [     {       \"name\": \"Yongjoo Ji\",       \"id\": \"676078682\"     },     {       \"name\": \"YeongDeok Kim\",       \"id\": \"100000177989020\"     },     {       \"name\": \"Chiee Lee\",       \"id\": \"100001501964223\"     },     {       \"name\": \"Hui Yong Lee\",       \"id\": \"100001541777465\"     },     {       \"name\": \"Sungsoo Kang\",       \"id\": \"100002048567006\"     },     {       \"name\": \"Jackie Kim\",       \"id\": \"100002075628312\"     },   ] }]";
			string faceListOri = "{   \"data\": [     {       \"name\": \"Yongjoo Ji\",       \"id\": \"676078682\"     },     {       \"name\": \"YeongDeok Kim\",       \"id\": \"100000177989020\"     },     {       \"name\": \"Chiee Lee\",       \"id\": \"100001501964223\"     },     {       \"name\": \"Hui Yong Lee\",       \"id\": \"100001541777465\"     },     {       \"name\": \"Sungsoo Kang\",       \"id\": \"100002048567006\"     },     {       \"name\": \"Jackie Kim\",       \"id\": \"100002075628312\"     },   ] }";*/
		//conn->sendFacebookFriendList(faceList, this, httpresponse_selector(SettingPopup::onHttpRequestCompleted));
	}


	break;
	case 2:
	{
		UserUpgradeInfo upgradeInfo;
		upgradeInfo.setUpgradeCount(6);
		ItemInfo itemInfo;
		itemInfo.setDescription("That Which Falls Has Parachute");
		itemInfo.setId(3);
		itemInfo.setName("PARACHUTE");
		itemInfo.setPrice(5000);
		upgradeInfo.setItemInfo(itemInfo);

		conn->sendUpgradeInfo(&upgradeInfo, this, httpresponse_selector(SettingPopup::onHttpRequestCompleted));
	}
	break;
	case 3:
	{
		StageScoreInfo scoreInfo;
		scoreInfo.setStage(-1);
		scoreInfo.setMaxScore(99999);
		scoreInfo.setMaxCombo(200);

		conn->sendScore(&scoreInfo, this, httpresponse_selector(SettingPopup::onHttpRequestCompleted));
	}
	break;
	case 5:
	{

		conn->requestUserInfo(AGApplication::GetInstance()->getUserInfo()->getFacebookId(), this, httpresponse_selector(SettingPopup::onHttpRequestCompleted));
	}
	break;
	case 6:
		conn->sendUserInfo(AGApplication::GetInstance()->getUserInfo(), this, httpresponse_selector(MainMenuScene::onHttpRequestCompleted));
		break;
	case 7 :
	{
		string temp = "{   \"data\": [     {       \"name\": \"Yongjoo Ji\",       \"id\": \"676078682\"     },     {       \"name\": \"YeongDeok Kim\",       \"id\": \"100000177989020\"     },     {       \"name\": \"Jang Jaewan\",       \"id\": \"100001069725498\"     }, {       \"name\": \"Chiee Lee\",       \"id\": \"100001501964223\"     },     {       \"name\": \"Hui Yong Lee\",       \"id\": \"100001541777465\"     },     {       \"name\": \"Sungsoo Kang\",       \"id\": \"100002048567006\"     },     {       \"name\": \"Jackie Kim\",       \"id\": \"100002075628312\"     },     {       \"name\": \"Yong Hee Lee\",       \"id\": \"100003050235639\"     }   ],   \"paging\": {     \"next\": \"https://graph.facebook.com/v2.0/100001497407847/friends?limit=5000&offset=5000&__after_id=enc_Aey_e73DHDNxoP8DNGs8xKc20KZfwOYeBMUdEOKPTBpMnUKQHCBBm8zmMWxYlDErbXKBfesn4Q-wyS3wQiS45vSv\"   } }";
		string next = conn->convertJsonForFbFriends(temp);
		next = conn->convertJsonForFbFriends(temp);
		next = conn->convertJsonForFbFriends(temp);
		next = conn->convertJsonForFbFriends(temp);
		next = conn->convertJsonForFbFriends(temp);
		next = conn->convertJsonForFbFriends(temp);
	}

	break;
	default:
		AGUtil::alert("not defined serverTag");
		break;

	}
}

void SettingPopup::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	CCMessageBox(resStr.c_str(), "response");

	CCLog("logo Scene |%s|", resStr.c_str());

	if(resStr.empty()) {
		CCLog("logo Scene resStr.compare() == 0");

		return;
	}

	UserInfo* info = HiHighJsonConvecter::sharedJsonConverter()->convertUserInfo(resStr);

}

void SettingPopup::back(CCObject*)
{
	aboutLayer->removeAllChildren();
	aboutLayer = NULL;

	setVisibleButtons(true);

}

void SettingPopup::onOffSound()
{
	HiHighAudio *audio = HiHighAudio::sharedAudio();
	bool isSoundOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF, false);

	if(isSoundOff) {
		//turn on
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_SOUND_OFF , false);
		audio->unmuteSound();
	}else {
		//turn off
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_SOUND_OFF , true);
		audio->muteSound();
	}

	isSoundOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF, false);
	changeVisibleSettingXIcon(1, isSoundOff);
	CCUserDefault::sharedUserDefault()->flush();
}

void SettingPopup::onOffMusic()
{
	HiHighAudio *audio = HiHighAudio::sharedAudio();
	bool isMusicOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_MUSIC_OFF, false);

	if(isMusicOff) {
		//turn on
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_MUSIC_OFF , false);
		audio->unmuteMusic();
	}else {
		//turn off
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_MUSIC_OFF , true);
		audio->muteMusic();
	}

	isMusicOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_MUSIC_OFF, false);
	changeVisibleSettingXIcon(2, isMusicOff);
	CCUserDefault::sharedUserDefault()->flush();
}

void SettingPopup::onOffVibe()
{
	HiHighAudio *audio = HiHighAudio::sharedAudio();
	bool isVibeOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_VIBE_OFF, false);
	if(isVibeOff) {
		//turn on
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_VIBE_OFF , false);
		audio->vibrate();
	}else {
		//turn off
		CCUserDefault::sharedUserDefault()->setBoolForKey(IS_VIBE_OFF , true);
	}

	isVibeOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_VIBE_OFF, false);
	changeVisibleSettingXIcon(3, isVibeOff);
	CCUserDefault::sharedUserDefault()->flush();
}


void SettingPopup::goPreviousScene()
{
	menuCloseCallback(NULL);
	CCScene* main = MainMenuScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
	CCDirector::sharedDirector()->replaceScene(transition);
}

void SettingPopup::tick(float dt) {

	string temp = "";

	if(CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {
		temp = "L O G O U T";
	}
	else {
		temp = "L O G I N";
	}

	//	CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
	//	CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
	//  CCNode* node = layer->getChildByTag(BASICPOPUP)->getChildByTag(MAINLAYER)->getChildByTag(SETTING_POPUP_TAG_FACEBOOK);
	HHButton *facebookBtn = (HHButton*)menu->getChildByTag(SETTING_POPUP_TAG_FACEBOOK);
	if(facebookBtn != NULL) {
		//CCLabelBMFont* label = (CCLabelBMFont*) node->getChildByTag(10001);
		facebookBtn->setString(temp.c_str());

	}


}
