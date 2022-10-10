///////////////////////////////////////////////////////////
//  StageMapScene.cpp
//  Implementation of the Class StageMapScene
//  Created on:      19-3-2014 ���� 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "StageMapScene.h"
#include "AbilitiesScene.h"
#include "SettingPopup.h"
#include "SlidingMenu.h"
#include "StageInfoPopup.h"
#include "../common/HeartChecker.h"
#include "HeartReqResPopup.h"
#include "../model/UserInfo.h"

#define STAGE_COUNT_PER_EPISODE 30
#define EPISODE_COUNT 4

StageMapScene::StageMapScene(){

}



StageMapScene::~StageMapScene(){
    
}

CCScene* StageMapScene::scene() {
    CCScene *scene = CCScene::create();
    StageMapScene *layer = StageMapScene::create();
    scene->addChild(layer);
    return scene;
}

bool StageMapScene::init() {
    
    if ( !CCLayer::init())
    {
        return false;
    }
    _winSize = CCDirector::sharedDirector()->getWinSize();
    
    makeStageMap();
    makeTopBar();

    CCControlButton *mailBox = AGUtil::createIconButton("mail", this, cccontrol_selector(StageMapScene::mailBoxListener), 1);
    mailBox->setTouchPriority(-120);
  
    mailBox->setPosition(ccp(70, _winSize.height - 180));
    this->addChild(mailBox);
    
    return true;
}

void StageMapScene::abilityClickListener(CCObject* pSender, CCControlEvent event) {
    CCScene* main = AbilitiesScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
    CCDirector::sharedDirector()->replaceScene(transition);
}

void StageMapScene::settingClickListener(CCObject* pSender, CCControlEvent event) {
    SettingPopup *popup = SettingPopup::createWithType(SETTING_POPUP_TYPE_STAGE_MAP);
    popup->show();
}

void StageMapScene::makeStageMap()
{
    
    CCArray* array = CCArray::createWithCapacity(STAGE_COUNT_PER_EPISODE * EPISODE_COUNT);
    for(int i =0; i < STAGE_COUNT_PER_EPISODE * EPISODE_COUNT; i++){
        CCSprite *spr = CCSprite::createWithSpriteFrameName("btn_stage.png");
        int temp = i+1;
        stringstream ss;
        ss << temp;
        string levelStr = ss.str();

        CCLabelTTF *stageLabel = CCLabelTTF::create(levelStr.c_str(), "Marker Felt", 40);
        CCMenuItemSprite *menuItem = new CCMenuItemSprite();
        menuItem->autorelease();
        menuItem->initWithNormalSprite(spr, spr, spr, this, menu_selector(StageMapScene::stageSelectListener));
        menuItem->setTag(i);
        menuItem->addChild(stageLabel);
        stageLabel->setPosition(ccp(menuItem->getContentSize().width/2, menuItem->getContentSize().height/2));
        array->addObject(menuItem);
    }

    SlidingMenuGrid * grid = SlidingMenuGrid::menuWithArray(array, 5, 6, CCPoint(72,320), CCPoint(120,130));
    grid->setContentSize(CCSizeMake(_winSize.width, _winSize.height - 120));

    grid->SetSwipeDeadZone(30.0f);
    grid->setTag(0);
    

	CC_SAFE_RELEASE(array);
	
    
    this->addChild(grid);
    
}

void StageMapScene::makeTopBar()
{
    CCLayerColor *topbar = CCLayerColor::create(ccc4(10, 100, 200, 255), _winSize.width, 120);
    topbar->setAnchorPoint(CCPointZero);
    topbar->setPosition(ccp(0, _winSize.height-120));
    this->addChild(topbar);
    
    settingBtn = AGUtil::createIconButton("btn_main_setting", this, cccontrol_selector(StageMapScene::settingClickListener));
    settingBtn->setPosition(ccp(60 , topbar->getContentSize().height / 2));
    settingBtn->setTouchPriority(-120);
    topbar->addChild(settingBtn);
    
    abilityBtn = AGUtil::createIconButton("btn_main_abillity", this, cccontrol_selector(StageMapScene::abilityClickListener));
    abilityBtn->setPosition(ccp(topbar->getContentSize().width - 60, topbar->getContentSize().height / 2));
    abilityBtn->setTouchPriority(-120);
    topbar->addChild(abilityBtn);
    
    CCSprite *heartTimerBG = CCSprite::createWithSpriteFrameName("btn_bg_01_default.png");
    heartTimerBG->setPosition(ccp(topbar->getContentSize().width/2, topbar->getContentSize().height/2));
    topbar->addChild(heartTimerBG);
    
    CCSprite * heart = CCSprite::createWithSpriteFrameName("heart.png");
    heart->setPosition(ccp(heartTimerBG->getContentSize().width - 70, heartTimerBG->getContentSize().height/2));
    heartTimerBG->addChild(heart);
    
    CCLabelTTF * count = CCLabelTTF::create("", "Marker Felt", 42);
    heart->addChild(count);
    count->setPosition(ccp(heart->getContentSize().width / 2, heart->getContentSize().height / 2));
    
    CCLabelTTF * time = CCLabelTTF::create("", "Marker Felt", 60);
    time->setFontFillColor(ccWHITE);
    time->enableStroke(ccBLACK, 2);

    time->setPosition(ccp(heartTimerBG->getContentSize().width / 2 - 30, heartTimerBG->getContentSize().height / 2));
    heartTimerBG->addChild(time);

    
    HeartChecker * instance = HeartChecker::sharedHeartChecker();
    addChild((CCNode*)instance);
    instance->setInterval(300, count, time);
    instance->start();
    
	
}

void StageMapScene::stageSelectListener(CCObject* obj)
{
    CCLog("###STAGE : %d", ((CCNode*)obj)->getTag()+1);


	UserInfo* info = AGApplication::GetInstance()->getUserInfo();

	if(info->getHeartInfo()->getHeartCount() <= 0 ) {

		AGUtil::alert("not enough heart");

		return;
	}


	if(info->getCurrentStage() < ((CCNode*)obj)->getTag()+1) {

		char temp[20];
		sprintf(temp, "%d clear please", info->getCurrentStage());

		AGUtil::alert(temp);

		
		return;
	}
	

	AGApplication::GetInstance()->getGameData()->setCurrentStage(((CCNode*)obj)->getTag()+1);

    StageInfoPopup *stagePopup = StageInfoPopup::create();
    stagePopup->show();

	

}

void StageMapScene::mailBoxListener(CCObject *obj, CCControlEvent event)
{

	HeartInfo* info = AGApplication::GetInstance()->getUserInfo()->getHeartInfo();

	info->increaseHeart();

    HeartReqResPopup *popup = HeartReqResPopup::createWithSize(CCSizeMake(400, 400));
    popup->show();
}
