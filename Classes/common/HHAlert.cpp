//
//  HHAlert.cpp
//  HiHigh
//
//  Created by insanity on 2014. 5. 22..
//
//

#include "HHAlert.h"
#include "../common/HHButton.h"
#define ALERT_HEIGHT 364

HHAlert::HHAlert() :  _title(NULL), _message(NULL), _okBtnLabel(NULL), _cancelBtnLabel(NULL), okayBtn(NULL), _showFlag(false),_isPush(false)
{
}



HHAlert::~HHAlert()
{
    
}

HHAlert* HHAlert::create(char const*  title, char const*  message, char const*  okBtnLabel, char const*  cancelBtnLabel)
{
    HHAlert *pRet = new HHAlert();
    pRet->autorelease();
    pRet->_title = title;
    pRet->_message = message;
    pRet->_okBtnLabel = okBtnLabel;
    pRet->_cancelBtnLabel = cancelBtnLabel;
    
    pRet->initAlert();
    
    return pRet;
}


void HHAlert::initAlert()
{
    this->initWithColor(ccc4(30,30,30,200));
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    
    
    CCSize visibleSize = pDirector->getVisibleSize();
    
    _alertlayer = CCLayerColor::create(ccc4(10,10,10,240), visibleSize.width, ALERT_HEIGHT);
    _alertlayer->setAnchorPoint(CCPointZero);
    _alertlayer->setPosition(ccp(0, visibleSize.height / 2 - _alertlayer->getContentSize().height/2));
    
    CCSprite* topLine = CCSprite::createWithSpriteFrameName("sub_titlebar_top.png");
    CCSprite* bottomLine = CCSprite::createWithSpriteFrameName("sub_titlebar_bottom.png");
    topLine->setAnchorPoint(CCPointZero);
    bottomLine->setAnchorPoint(CCPointZero);
    topLine->setPosition(ccp(0, ALERT_HEIGHT));
    bottomLine->setPosition(ccp(0, 0));
    _alertlayer->addChild(topLine);
    _alertlayer->addChild(bottomLine);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "button/popup_btn_close.png",
                                                          "button/popup_btn_close.png",
                                                          this,
                                                          menu_selector(HHAlert::close) );

    
    CCMenu * closeMenu = CCMenu::create(pCloseItem, NULL);
    closeMenu->setPosition( ccp(visibleSize.width - 30 , ALERT_HEIGHT - 30) );
    closeMenu->setAnchorPoint(ccp(0,0));
    _alertlayer->addChild(closeMenu);
    closeMenu->setZOrder(100);
    closeMenu->setScale(0.8);
    closeMenu->setVisible(false);
    
    if(_title != NULL) {
        titleLabel = CCLabelBMFont::create(_title, TEXT_FONT_SMALL);
        titleLabel->setPosition(ccp(_alertlayer->getContentSize().width / 2, ALERT_HEIGHT - 40));
        _alertlayer->addChild(titleLabel);
    }
    
    if(_message != NULL) {
		messageLabel = CCLabelBMFont::create(_message, TEXT_FONT_SMALL);
        messageLabel->setPosition(ccp(_alertlayer->getContentSize().width / 2, ALERT_HEIGHT - 130));
        _alertlayer->addChild(messageLabel);
    }
    
    CCMenuItemLabel *cancelBtn = NULL;
    if(_cancelBtnLabel != NULL) {

        cancelBtn = AGUtil::createLabelButton(_cancelBtnLabel, TEXT_FONT_SMALL, "", "btn_bg_05.png", 0, this, menu_selector(HHAlert::cancelBtnListener));
        
        //cancelBtn->setPosition(ccp(200, 75));
//		if (_okBtnLabel == NULL) {
//			cancelBtn->setPosition(ccp(visibleSize.width / 2, 75));
//		}
    }

    if(_okBtnLabel != NULL) {
        okayBtn = AGUtil::createLabelButton(_okBtnLabel, TEXT_FONT_SMALL, "", "btn_bg_05.png", 0);

        //okayBtn->setPosition(ccp(visibleSize.width  - 200, 75));
//        if (_cancelBtnLabel == NULL) {
//            okayBtn->setPosition(ccp(visibleSize.width  / 2, 75));
//        }
    }
    
    CCMenu *menu = NULL;
    if(okayBtn && !cancelBtn) {
        menu = CCMenu::create(okayBtn, NULL);
    }else if(cancelBtn && !okayBtn) {
        menu = CCMenu::create(cancelBtn, NULL);
    }else {
        menu = CCMenu::create(cancelBtn, okayBtn, NULL);
    }
    menu->setZOrder(100);
    menu->setPosition(ccp(_alertlayer->getContentSize().width/2, 75));
    menu->alignItemsHorizontallyWithPadding(30);
    
    _alertlayer->addChild(menu);
    _alertlayer->setTouchEnabled(false);
    this->addChild(_alertlayer);
}

void HHAlert::close(CCObject* obj)

{
	if(_isPush) {
		CCDirector::sharedDirector()->popScene();	
		_isPush = false;
	}

    this->removeFromParentAndCleanup(true);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}

void HHAlert::show()
{
    CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
    layer->addChild(this, 300);


    _showFlag = true;


}

void HHAlert::showPush() {

	_isPush = true;
	
	CCScene *scene = CCScene::create();
	scene->setContentSize(this->getContentSize());	
    scene->addChild(this);
    //CCTransitionScene* transition = CCTras::create(0.1f, scene);
	CCDirector::sharedDirector()->pushScene(scene);
}

void HHAlert::setImage(CCSprite *sprite)
{
    sprite->setPosition(ccp(_alertlayer->getContentSize().width /2, _alertlayer->getContentSize().height - sprite->getContentSize().height/2));
    _alertlayer->addChild(sprite);
}

bool HHAlert::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void HHAlert::cancelBtnListener(CCObject *obj)
{
	if(_isPush) {
		CCDirector::sharedDirector()->popScene();	
		_isPush = false;
	/*	return;*/
	}

    close(obj);
    _showFlag = false;
}

bool HHAlert::isShow() {

	return _showFlag;
}


