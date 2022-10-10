#include "MagnetItemObject.h"
#include "../game/Hero.h"
#include "../model/UserInfo.h"


MagnetItemObject::MagnetItemObject(void)
{

	_keepTime = 2;
	_objectType = INTERACTION_OBJECT_TYPE_MAGNET;

	ItemObject::applyUpgrade(STR_MAGNET_ITEM_NAME);

}


MagnetItemObject::~MagnetItemObject(void)
{
}


void MagnetItemObject::useItem() {

	interactionObject::useItem();
	AGApplication::GetInstance()->setSpeed(HERO_STATUS_TYPE_MAGNET);
    HiHighAudio::sharedAudio()->playEffect("magnet");	
	_checkRemove = true;

}
