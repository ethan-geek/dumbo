///////////////////////////////////////////////////////////
//  FakeFootBarObject.cpp
//  Implementation of the Class FakeFootBarObject
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "FakeFootBarObject.h"


FakeFootBarObject::FakeFootBarObject() : _isAnimation(false), _angle(0){

	if(CCAnimationCache::sharedAnimationCache()->animationByName("AnimFakeFoot") == NULL ){
		CCArray *frames = CCArray::create();
		char temp[30];
		for(int indexI = 1 ; indexI < 20+1; ++indexI ) {
			sprintf(temp, "fake_footbar00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "AnimFakeFoot");
	}

}



FakeFootBarObject::~FakeFootBarObject(){

}

void FakeFootBarObject::setAngle(float angle)
{
	_angle = angle;
}
float FakeFootBarObject::getAngle()
{
	return _angle;
}


void FakeFootBarObject::processContact() {

	if(_checkContact == false) {
		return;
	} 

	if(AGApplication::GetInstance()->getHeroVelocity() >= 0 ) {
		_checkContact = false;
		return;
	}

	if(_isAnimation) {
		return;
	}

	HiHighAudio::sharedAudio()->playEffect("fakefootbar");

	_checkContact = false;


	processAnimation();
	//_checkRemove = true;
}



void FakeFootBarObject::processAnimation() {

	_isAnimation = true;


	CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("AnimFakeFoot"));

	CCCallFunc * func = CCCallFunc::create(_sprite, callfunc_selector(FakeFootBarObject::removeFakeFootBar));
	//CCActionInterval* move = CCMoveTo::create(0.01,ccp(_sprite->getPositionX(), -20));
	CCSequence* seq = CCSequence::create(animate, func, NULL);
	//_sprite->setAnchorPoint(ccp(0.5,0.67));
	_sprite->runAction(seq);

	//_sprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("FakeFootBar_off.png"));

	//CCFadeOut *fadeout = CCFadeOut::create(1.0);
	//CCCallFunc *callbackAction = CCCallFunc::create(_sprite, callfunc_selector(FakeFootBarObject::removeFakeFootBar));
	//CCSequence *seq = CCSequence::create(fadeout, callbackAction, NULL);
	//_sprite->runAction(seq);

}

void FakeFootBarObject::removeFakeFootBar() {
	_checkRemove = true;
}
