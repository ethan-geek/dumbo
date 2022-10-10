///////////////////////////////////////////////////////////
//  TrapObject.cpp
//  Implementation of the Class TrapObject
//  Created on:      19-3-2014 ���� 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "TrapObject.h"
#include "../common/AGEarthQuakeEffect.h"

TrapObject::TrapObject(){

}



TrapObject::~TrapObject(){

}


void TrapObject::processContact() {

	if(_checkContact == false) {
		return;
	}

	_checkContact = false;
	

	if (_application->setSpeed(HERO_STATUS_TYPE_TRAP)) {
		AGApplication::GetInstance()->getGameData()->initCombo();
		HiHighAudio::sharedAudio()->playEffect("trap");
		HiHighAudio::sharedAudio()->vibrate();
		CCParticleSystem *inkParticle = CCParticleSystemQuad::create("paticle/trapInk.plist");
		inkParticle->setAutoRemoveOnFinish(true);
		inkParticle->setAnchorPoint(ccp(0, 0));
		inkParticle->setPosition(ccp(0, 0));

		_application->_parallaxNode->addChild(inkParticle, ZINDEX_PATICLE, ccp(0.0, 1.0), ccp(_sprite->getPositionX(), -_application->_parallaxNode->getPositionY() + (_sprite->getPositionY())));
        AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE)->runAction(AGEarthQuakeEffect::actionWithDuration(1.0f, 5.0f));
		this->sprayInk();

		_sprite->setVisible(false);
		_checkRemove = true;
	}
	else {
		_sprite->setVisible(false);
		_checkRemove = true;
	}

}

void TrapObject::fadeoutInk(CCObject* obj) {

    HiHighAudio::sharedAudio()->playEffect("ink");
    CCSprite* pInk = (CCSprite*)obj;
	CCFadeOut *fadeout = CCFadeOut::create(1.5);
	CCCallFunc *inkCallback = CCCallFuncO::create(pInk, callfuncO_selector(TrapObject::removeInk),pInk);
	CCSequence *seq = CCSequence::create(fadeout, inkCallback, NULL);

	pInk->runAction(seq);
	_checkRemove = true;
}

void TrapObject::removeInk(CCObject* obj)
{ 
	CCSprite* pInk = (CCSprite*)obj;
	pInk->removeFromParent();
	pInk = NULL;
}

void TrapObject::sprayInk()
{
	CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
	CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);

	float scaleMin = 0.5;
	float scaleMax = 1.5;
	float positionXMin = 50;
	float positionXMax = layer->getContentSize().width-50;
	float positionYMin = 50;
	float positionYMax = layer->getContentSize().height-50;
	float rotationMin = 0;
	float rotationMax = 360;
	float delayMin = 0.15;
	float delayMax = 0.35;

	for (int i = 0; i < 4; i++)
	{
		CCSprite * ink = CCSprite::createWithSpriteFrameName(AGUtil::reSizeImage("game_effect_ink.png").c_str());
		ink->setOpacity(0.2);
		float scaleRand = (float)AGApplication::GetInstance()->getRand() / (float)RAND_MAX;
		float scale = scaleMin + scaleRand * (scaleMax - scaleMin);
		ink->setScale(0.1);

		float posXRand = (float)AGApplication::GetInstance()->getRand() / (float)RAND_MAX;
		float posX = positionXMin + posXRand * (positionXMax - positionXMin);
		float posYRand = (float)AGApplication::GetInstance()->getRand() / (float)RAND_MAX;
		float posY = positionYMin + posYRand * (positionYMax - positionYMin);
		float rotation = rotationMin + scaleRand * (rotationMax - rotationMin);

		ink->setPosition(ccp(posX, posY)); 
		ink->setRotation(rotation);
		layer->addChild(ink, 300);

		CCScaleTo *scale_ = CCScaleTo::create(0.06, scale);
		CCEaseIn *easeIn = CCEaseIn::create(scale_, 0.6f);

		CCCallFunc *inkCallback = CCCallFuncO::create(_sprite, callfuncO_selector(TrapObject::fadeoutInk), ink);
		CCSequence *seq = CCSequence::create(CCDelayTime::create(delayMin + scaleRand * (delayMax - delayMin)), easeIn, inkCallback, NULL);

		ink->runAction(seq);

	}


    
}
