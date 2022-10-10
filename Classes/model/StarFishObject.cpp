#include "StarFishObject.h"
#include "../game/Hero.h"


StarFishObject::StarFishObject(void)
{
}


StarFishObject::~StarFishObject(void)
{
}

void StarFishObject::setSprite(CCSprite* sprite) {
	interactionObject::setSprite(sprite);
	CCScaleTo *scaleUp = CCScaleTo::create(0.6, 1.05);
	CCScaleTo *scaleDown = CCScaleTo::create(0.6, 0.95);
	CCSequence *seq = CCSequence::create(scaleUp, scaleDown, NULL);
	CCRepeatForever *r = CCRepeatForever::create(seq);
	this->_sprite->runAction(r);
}

void StarFishObject::processContact()   { 

	if(_checkContact == false) {
		return;
	}

	HiHighAudio::sharedAudio()->playEffect("starfish");

    CCParticleSystem *ptc = CCParticleSystemQuad::create("paticle/speed.plist");
    ptc->setAutoRemoveOnFinish(true);
    ptc->setDuration(1.5);
    ptc->setAnchorPoint(ccp(0,0));
    ptc->setPosition(ccp(0,-20));
    AGApplication::GetInstance()->_hero->_heroWrapperSprite->addChild(ptc, 5);

	_application->setSpeed(HERO_STATUS_TYPE_STARFISH);
	

	
	_checkContact = false;
	_checkRemove = true;

}

void StarFishObject::useItem()
{
    interactionObject::useItem();
    
}