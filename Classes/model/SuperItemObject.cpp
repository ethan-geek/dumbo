///////////////////////////////////////////////////////////
//  SuperItemObject.cpp
//  Implementation of the Class SuperItemObject
//  Created on:      19-3-2014 ���� 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "SuperItemObject.h"
#include "../game/Hero.h"

#include "../common/AGEarthQuakeEffect.h"

SuperItemObject::SuperItemObject()  {

	_objectType = INTERACTION_OBJECT_TYPE_SUPERITEM;

	ItemObject::applyUpgrade(STR_SUPER_ITEM_NAME);
}



SuperItemObject::~SuperItemObject(){

}

void SuperItemObject::useItem() {

	interactionObject::useItem();
    HiHighAudio::sharedAudio()->playEffect("superitem");
	HiHighAudio::sharedAudio()->vibrate(_keepTime);
	AGApplication::GetInstance()->setSpeed(HERO_STATUS_TYPE_SUPERITEM);
	CCParticleSystem *superPaticle = CCParticleSystemQuad::create("paticle/super_t2.plist");
    superPaticle->setAutoRemoveOnFinish(true);
	superPaticle->setDuration(_keepTime);
    superPaticle->setScale(2);
	superPaticle->setAnchorPoint(ccp(0,0));
	superPaticle->setPosition(ccp(0,-20));
	AGApplication::GetInstance()->_hero->_heroWrapperSprite->addChild(superPaticle, 5);
    
    CCParticleSystem *superBGParticle = CCParticleSystemQuad::create("paticle/super_bg.plist");
    superBGParticle->setScale(2);
    superBGParticle->setAutoRemoveOnFinish(true);
    superBGParticle->setDuration(_keepTime);
    CCLayer* target = (CCLayer*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS);
    superBGParticle->setPosition(ccp(target->getContentSize().width/2, target->getContentSize().height/2));
    target->addChild(superBGParticle);

	AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE)->runAction(AGEarthQuakeEffect::actionWithDuration(_keepTime, 3.0f));
    
    CCLayer* coreLayer = (CCLayerColor*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE);
    CCScaleTo *scaleDown = CCScaleTo::create(1.6, 0.88);
    CCScaleTo *scaleUp = CCScaleTo::create(1.2, 1);
    CCSequence *seq = CCSequence::create(scaleDown, CCDelayTime::create(_keepTime-1), scaleUp, NULL);
    coreLayer->runAction(seq);
    

    
	_checkRemove = true;
	
}


