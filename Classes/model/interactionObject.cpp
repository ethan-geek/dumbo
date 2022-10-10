///////////////////////////////////////////////////////////
//  interactionObject.cpp
//  Implementation of the Class interactionObject
//  Created on:      19-3-2014 ���� 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "interactionObject.h"
#include "../game/Hero.h"
#include "../model/UserInfo.h"

interactionObject::interactionObject() : _checkContact(false), _checkRemove(false), _itemHaveType(ITEM_HAVE_TYPE_NO), _checkHave(false), _imageName(""), _body(NULL){
	_application = AGApplication::GetInstance();
}



interactionObject::~interactionObject(){

}





void interactionObject::addInteractionObject(){

}


void interactionObject::processAnimation(){

}


void interactionObject::processContact(){

}

void interactionObject::processPosition() {

}

void interactionObject::processPosition(float frameVelocity, b2Body* body){

	CCPoint vec = ccpAdd(ccp(body->GetPosition().x, body->GetPosition().y), ccp(0, -frameVelocity*INTERACTION_OBJECT_SPEED/PTM_RATIO));
	body->SetTransform(b2Vec2(vec.x, vec.y), body->GetAngle());

}


void interactionObject::removeGameObject(){

	_sprite->removeAllChildren();
	_sprite->removeFromParentAndCleanup(true);
	_body->SetUserData(NULL);

	_application->_world->DestroyBody(_body);

}

void interactionObject::useItem() {
	CCParticleSystem *particle = CCParticleSystemQuad::create("paticle/use_item.plist");
	particle->setAutoRemoveOnFinish(true);
	particle->setScale(2);
	Hero *hero = AGApplication::GetInstance()->_hero;
	particle->setPosition(ccp(hero->_heroSprite->getContentSize().width / 2, hero->_heroSprite->getContentSize().height / 2 - 80));

	hero->_heroSprite->addChild(particle);
    
    //effect
    useItemEffect();
}

void interactionObject::useItemEffect()
{
    CCSprite* spr = NULL;
    if (getInteractionObjectType() != INTERACTION_OBJECT_TYPE_STARTJUMP) {
        spr = CCSprite::createWithSpriteFrameName(getImageName().c_str());
    }else {
        UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
        UserUpgradeInfo* userUpgradeInfo = userInfo->getUserUpgradeInfo(STR_START_ITEM_NAME);
        
        if (userUpgradeInfo != NULL && userUpgradeInfo->getUpgradeCount() > 0) {
            spr = CCSprite::createWithSpriteFrameName("game_item_rocket.png");
        }
    }
    if(spr) {
        spr->setOpacity(255*0.2);
        CCLayer * coreLayer = (CCLayer*)_application->_node;
        //spr->setScale(2);
        spr->setPosition(ccp(coreLayer->getContentSize().width/2, coreLayer->getContentSize().height/2));
        coreLayer->addChild(spr, ZINDEX_HERO);
        
        CCScaleTo *scaleTo = CCScaleTo::create(1.0, 6);
        CCFadeOut *fadeOut = CCFadeOut::create(1.0);
        CCSpawn *spawn = CCSpawn::create(scaleTo, fadeOut, NULL);
        CCSequence *seq = CCSequence::create(spawn, CCCallFuncO::create(spr, callfuncO_selector(interactionObject::useItemEffectCallback), spr), NULL);
        spr->runAction(seq);
    }
}

void interactionObject::useItemEffectCallback(cocos2d::CCObject *obj)
{
    CCSprite *spr = (CCSprite*)obj;
    spr->removeFromParentAndCleanup(true);
}

bool interactionObject::processMagnet() {

	// hero 마그셋 상태 검사
	if(_application->_hero->isStatus(HERO_STATUS_TYPE_MAGNET) == false){
		return false;
	}
	//  마그넷 적용 코인들 검사
	if(isAbleMagnet() == false) {
		return false;
	}

	// 거리 체크
	b2Vec2 center = _application->_hero->_heroBody->GetPosition();

	b2Vec2 position = _body->GetPosition();

	b2Vec2 d = center - position;

	if(d.Length() > _application->_hero->_heroSprite->getContentSize().width/PTM_RATIO/2 * MAGNET_RATIO) {
		return false;
	}

	d.Normalize();
	_body->SetLinearVelocity(50.0f *d);

	return true;

}


bool interactionObject::isAbleMagnet() {

	if(_objectType == INTERACTION_OBJECT_TYPE_COIN
		||_objectType == INTERACTION_OBJECT_TYPE_STARFISH
			/*||_objectType == INTERACTION_OBJECT_TYPE_FULLCOIN
			||_objectType == INTERACTION_OBJECT_TYPE_MAGNET
			||_objectType == INTERACTION_OBJECT_TYPE_SHIELD
			||_objectType == INTERACTION_OBJECT_TYPE_SUPERITEM
			||_objectType == INTERACTION_OBJECT_TYPE_WEIGHT*/
			) {
		return true;
	}


	return false;
}




void interactionObject::setImageName(string imageName) {

	if(_objectType == INTERACTION_OBJECT_TYPE_FAKE_FOOTBAR) {
		imageName += "_on";
	}

	if(_objectType == INTERACTION_OBJECT_TYPE_FOOTBAR) {
		int count = AGApplication::GetInstance()->getRand() % 3 + 1;
		char temp[4];
		sprintf(temp, "_%02d", count);
		
		imageName += temp;
	}


	if(_objectType == INTERACTION_OBJECT_TYPE_COIN) {
		imageName += "_light";
	}
		


	_imageName = imageName+".png";
	_imageName = AGUtil::reSizeImage(_imageName.c_str());
}
void interactionObject::setObjectType(INTERACTION_OBJECT_TYPE type) {
	_objectType = type;
}
void interactionObject::setItemHaveType(ITEM_HAVE_TYPE type) {
	_itemHaveType = type;
}
void interactionObject::setPosition(CCPoint& point) {

	//	point.x = point.x;
	//	point.y = point.y;

	_position = point;
}
void interactionObject::setSpeed(float speed) {
	_speed = speed;
}

string interactionObject::getImageName() {
	return _imageName;
}
INTERACTION_OBJECT_TYPE interactionObject::getInteractionObjectType() {
	return _objectType;
}
ITEM_HAVE_TYPE interactionObject::getItemHaveType() {
	return _itemHaveType;
}
CCPoint interactionObject::getPosition() {
	return _position;
}
float interactionObject::getSpeed() {
	return _speed;
}


CCSprite* interactionObject::getSprite() {
	return _sprite;
}
void interactionObject::setSprite(CCSprite* sprite) {
	_sprite = sprite;
}

bool interactionObject::getCheckContact()
{
	return _checkContact;
}
void interactionObject::setCheckContact(bool isContact)
{
	_checkContact = isContact;
}


void interactionObject::setBody(b2Body* body) {
	_body = body;
}

bool interactionObject::getCheckRemove() {
	return _checkRemove;
}

bool interactionObject::getCheckHave() {
	return _checkHave;
}
void interactionObject::setCheckHave(bool isHave) {
	_checkHave = isHave;
}
void interactionObject::setCheckRemove(bool isRemove) {
	_checkRemove = isRemove;
}
