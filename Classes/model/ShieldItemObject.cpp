#include "ShieldItemObject.h"
#include "../game/hero.h"
#include "../model/UserInfo.h"

ShieldItemObject::ShieldItemObject(void)
{

	_objectType = INTERACTION_OBJECT_TYPE_SHIELD;

	ItemObject::applyUpgrade(STR_SHIELD_ITEM_NAME);

}


ShieldItemObject::~ShieldItemObject(void)
{
}

void ShieldItemObject::useItem() {

	interactionObject::useItem();

	AGApplication::GetInstance()->setSpeed(HERO_STATUS_TYPE_SHIELD);
    HiHighAudio::sharedAudio()->playEffectLoop("shield");

	CCSprite *shield = CCSprite::createWithSpriteFrameName("Shield_action.png");
	shield->setPosition(ccp(0, 0));
	int tag = this->getInteractionObjectType();
	shield->setTag(this->getInteractionObjectType());
	AGApplication::GetInstance()->_hero->_heroWrapperSprite->addChild(shield, 4);
	CCScaleTo *scaleUp = CCScaleTo::create(0.4, 1.05);
	CCScaleTo *scaleDown = CCScaleTo::create(0.4, 0.95);
	CCSequence *seq = CCSequence::create(scaleUp, scaleDown, NULL);
	CCRepeatForever *r = CCRepeatForever::create(seq);
	shield->runAction(r);

	_checkRemove = true;
}
