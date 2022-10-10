#include "HeroStatus.h"
#include "./Hero.h"
#include "./InteractionManager.h"

HeroStatus::HeroStatus(void)
{
	if(_itemStatusList.size() <= 0) {
		_itemStatusList.push_back(HEROITEMSTATUS());
	}

	_beforeStatusArray[0] = HERO_STATUS_TYPE_DEFAULT;
	_beforeStatusArray[1] = HERO_STATUS_TYPE_DEFAULT;
}


HeroStatus::~HeroStatus(void)
{
}


bool HeroStatus::isStatus(HERO_STATUS_TYPE type) {

	for(int indexI = _itemStatusList.size() - 1 ; indexI >= 0; --indexI) {

		HEROITEMSTATUS& itemStatus = _itemStatusList[indexI];

		if(type == itemStatus._statusType) {
			return true;
		}

	}

	return false;
}

bool HeroStatus::isTilt(HERO_TILT_TYPE type) {
	if(_tileType == type ) {
		return true;
	}
	return false;
}



void HeroStatus::setStatusType(HERO_STATUS_TYPE status, interactionObject* haveItem) {
	
	// no itemStatus
	if(checkItemType(status) == false) {

		if(_itemStatusList.size() <= 0) {
			_itemStatusList.push_back(HEROITEMSTATUS());
		}
		HEROITEMSTATUS& itemStatus = _itemStatusList[0];
		
		if(itemStatus._statusType == status) {
			return;
		}
		itemStatus._statusType = status;
		_beforeStatusArray[0] = status;
	}

	else {
		// 1 ~ super, fullcoin ...
		for(int indexI = 1 ; indexI < _itemStatusList.size(); ++indexI ) { 
			HEROITEMSTATUS& itemStatus = _itemStatusList[indexI];

			if(itemStatus._statusType == status) {

				itemStatus._saveDt = 0;

				if(itemStatus._statusType == HERO_STATUS_TYPE_WEIGHT) {
					CCNode* node = AGApplication::GetInstance()->_hero->_heroWrapperSprite->getChildByTag(INTERACTION_OBJECT_TYPE_WEIGHT);
					node->removeFromParentAndCleanup(true);
				}
				if(itemStatus._statusType == HERO_STATUS_TYPE_SHIELD) {
					CCNode* node = AGApplication::GetInstance()->_hero->_heroWrapperSprite->getChildByTag(INTERACTION_OBJECT_TYPE_SHIELD);
					node->stopAllActions();
					node->removeFromParentAndCleanup(true);
                    HiHighAudio::sharedAudio()->stopEffect();
				}
				

				return;
			}

		}

		HEROITEMSTATUS itemStatus;
		itemStatus._statusType = status;
		itemStatus._imageName = haveItem->getImageName();

		if(haveItem != NULL) {
			CCLog("_statusKeepTime = %f", ((ItemObject*)haveItem)->getKeepTime());
			itemStatus._statusKeepTime = ((ItemObject*)haveItem)->getKeepTime();
		}

		_itemStatusList.push_back(itemStatus);
		CCLog("----- Item start : %d" , _itemStatusList.size());

		_timerManager.useItem(itemStatus);
	}


}

void HeroStatus::setTiltType(HERO_TILT_TYPE type) {
	_tileType = type;
}


bool HeroStatus::checkItemType(HERO_STATUS_TYPE& type) {

	
	if(checkItemRelativeVelocity(type) 
		|| checkItemUNRelativeVelocity(type) 
		|| checkItemUNDecreaseRelativeVelocity(type)) {
		return true;
	}

	return false;
}

void HeroStatus::testCurrentStatus(HERO_STATUS_TYPE& status) {
	switch (status)
	{
	case HERO_STATUS_TYPE_DEFAULT :
		CCLog("hero status : HERO_STATUS_TYPE_DEFAULT");
			   break;
	case HERO_STATUS_TYPE_DROP :
		CCLog("hero status : HERO_STATUS_TYPE_DROP");
			   break;
	case HERO_STATUS_TYPE_FALL : 
		CCLog("hero status : HERO_STATUS_TYPE_FALL");
		break;
	case HERO_STATUS_TYPE_FULLCOIN :
		CCLog("hero status : HERO_STATUS_TYPE_FULLCOIN");
		break;
	case HERO_STATUS_TYPE_JUMP :
		CCLog("hero status : HERO_STATUS_TYPE_JUMP");
		break;
	case HERO_STATUS_TYPE_STARTJUMP :
		CCLog("hero status : HERO_STATUS_TYPE_STARTJUMP");
		break;
	case HERO_STATUS_TYPE_SUPERITEM :
		CCLog("hero status : HERO_STATUS_TYPE_SUPERITEM");
		break;
	case HERO_STATUS_TYPE_TRAP :
		CCLog("hero status : HERO_STATUS_TYPE_TRAP");
		break;
	default:
		break;
	}
}

