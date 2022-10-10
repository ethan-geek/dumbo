#include "ItemTimerManager.h"


ItemTimerManager::ItemTimerManager(void) : _index(0)
{

	for(int indexI = 0 ; indexI < PROGRASSBAR_ARRAY_SIZE; ++indexI) {
		_itemTimerList[indexI] = ItemTimer();
	}

}


ItemTimerManager::~ItemTimerManager(void)
{
}


void ItemTimerManager::useItem(HEROITEMSTATUS& status) {

	if(_itemTimerMap.find(status._statusType) != _itemTimerMap.end()) {
		ItemTimer& timer = _itemTimerMap[status._statusType];
		timer.timeInit();
		return;
	}
	if(status._imageName == "" && status._statusType != HERO_STATUS_TYPE_STARTJUMP) {
		return;
	}

	for(int indexI = 0 ; indexI < PROGRASSBAR_ARRAY_SIZE; ++indexI) {
		if(_itemTimerList[indexI].getObjectType() == HERO_STATUS_TYPE_DEFAULT) {
			_index = indexI;
			break;
		}
	}
    
    CCSprite* partsFrame = (CCSprite*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS);
    
    CCSprite* item = NULL;
    if (status._imageName == "SuperItem.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_super.png");
    }else if(status._imageName == "Umbrella.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_drop.png");
    }else if(status._imageName == "Magnet.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_magnet.png");
    }else if(status._imageName == "Shield.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_shield.png");
    }else if(status._imageName == "FullCoin.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_fullcoin.png");
    }else if(status._imageName == "DoubleItem.png") {
        item = CCSprite::createWithSpriteFrameName("gage_icon_2x.png");
	}
	
	if(status._statusType == HERO_STATUS_TYPE_STARTJUMP) {
        item = CCSprite::createWithSpriteFrameName("gage_icon_rocket.png");
    }
    
    CCSprite* background = CCSprite::createWithSpriteFrameName("btn_bg_gage_middle.png");
    
//	string temp = status._imageName;
//    CCSprite* item = CCSprite::createWithSpriteFrameName(temp.c_str());
    item->setAnchorPoint(ccp(1, 0.5));
	item->setPosition(ccp(background->getContentSize().width - 3, background->getContentSize().height/2));
    
	background->addChild(item);
	partsFrame->addChild(background);
    
    background->setAnchorPoint(ccp(1, 0.5));
	background->setPosition(ccp(AGApplication::GetInstance()->_winSize.width - 12 ,
		AGApplication::GetInstance()->_winSize.height - 76 -(background->getContentSize().height* _index)));

	ItemTimer timer;
	timer.setData(background, status._statusType , status._statusKeepTime );
	
	_itemTimerList[_index] = timer;
	
}

void ItemTimerManager::flowTime(HERO_STATUS_TYPE& type, float flowTime) {

	/*if(_itemTimerMap.find(type) == _itemTimerMap.end()) {
		return;
	}*/

	for(int indexI = 0 ; indexI < PROGRASSBAR_ARRAY_SIZE; ++indexI) {
		if(_itemTimerList[indexI].getObjectType() == type) {
			_itemTimerList[indexI].tick(flowTime);
			break;
		}
	}

}

void ItemTimerManager::removeItem(HERO_STATUS_TYPE& type) {

	

	for(int indexI = 0 ; indexI < PROGRASSBAR_ARRAY_SIZE; ++indexI) {
		if(_itemTimerList[indexI].getObjectType() == type) {
			_itemTimerList[indexI].release();
			break;
		}
	}

}

