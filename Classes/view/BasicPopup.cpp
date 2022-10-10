///////////////////////////////////////////////////////////
//  BasicPopup.cpp
//  Implementation of the Class BasicPopup
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////


#include "BasicPopup.h"


BasicPopup::BasicPopup()
{
}



BasicPopup::~BasicPopup()
{
    
}

void BasicPopup::initPopup()
{
    this->setTag(BASICPOPUP);
    this->init();
    
    mWinSize = CCDirector::sharedDirector()->getWinSize();
    
    mainLayer = CCLayerColor::create(ccc4(0, 0, 0, 255 * 0.9), mWinSize.width, mWinSize.height);
    mainLayer->setTag(MAINLAYER);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
   
    mainLayer->setPosition(CCPointZero);
    
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "button/popup_btn_close.png",
                                                          "button/popup_btn_close.png",
                                                          this,
                                                          menu_selector(BasicPopup::menuCloseCallback) );
    pCloseItem->setScale(1.2);
    
    
    closeMenu = CCMenu::create(pCloseItem, NULL);
    closeMenu->setPosition( ccp(mWinSize.width - 50 , mWinSize.height - 50) );
    closeMenu->setAnchorPoint(ccp(0,0));
    mainLayer->addChild(closeMenu);
    closeMenu->setZOrder(99);
    
    
    this->addChild(mainLayer);
    //mainLayer->setTouchEnabled(false);
}

void BasicPopup::initPopup(CCSize size)
{
	this->setTag(BASICPOPUP);
    this->initWithColor(ccc4(0, 0, 0, 255*0.9));
    mainLayer = CCLayerColor::create(ccc4(0, 0, 255, 0), size.width, size.height);
    mainLayer->setTag(MAINLAYER);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    
    CCSize visibleSize = pDirector->getVisibleSize();
    mainLayer->setPosition(ccp(visibleSize.width / 2 - size.width / 2, visibleSize.height / 2 - size.height / 2));
	
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "button/btn_close_01.png",
                                                          "button/btn_close_01.png",
                                                          this,
                                                          menu_selector(BasicPopup::menuCloseCallback) );
    pCloseItem->setScale(1.2);


    closeMenu = CCMenu::create(pCloseItem, NULL);
    closeMenu->setAnchorPoint(ccp(1,1));
    closeMenu->setPosition( ccp(size.width - 20 , size.height - 20) );
    
    mainLayer->addChild(closeMenu);
    closeMenu->setZOrder(99);


    this->addChild(mainLayer);
    //mainLayer->setTouchEnabled(false);
}

void BasicPopup::show()
{
    CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);

    layer->addChild(this, 300);
//    this->setAnchorPoint(ccp(0.5f, 0.5f));
//    mainLayer->setScale(0.1);
//    CCScaleTo *scale = CCScaleTo::create(0.1, 1);
//    CCEaseIn *easeIn = CCEaseIn::create(scale, 3.f);
//    mainLayer->runAction(easeIn);
}




void BasicPopup::menuCloseCallback(CCObject* pSender)
{
	this->removeAllChildren();
    this->removeFromParentAndCleanup(true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}

bool BasicPopup::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    
    return true;
}




