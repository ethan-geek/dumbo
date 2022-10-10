#include "WeighItemObject.h"
#include "../game/Hero.h"

WeighItemObject::WeighItemObject(void)
{

	_objectType = INTERACTION_OBJECT_TYPE_WEIGHT;
	
	ItemObject::applyUpgrade(STR_PARACHUTE_ITEM_NAME);

}


WeighItemObject::~WeighItemObject(void)
{
}


void WeighItemObject::useItem() {

	interactionObject::useItem();

	AGApplication::GetInstance()->setSpeed(HERO_STATUS_TYPE_WEIGHT);
	_application->setWeightMultiple(PARACHUTE_RATIO);

	CCSprite *parachute = CCSprite::createWithSpriteFrameName("parachute.png");
	parachute->setPosition(ccp(0, -5));
	parachute->setTag(this->getInteractionObjectType());
	parachute->setVisible(false);
	AGApplication::GetInstance()->_hero->_heroWrapperSprite->addChild(parachute, 4);
	if(AGApplication::GetInstance()->getHeroVelocity() < 0 ) {
		AGApplication::GetInstance()->setHeroVelocity(-1);
	}


	_checkRemove = true;

}