bool HeroStatus::checkKeepTime(float dt) {

	for(int indexI = 1 ; indexI < _itemStatusList.size(); ++indexI ) {
		HEROITEMSTATUS& itemStatus = _itemStatusList[indexI];

		if(itemStatus._statusKeepTime != 0) {

			itemStatus._saveDt += dt;

			_timerManager.flowTime(itemStatus._statusType, itemStatus._saveDt);

			if(checkItemRelativeVelocity(itemStatus._statusType)) {
				AGApplication::GetInstance()->_hero->_heroBody->SetLinearVelocity(b2Vec2(0, AGUtil::getSpeed(itemStatus._statusType)));
			}


			if(itemStatus._statusKeepTime <= itemStatus._saveDt) {

				if(itemStatus._statusType == HERO_STATUS_TYPE_WEIGHT) {
					CCLog("===== close HERO_STATUS_TYPE_WEIGHT");
					AGApplication::GetInstance()->setWeightMultiple(1);
					CCNode* node = AGApplication::GetInstance()->_hero->_heroWrapperSprite->getChildByTag(INTERACTION_OBJECT_TYPE_WEIGHT);
					node->removeFromParentAndCleanup(true);
				}
				if(itemStatus._statusType == HERO_STATUS_TYPE_SHIELD) {
					CCLog("===== close HERO_STATUS_TYPE_SHIELD");
					CCNode* node = AGApplication::GetInstance()->_hero->_heroWrapperSprite->getChildByTag(INTERACTION_OBJECT_TYPE_SHIELD);
					node->stopAllActions();
					node->removeFromParentAndCleanup(true);
                    HiHighAudio::sharedAudio()->stopEffect();
				}
				if(itemStatus._statusType == HERO_STATUS_TYPE_FULLCOIN) {
					AGApplication::GetInstance()->getInteractionManager()->changeHeight();
				}

				_timerManager.removeItem(itemStatus._statusType);
				_beforeStatusArray[1] = itemStatus._statusType;
				itemStatus._statusType = HERO_STATUS_TYPE_DEFAULT;
				itemStatus._statusKeepTime = 0 ;

				_itemStatusList.erase(_itemStatusList.begin() + indexI);
				
				setStatusType(HERO_STATUS_TYPE_JUMP, NULL);
				return true;

			}
			else {

			}

		}
	}
	return false;
}

bool HeroStatus::isStatusRelativeVelocity() {

	for(int indexI = 0; indexI < _itemStatusList.size() ; ++indexI) {

		HEROITEMSTATUS& status = _itemStatusList[indexI];

		if(checkItemRelativeVelocity(status._statusType)) {
			return true;
		}

	}

	return false;

}

bool HeroStatus::isStatusUNDecreaseRelativeVelocity() { 
	for(int indexI = 0; indexI < _itemStatusList.size() ; ++indexI) {

		HEROITEMSTATUS& status = _itemStatusList[indexI];

		if(checkItemUNDecreaseRelativeVelocity(status._statusType)) {
			return true;
		}

	}

	return false;
}

bool HeroStatus::checkItemRelativeVelocity(HERO_STATUS_TYPE& type) {

	if(type == HERO_STATUS_TYPE_SUPERITEM
		|| type == HERO_STATUS_TYPE_STARTJUMP){
			return true;
	}
	return false;
}

bool HeroStatus::checkItemUNRelativeVelocity(HERO_STATUS_TYPE& type) {

	if(type == HERO_STATUS_TYPE_FULLCOIN
		|| type == HERO_STATUS_TYPE_WEIGHT
		|| type == HERO_STATUS_TYPE_MAGNET
		|| type == HERO_STATUS_TYPE_DOUBLE){
		return true;
	}
	return false;
}

bool HeroStatus::checkItemUNDecreaseRelativeVelocity(HERO_STATUS_TYPE& type) {
	if(type == HERO_STATUS_TYPE_SHIELD){
		return true;
	}
	return false;
}

HEROITEMSTATUS HeroStatus::getDefaultStatus() {
	return _itemStatusList[0];
}


HERO_STATUS_TYPE HeroStatus::getBeforeStatus() {
	return _beforeStatusArray[0];
}
HERO_STATUS_TYPE HeroStatus::getBeforeStatusItem() {
	return _beforeStatusArray[1];
}