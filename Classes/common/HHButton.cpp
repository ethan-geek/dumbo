//
//  HHButton.cpp
//  HiHigh
//
//  Created by Insanity on 2014. 10. 17..
//
//

#include "HHButton.h"

HHButton::HHButton() : mColor(ccc3(255, 255, 255)), mWidth(0), mHeight(0), mBackgroundImage(NULL), mHasBorder(false)
{

}



HHButton::~HHButton()
{
    
}

HHButton * HHButton::create(CCNode*label, CCObject* target, SEL_MenuHandler selector)
{
    HHButton *pRet = new HHButton();
    pRet->initWithLabel(label, target, selector);
    pRet->autorelease();
    return pRet;
}

void HHButton::setString(const char * label)
{
    dynamic_cast<CCLabelProtocol*>(m_pLabel)->setString(label);
}


void HHButton::draw()
{
    CCMenuItemLabel::draw();
    
    if(mWidth == 0 || mHeight == 0) {
        this->setContentSize(CCSizeMake(m_pLabel->getContentSize().width * 1.6, m_pLabel->getContentSize().height * 1.4));
    }else {
        this->setContentSize(CCSizeMake(mWidth, mHeight));
    }
    
    if(mHasBorder) {
        ccDrawColor4B(mColor.r, mColor.g, mColor.b, 255);
        ccDrawRect(ccp(0, this->getContentSize().height), ccp(this->getContentSize().width,0));
        ccDrawRect(ccp(1, this->getContentSize().height-1), ccp(this->getContentSize().width-1, 1));
        ccDrawRect(ccp(2, this->getContentSize().height-2), ccp(this->getContentSize().width-2, 2));
        ccDrawRect(ccp(3, this->getContentSize().height-3), ccp(this->getContentSize().width-3, 3));
    }
    
    m_pLabel->setAnchorPoint(ccp(0.5, 0.5));
    if(this->getChildByTag(80) != NULL) {
        m_pLabel->setPosition(this->getContentSize().width / 2 + 20, this->getContentSize().height / 2);
    }else {
        m_pLabel->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    }
    
    //CCLog("#### %f %f /// %f %f", this->getContentSize().width, this->getContentSize().height, m_pLabel->getContentSize().width, m_pLabel->getContentSize().height);
}

void HHButton::setColor(ccColor3B color)
{
    CCMenuItemLabel::setColor(color);
    mColor = color;
    draw();
}

void HHButton::setSize(float width, float height)
{
    mWidth = width;
    mHeight = height;
    draw();
}


void HHButton::setIcon(const char *fileName, bool bContainOff)
{
    
    CCSprite * icon = CCSprite::createWithSpriteFrameName(fileName);
    icon->setTag(80);
    this->addChild(icon);
    icon->setPosition(ccp(20, this->getContentSize().height / 2 - icon->getContentSize().height / 2));
    icon->setAnchorPoint(ccp(0,0));

    if (bContainOff) {
        CCSprite * xIcon = CCSprite::createWithSpriteFrameName("icon_setting_off.png");
        xIcon->setTag(SETTING_BTN_IGNORE_TAG);
        xIcon->setAnchorPoint(ccp(0,0));
        xIcon->setVisible(false);
        CCPoint pt = icon->getPosition();
        
        xIcon->setPosition(ccp(pt.x + icon->getContentSize().width - xIcon->getContentSize().width,pt.y));
        this->addChild(xIcon);
    }
}

void HHButton::selected()
{
    // subclass to change the default action
    if(m_bEnabled)
    {
        CCMenuItem::selected();
        
        CCAction *action = getActionByTag(0xc0c05002);
        if (action)
        {
            this->stopAction(action);
        }
        else
        {
            m_fOriginalScale = this->getScale();
        }
        
        CCAction *zoomAction = CCScaleTo::create(0.1f, m_fOriginalScale * 0.85f);
        zoomAction->setTag(0xc0c05002);
        this->runAction(zoomAction);
    }
}

void HHButton::setBackgroundImage(const char *fileName)
{
    //mBackgroundImage = CCSprite::createWithSpriteFrameName(fileName);
    mBackgroundImage = CCSprite::create(fileName);
    
    mWidth = mBackgroundImage->getContentSize().width;
    mHeight = mBackgroundImage->getContentSize().height;
    
    mBackgroundImage->setAnchorPoint(CCPointZero);
    mBackgroundImage->setPosition(CCPointZero);
    this->addChild(mBackgroundImage);
    
}

void HHButton::setBorder()
{
    mHasBorder = true;
}

