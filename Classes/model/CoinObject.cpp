///////////////////////////////////////////////////////////
//  CoinObject.cpp
//  Implementation of the Class CoinObject
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "CoinObject.h"


CoinObject::CoinObject() :  _coinType(COIN_TYPE_NORMAL), _coin(NULL){

}



CoinObject::~CoinObject(){

}


void CoinObject::initRigid() {
	
	 string coin = _imageName;
	AGUtil::replaceStr(coin, "_light.png", ".png");

	if(AGApplication::GetInstance()->_hero->isStatus(HERO_STATUS_TYPE_FULLCOIN)) {
		_sprite->initWithSpriteFrameName(coin.c_str());
		return;
	}
	
	CCSprite* shiny = CCSprite::createWithSpriteFrameName(_imageName.c_str());
	
	_coin = CCSprite::createWithSpriteFrameName(coin.c_str());
	
	_sprite->setOpacity(0);
	_coin->setTag(6969);	
	shiny->setTag(6969);
	_sprite->addChild(shiny);
	_sprite->addChild(_coin);

	shiny->setPosition(ccp(_sprite->getContentSize().width/2,_sprite->getContentSize().height/2));
	_coin->setPosition(ccp(_sprite->getContentSize().width/2,_sprite->getContentSize().height/2));


	if(_sizeType != COIN_SIZE_TYPE_BIG) {
		return;
	}
	shiny->setScale(0.7);
	CCScaleTo *scaleUp = CCScaleTo::create(0.7, 1.10);
	CCScaleTo *scaleDown = CCScaleTo::create(0.7, 0.8);
	CCSequence *seq = CCSequence::create(scaleUp, scaleDown, NULL);
	CCRepeatForever *r = CCRepeatForever::create(seq);

	shiny->runAction(r);
	


}


void CoinObject::processGold(){

}

void CoinObject::setCoinSizeType(string coinSizeType) {

	if(coinSizeType == "CoinSmall") {
		_sizeType = COIN_SIZE_TYPE_SMALL;
		_goldAmount = GOLD_AMOUNT_TYPE_SMALL;
	}
	else if(coinSizeType == "CoinNormal") {
		_sizeType = COIN_SIZE_TYPE_NORMAL;
		_goldAmount = GOLD_AMOUNT_TYPE_NORMAL;
	}
	else if(coinSizeType == "CoinBig") {
		_sizeType = COIN_SIZE_TYPE_BIG;
		_goldAmount = GOLD_AMOUNT_TYPE_BIG;
	}
	else if(coinSizeType == "DynamicCoinSmall") {
		_sizeType = COIN_SIZE_TYPE_SMALL;
		_goldAmount = GOLD_AMOUNT_TYPE_SMALL;
	}

	else if(coinSizeType == "DynamicCoinNormal") {
		_sizeType = COIN_SIZE_TYPE_NORMAL;
		_goldAmount = GOLD_AMOUNT_TYPE_NORMAL;
	}
	else if(coinSizeType == "DynamicCoinBig") {
		_sizeType = COIN_SIZE_TYPE_BIG;
		_goldAmount = GOLD_AMOUNT_TYPE_BIG;
	}
}

COIN_SIZE_TYPE CoinObject::getCoinSizeType() {
	return _sizeType;
}

int CoinObject::getGoldAmount() {
	return _goldAmount;
}


void CoinObject::processContact() {

	if(_checkContact == false) {
		return;
	}

	HiHighAudio::sharedAudio()->playEffect("coin");

	CCParticleSystem *coinPaticle = CCParticleSystemQuad::create("paticle/coin_star2.plist");
    coinPaticle->setScale(0.5);
	coinPaticle->setAutoRemoveOnFinish(true);
	coinPaticle->setAnchorPoint(ccp(0,0));
	_application->_parallaxNode->addChild(coinPaticle,ZINDEX_PATICLE, ccp(0.0, 1.0), ccp(_sprite->getPositionX(),  (-_application->_parallaxNode->getPositionY() + (_sprite->getPositionY()))-10 ));

	_application->getGameData()->increaseGold(_goldAmount);
	_application->setSpeed(HERO_STATUS_TYPE_JUMP);

    
    if(_application->_hero->isStatus(HERO_STATUS_TYPE_DOUBLE)) {
        CCSprite* doubleItemEffect = CCSprite::createWithSpriteFrameName("game_effect_2x.png");
        doubleItemEffect->setScale(1.2);
        _application->_parallaxNode->addChild(doubleItemEffect,ZINDEX_PATICLE, ccp(0.0, 1.0), ccp(_sprite->getPositionX(),  (-_application->_parallaxNode->getPositionY() + (_sprite->getPositionY()))-10 ));
        
        CCCallFunc *callFunc = CCCallFuncO::create(doubleItemEffect, callfuncO_selector(CoinObject::removeDoubleMark),doubleItemEffect);
        CCSequence *seq = CCSequence::create(CCDelayTime::create(0.7), callFunc, NULL);
        doubleItemEffect->runAction(seq);
    }

	_sprite->setVisible(false);

	_checkContact = false;
	_checkRemove = true;

}

void CoinObject::removeDoubleMark(CCObject* obj)
{
    CCSprite* pSprite = (CCSprite*)obj;
    pSprite->removeFromParent();
    pSprite = NULL;
}

void CoinObject::processPosition(float frameVelocity, b2Body* body) {
	interactionObject::processPosition(frameVelocity, body);

}

void CoinObject::processPosition() {

}

void CoinObject::setSprite(CCSprite* sprite) {
	interactionObject::setSprite(sprite);



	/*CCAnimation* animation = getAnimation(_imageName);


	CCAnimate* animate = CCAnimate::create(animation);

	CCAction *action = CCRepeatForever::create(animate);

	_sprite->runAction(action);*/
}

CCAnimation* CoinObject::getAnimation(const string& imageName) {

	CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
	CCAnimation* animation = animationCache->animationByName(imageName.c_str());
	if(animation != NULL) {
		return processSpeed(animation, imageName);
	}

	string aniSprite = imageName;
	int pos = aniSprite.find(".png");
	aniSprite.replace(pos, 4,"");

	string imageName1 = _imageName;
	string imageName2 = aniSprite+"_02.png";
	string imageName3 = aniSprite+"_03.png";
	string imageName4 = aniSprite+"_04.png";
	string imageName5 = aniSprite+"_05.png";
	string imageName6 = aniSprite+"_06.png";


	CCArray *frames = CCArray::create();
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName1.c_str()));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName2.c_str()));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName3.c_str()));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName4.c_str()));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName5.c_str()));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(imageName6.c_str()));


	animation = CCAnimation::createWithSpriteFrames(frames, 0.2);
	animationCache->addAnimation(animation, imageName.c_str());
	
	return processSpeed(animation, imageName);
}

CCAnimation* CoinObject::processSpeed(CCAnimation* animation, const string& imageName) {
	if(imageName.find("Small") != string::npos) {
		animation->setDelayPerUnit(SPIN_SPEED_SMALL);
	}
	else if(imageName.find("Normal") != string::npos) {
		animation->setDelayPerUnit(SPIN_SPEED_NORMAL);
	}
	else if(imageName.find("Big") != string::npos) {
		animation->setDelayPerUnit(SPIN_SPEED_BIG);
	}
	return animation;
}
void CoinObject::shinyTick(CCObject* object) {


}