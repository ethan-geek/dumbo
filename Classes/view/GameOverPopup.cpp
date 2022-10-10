///////////////////////////////////////////////////////////
//  GameOverPopup.cpp
//  Implementation of the Class GameOverPopup
//  Created on:      19-3-2014 ���� 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "GameOverPopup.h"

#include "../game/GamePlayScene.h"
#include "../model/UserInfo.h"
#include "../model/HeartInfo.h"
#include "../view/GameLoadingScene.h"
#include "../view/StageMapScene.h"


GameOverPopup::GameOverPopup() :_saveMeCount(0){

}



GameOverPopup::~GameOverPopup(){

}

GameOverPopup* GameOverPopup::create()
{
    GameOverPopup *pRet = new GameOverPopup();
    pRet->autorelease();
    pRet->initPopup(CCSizeMake(500, 600));
    pRet->initGameOverPopup();
    
    return pRet;
}

void GameOverPopup::setCallback(GamePlayScene* obj, void (GamePlayScene::*callBack)(int), int count) {
	_callObject = obj;
	_callBack = callBack;
	_saveMeCount = count;
}

void GameOverPopup::initGameOverPopup()
{
 
    closeMenu->setVisible(false);
    
    
    CCSprite *bg = CCSprite::createWithSpriteFrameName("popup_bg_01.png");
    bg->setPosition(ccp(mainLayer->getContentSize().width/2, mainLayer->getContentSize().height/2));
    mainLayer->addChild(bg);
    
    
    CCControlButton * saveMeBtn = AGUtil::createTextWithIconButton("SAVE ME", 0.9, "btn_bg_02", NULL, this, cccontrol_selector(GameOverPopup::saveMeBtnListener), TEXT_FONT_NORMAL, true);
    saveMeBtn->setPosition(ccp(mainLayer->getContentSize().width/2, 426));
  	saveMeBtn->setTouchPriority(-200);
    mainLayer->addChild(saveMeBtn);
    
    
    CCControlButton * retryBtn = AGUtil::createTextWithIconButton("Retry", 0.9, "btn_bg_02", NULL, this, cccontrol_selector(GameOverPopup::retryBtnListener), TEXT_FONT_NORMAL);
    retryBtn->setPosition(ccp(mainLayer->getContentSize().width/2, 250));
  	retryBtn->setTouchPriority(-200);
    mainLayer->addChild(retryBtn);
    
    
    
    CCControlButton * backBtn = AGUtil::createTextWithIconButton("Back", 0.9, "btn_bg_02", NULL, this, cccontrol_selector(GameOverPopup::backBtnListener), TEXT_FONT_NORMAL);
    backBtn->setPosition(ccp(mainLayer->getContentSize().width/2, 150));
  	backBtn->setTouchPriority(-200);
    mainLayer->addChild(backBtn);
}


void GameOverPopup::saveMeBtnListener(CCObject* obj,CCControlEvent event)
{
    
	char temp[1024];
	sprintf(temp, "decrease %d G ?", RESUREECTION_PAY * _saveMeCount);

	alert = HHAlert::create("Resurrection", temp, "Buy", "Cancel");
    alert->show();
    //alert->okayBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameOverPopup::buySaveMeItem), CCControlEventTouchUpInside);

}

void GameOverPopup::buySaveMeItem(cocos2d::CCObject *obj, CCControlEvent event)
{
    

	UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();

	if(userInfo->getGold() < RESUREECTION_PAY * _saveMeCount) {
		AGUtil::alert("not enough gold");
		return;
	}
	
	userInfo->setGold(userInfo->getGold() - RESUREECTION_PAY * _saveMeCount);

	
	HeartInfo* hearInfo = userInfo->getHeartInfo();
	hearInfo->increaseHeart();

    alert->close(obj);
    (_callObject->*_callBack)(5000 * _saveMeCount);
	AGUtil::gameResume();
	menuCloseCallback(obj);
    

}

void GameOverPopup::retryBtnListener(CCObject* obj,CCControlEvent event)
{
    
	HeartInfo* hearInfo = AGApplication::GetInstance()->getUserInfo()->getHeartInfo();

	AGUtil::gameResume();
	menuCloseCallback(obj);

	 CCScene *loading = GameLoadingScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, loading);
    CCDirector::sharedDirector()->replaceScene(transition);
    
}

void GameOverPopup::backBtnListener(CCObject* obj,CCControlEvent event)
{
   

	AGUtil::gameResume();
	menuCloseCallback(obj);

   CCScene *map = StageMapScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, map);
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameOverPopup::show()
{
    
    CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
    
    layer->addChild(this, 300);
    this->setAnchorPoint(ccp(0.5f, 0.5f));
    mainLayer->setScale(0.1);
    CCScaleTo *scale = CCScaleTo::create(0.1, 1);
    CCEaseIn *easeIn = CCEaseIn::create(scale, 1.f);
    CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(GameOverPopup::pauseCallback));
    
    CCSequence *seq = CCSequence::create(easeIn, callFunc, NULL);
    
    mainLayer->runAction(seq);
    
}

void GameOverPopup::pauseCallback()
{
    AGUtil::gamePause();
}


