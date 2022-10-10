///////////////////////////////////////////////////////////
//  PausePopup.cpp
//  Implementation of the Class PausePopup
//  Created on:      19-3-2014 ���� 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////


#include "PausePopup.h"
#include "StageMapScene.h"
#include "../model/UserInfo.h"
#include "../view/GameLoadingScene.h"
#include "../view/MainMenuScene.h"
#include "../common/HHButton.h"

PausePopup::PausePopup(){

}



PausePopup::~PausePopup(){

}

PausePopup* PausePopup::createWithSize(CCSize size)
{
    PausePopup *pRet = new PausePopup();
    pRet->autorelease();
    pRet->initPopup();
    pRet->initPausePopup();
    
    return pRet;
}

void PausePopup::initPausePopup()
{
    closeMenu->setVisible(false);
    
    CCLabelBMFont *continueLabel = CCLabelBMFont::create("C O N T I N U E", TEXT_FONT_NORMAL);
    HHButton *continueBtn = HHButton::create(continueLabel, this, menu_selector(PausePopup::menuSelected));
    continueBtn->setSize(400, 90);
    continueBtn->setTag(1);
    continueBtn->setBorder();
    
    CCLabelBMFont *retryLabel = CCLabelBMFont::create("R E T R Y", TEXT_FONT_NORMAL);
    HHButton *retryBtn = HHButton::create(retryLabel, this, menu_selector(PausePopup::menuSelected));
    retryBtn->setSize(400, 90);
    retryBtn->setTag(2);
    retryBtn->setBorder();
    
    CCLabelBMFont *soundLabel = CCLabelBMFont::create("S O U N D", TEXT_FONT_NORMAL);
    HHButton *soundBtn = HHButton::create(soundLabel, this, menu_selector(PausePopup::menuSelected));
    soundBtn->setSize(400, 90);
    soundBtn->setIcon("icon_setting_sound.png", true);
    soundBtn->setTag(3);
    soundBtn->setBorder();
    soundBtn->setColor(ccc3(200, 200, 200));
    
    CCLabelBMFont *musicLabel = CCLabelBMFont::create("M U S I C", TEXT_FONT_NORMAL);
    HHButton *musicBtn = HHButton::create(musicLabel, this, menu_selector(PausePopup::menuSelected));
    musicBtn->setSize(400, 90);
    musicBtn->setIcon("icon_setting_music.png", true);
    musicBtn->setTag(4);
    musicBtn->setBorder();
    musicBtn->setColor(ccc3(200, 200, 200));
    
    CCLabelBMFont *vibeLabel = CCLabelBMFont::create("V I B R A T E", TEXT_FONT_NORMAL);
    HHButton *vibeBtn = HHButton::create(vibeLabel, this, menu_selector(PausePopup::menuSelected));
    vibeBtn->setSize(400, 90);
    vibeBtn->setIcon("icon_setting_vibration.png", true);
    vibeBtn->setTag(5);
    vibeBtn->setBorder();
    vibeBtn->setColor(ccc3(200, 200, 200));

    CCLabelBMFont *backLabel = CCLabelBMFont::create("B A C K", TEXT_FONT_NORMAL);
    HHButton *backBtn = HHButton::create(backLabel, this, menu_selector(PausePopup::menuSelected));
    backBtn->setSize(400, 90);
    backBtn->setIcon("icon_setting_out.png", true);
    backBtn->setTag(6);
    backBtn->setBorder();
    backBtn->setColor(ccc3(200, 200, 200));

    
    settingMenu = CCMenu::create(continueBtn, retryBtn, soundBtn, musicBtn, vibeBtn, backBtn, NULL);
    settingMenu->alignItemsVerticallyWithPadding(50);
    mainLayer->addChild(settingMenu);
    
    loadConfig();
}

void PausePopup::loadConfig()
{
	bool isSoundOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_SOUND_OFF, false);
	bool isMusicOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_MUSIC_OFF, false);
	bool isVibeOff = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_VIBE_OFF, false);
    
    changeVisibleSettingXIcon(3,isSoundOff);
    changeVisibleSettingXIcon(4,isMusicOff);
    changeVisibleSettingXIcon(5,isVibeOff);
    
}

void PausePopup::changeVisibleSettingXIcon(int tag, bool b) {
    
    HHButton * btn = (HHButton *)settingMenu->getChildByTag(tag);
    CCSprite * xIcon = (CCSprite *)btn->getChildByTag(SETTING_BTN_IGNORE_TAG);
    CCSprite *icon = (CCSprite*)btn->getChildByTag(80);
    
    if(xIcon != NULL) {
        if(b == false) {
            icon->setOpacity(255);
            xIcon->setVisible(false);
        }else {
			icon->setOpacity(255 * 0.6);
            xIcon->setVisible(true);
        }
    }

}

void PausePopup::menuSelected(CCObject* obj)
{
    CCNode *node = (CCNode*)obj;
    switch (node->getTag()) {
        case 1:
        {
            continueGame();
        }
            break;
        case 2:
        {
            retryGame();
        }
            break;
        case 3:
        {
            onOffSound();
        }
            break;
        case 4:
        {
            onOffMusic();
        }
            break;
        case 5:
        {
            onOffVibe();
        }
            break;
        case 6:
        {
            goPreviousScene();
        }
            break;
        default:
            break;
    }
}



void PausePopup::onOffSound()
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
    changeVisibleSettingXIcon(3, isSoundOff);
    CCUserDefault::sharedUserDefault()->flush();
}

void PausePopup::onOffMusic()
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
    changeVisibleSettingXIcon(4, isMusicOff);
    CCUserDefault::sharedUserDefault()->flush();
}

void PausePopup::onOffVibe()
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
    changeVisibleSettingXIcon(5, isVibeOff);
    CCUserDefault::sharedUserDefault()->flush();
}


void PausePopup::continueGame()
{
    menuCloseCallback(NULL);
    AGUtil::gameResume();
}

void PausePopup::retryGame()
{
	UserInfo* info = AGApplication::GetInstance()->getUserInfo();
	HeartInfo* hearInfo = info->getHeartInfo();

	AGUtil::gameResume();
	menuCloseCallback(NULL);


	SceneManager::replaceScene("GameLoadingScene");

	 /*CCScene *loading = GameLoadingScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, loading);
    CCDirector::sharedDirector()->replaceScene(transition);*/
}



void PausePopup::show()
{

    BasicPopup::show();

	

    AGUtil::gamePause();
}

void PausePopup::pauseCallback()
{
    AGUtil::gamePause();
}


void PausePopup::goPreviousScene()
{
    AGUtil::gameResume();
    menuCloseCallback(NULL);

	CCScene *prevScene = NULL;
	if (AGApplication::GetInstance()->getGameData()->getCurrentStage() <= 0) {
		SceneManager::replaceScene("MainMenuScene");
	}
	else {
		SceneManager::replaceScene("StageMapScene");
	}
	
}


