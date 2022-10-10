///////////////////////////////////////////////////////////
//  FullCoinItemObject.cpp
//  Implementation of the Class FullCoinItemObject
//  Created on:      19-3-2014 ���� 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "FullCoinItemObject.h"
#include "../game/Hero.h"


FullCoinItemObject::FullCoinItemObject() {

	_keepTime = 2;
	_objectType = INTERACTION_OBJECT_TYPE_FULLCOIN;

	ItemObject::applyUpgrade(STR_FULL_COIN_ITEM_NAME);

}



FullCoinItemObject::~FullCoinItemObject(){

}



void FullCoinItemObject::useItem() {

	interactionObject::useItem();
    HiHighAudio::sharedAudio()->playEffect("fullcoin");
	
	_application->setSpeed(HERO_STATUS_TYPE_FULLCOIN);
	_application->setGravity(0);
	
	_checkRemove = true;
}


