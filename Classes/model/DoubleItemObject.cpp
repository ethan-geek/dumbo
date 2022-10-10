#include "DoubleItemObject.h"
#include "../game/Hero.h"

DoubleItemObject::DoubleItemObject(void)
{
	_keepTime = 4;
	_objectType = INTERACTION_OBJECT_TYPE_DOUBLE;

	ItemObject::applyUpgrade(STR_DOUBLE_ITEM_NAME);

}


DoubleItemObject::~DoubleItemObject(void)
{
}


void DoubleItemObject::useItem() {
	interactionObject::useItem();
    
	_application->setSpeed(HERO_STATUS_TYPE_DOUBLE);
    
	_checkRemove = true;
}

