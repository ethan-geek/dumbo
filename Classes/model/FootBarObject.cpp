///////////////////////////////////////////////////////////
//  FootBarObject.cpp
//  Implementation of the Class FootBarObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "FootBarObject.h"


FootBarObject::FootBarObject(){

}



FootBarObject::~FootBarObject(){

}

void FootBarObject::setAngle(float angle)
{
	_angle = angle;
}
float FootBarObject::getAngle()
{
	return _angle;
}

void FootBarObject::setSprite(cocos2d::CCSprite *sprite)
{
    interactionObject::setSprite(sprite);
    bool isFlip = false;
    isFlip = AGApplication::GetInstance()->getRand() % 2;
    sprite->setFlipX(isFlip);
}

void FootBarObject::processContact() {

	if(_checkContact == false) {
		return;
	} 

	if(AGApplication::GetInstance()->getHeroVelocity() >= 0 ) {
		_checkContact = false;
		return;
	}
	
    HiHighAudio::sharedAudio()->playEffect("footbar");
    
	_application->setSpeed(HERO_STATUS_TYPE_FOOTBAR);
	_checkContact = false;

	processAnimation();

}


void FootBarObject::processAnimation() {
//
//	CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
//	CCAnimate* animate = CCAnimate::create(animationCache->animationByName("AnimFootBar"));
//	CCAction *action = CCRepeat::create(animate, 1);
//
//	this->getSprite()->runAction(action);

	//particle
	CCParticleSystem *footbarPtc = CCParticleSystemQuad::create("paticle/footbar.plist");
	footbarPtc->setAutoRemoveOnFinish(true);
	footbarPtc->setScale(0.9);
	footbarPtc->setAnchorPoint(ccp(0, 0));
	_application->_parallaxNode->addChild(footbarPtc, ZINDEX_PATICLE, ccp(0.0, 1.0), ccp(_sprite->getPositionX(), -_application->_parallaxNode->getPositionY() + (_sprite->getPositionY())));

}