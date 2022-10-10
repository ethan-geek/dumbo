#include "ItemObject.h"
#include "../game/Hero.h"
#include "../model/UserInfo.h"

ItemObject::ItemObject(void)
{
	_keepTime = 3;
	_itemHaveType = ITEM_HAVE_TYPE_YES;
    
}


ItemObject::~ItemObject(void)
{
}


float ItemObject::getKeepTime() {
	return _keepTime;
}


void ItemObject::processContact() {
	if(_checkContact == false) {
		return;
	}
	if(_checkHave) {
		return;
	}

	_checkContact = false;
	_sprite->setVisible(false);
	
	_application->setSpeed(HERO_STATUS_TYPE_JUMP);

	AGApplication::GetInstance()->_hero->setItem(this);
}


void ItemObject::applyUpgrade(const char* itemStr) {

	UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
	UserUpgradeInfo* userUpgradeInfo = userInfo->getUserUpgradeInfo(itemStr);

	if (userUpgradeInfo != NULL && userUpgradeInfo->getUpgradeCount() > 0)
	{
		_keepTime = _keepTime + userUpgradeInfo->getUpgradeTime();
	}

}