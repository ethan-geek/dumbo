///////////////////////////////////////////////////////////
//  HeartReqResPopup.cpp
//  Implementation of the Class HeartReqResPopup
//  Created on:      19-3-2014 ¿ÀÀü 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "HeartReqResPopup.h"


HeartReqResPopup::HeartReqResPopup()
{

}

HeartReqResPopup::~HeartReqResPopup()
{

}

HeartReqResPopup* HeartReqResPopup::createWithSize(CCSize size)
{
    HeartReqResPopup *pRet = new HeartReqResPopup();
    pRet->autorelease();
    pRet->initPopup(size);
    pRet->initHeartPopup();
    
    return pRet;
}

void HeartReqResPopup::initHeartPopup()
{
    CCSprite *bg = CCSprite::createWithSpriteFrameName("popup_bg_01.png");
    bg->setPosition(ccp(mainLayer->getContentSize().width/2, mainLayer->getContentSize().height/2));
    mainLayer->addChild(bg);
    
    CCLabelTTF* sendLabel = CCLabelTTF::create("Send", "Marker Felt", 40);
    sendLabel->setColor(ccc3(255, 1, 1));
    CCMenuItemLabel* sendBtn = CCMenuItemLabel::create(sendLabel, this, menu_selector(HeartReqResPopup::sendHeart));
    sendBtn->setTag(1);
    
    CCLabelTTF* askLabel = CCLabelTTF::create("Ask", "Marker Felt", 40);
    askLabel->setColor(ccc3(255, 1, 1));
    CCMenuItemLabel* askBtn = CCMenuItemLabel::create(askLabel, this, menu_selector(HeartReqResPopup::askHeart));
    askBtn->setTag(2);
    
    
    CCMenu *menu = CCMenu::create(sendBtn, askBtn, NULL);
    menu->alignItemsVerticallyWithPadding(40);
    menu->setPosition(ccp(mainLayer->getContentSize().width/2, mainLayer->getContentSize().height/2));
    
    mainLayer->addChild(menu);
}

void HeartReqResPopup::sendHeart(CCObject* obj)
{
    CCLog("send");
}

void HeartReqResPopup::askHeart(CCObject* obj)
{
    CCLog("aske");
}