#include "StartItemObject.h"
#include "../game/Hero.h"


StartItemObject::StartItemObject(void)
{
	_keepTime = 2;
	_objectType = INTERACTION_OBJECT_TYPE_STARTJUMP;

	ItemObject::applyUpgrade(STR_START_ITEM_NAME);

}


StartItemObject::~StartItemObject(void)
{
}

void StartItemObject::useItem() {

    interactionObject::useItemEffect();
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

	AGApplication::GetInstance()->setSpeed(HERO_STATUS_TYPE_STARTJUMP);
    
    CCLayer* coreLayer = (CCLayerColor*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE);
    CCScaleTo *scaleDown = CCScaleTo::create(1.2, 0.8);
    CCScaleTo *scaleUp = CCScaleTo::create(1.2, 1);
    CCSequence *seq = CCSequence::create(scaleDown, CCDelayTime::create(2), scaleUp, NULL);
    coreLayer->runAction(seq);
}

