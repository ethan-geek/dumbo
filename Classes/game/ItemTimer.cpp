#include "ItemTimer.h"


ItemTimer::ItemTimer(void) : _type(HERO_STATUS_TYPE_DEFAULT) 
{
}


ItemTimer::~ItemTimer(void)
{
}

void ItemTimer::timeInit() {
	_timer->setPercentage(100.0f);
}
void ItemTimer::setData(CCSprite* parent,HERO_STATUS_TYPE type, float totalTime) {
	_parent = parent;
	_type = type;
	_totalTime = totalTime;

	CCSprite* sp = CCSprite::createWithSpriteFrameName("btn_gage_bar.png");
    sp->setOpacity(255*0.5);
    sp->setAnchorPoint(ccp(1, 0.5));
	_timer = CCProgressTimer::create(sp);
	
	_timer->setType(kCCProgressTimerTypeBar);
	_timer->setPercentage(100.0f);
    _timer->setPosition(ccp(parent->getContentSize().width/2 - 12, parent->getContentSize().height/2));
	_timer->setMidpoint(ccp(1,0));
	_timer->setBarChangeRate(ccp(1, 0));
	
	_parent->addChild(_timer);
}
void ItemTimer::tick(float dt) {
	float percentage = 100.0f- 100.0f * (dt/_totalTime) ;
	_timer->setPercentage(percentage);
}

void ItemTimer::release() {
	_parent->removeAllChildren();
	_parent->removeFromParentAndCleanup(true);
	_type = HERO_STATUS_TYPE_DEFAULT;
}


HERO_STATUS_TYPE ItemTimer::getObjectType() {
	return _type;
}