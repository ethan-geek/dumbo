///////////////////////////////////////////////////////////
//  Hero.cpp
//  Implementation of the Class Hero
//  Created on:      19-3-2014 오전 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "Hero.h"
#include "GamePlaySceneParts.h"



Hero::Hero() {

	_application = AGApplication::GetInstance();
	_winSize = CCDirector::sharedDirector()->getWinSize();
	_heroStatus = new HeroStatus();
	_heroAnimation = new HeroAnimation();
	_heroPosition = new HeroPosition();
	_haveItemList.clear();
    

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("character/character.plist");

	_heroWrapperSprite = CCSprite::create();
	_heroWrapperSprite->setTag(SPRITE_TYPE_HERO);

	_heroSprite = CCSprite::createWithSpriteFrameName("air_idle0001.png");
	_heroSprite->setTag(SPRITE_TYPE_HERO);

	_heroWrapperSprite->addChild(_heroSprite, ZINDEX_HERO);

	createRigidBody();

	setStatusType(HERO_STATUS_TYPE_DEFAULT);
	setItem(new StartItemObject());

	initItemRelation();
    
    _isFirstTimeGettingItem = CCUserDefault::sharedUserDefault()->getBoolForKey(IS_FIRST_TIME_GETTING_ITEM, true);
    
    invisible = false;

}



Hero::~Hero(){
	delete _heroStatus;
	delete _heroAnimation;
	delete _heroPosition;
}

void Hero::initItemRelation() {


	//vector<HERO_STATUS_TYPE> startJumpRelation;
	//startJumpRelation.push_back(HERO_STATUS_TYPE_STARTJUMP);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_STARTJUMP] = startJumpRelation;

	//vector<HERO_STATUS_TYPE> parachuteRelation;
	//parachuteRelation.push_back(HERO_STATUS_TYPE_WEIGHT);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_WEIGHT] = parachuteRelation;

	//vector<HERO_STATUS_TYPE> shieldRelation;
	//shieldRelation.push_back(HERO_STATUS_TYPE_SHIELD);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_SHIELD] = shieldRelation;

	//vector<HERO_STATUS_TYPE> superRelation;
	////superRelation.push_back(HERO_STATUS_TYPE_STARFISH);
	//superRelation.push_back(HERO_STATUS_TYPE_SUPERITEM);
	////superRelation.push_back(HERO_STATUS_TYPE_STARTJUMP);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_SUPERITEM] = superRelation;


	//vector<HERO_STATUS_TYPE> magnetRelation;
	//magnetRelation.push_back(HERO_STATUS_TYPE_MAGNET);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_MAGNET] = magnetRelation;

	//vector<HERO_STATUS_TYPE> doubleRelation;
	//doubleRelation.push_back(HERO_STATUS_TYPE_DOUBLE);
	//_itemRelationMap[INTERACTION_OBJECT_TYPE_DOUBLE] = doubleRelation;

}

void Hero::createRigidBody() {



	b2BodyDef actorBodyDef;
	actorBodyDef.type = b2_dynamicBody;
	//actorBodyDef.position.Set(_winSize.width/2/PTM_RATIO,_heroSprite->getContentSize().height/3/PTM_RATIO);
    actorBodyDef.position.Set(_winSize.width/2/PTM_RATIO, 205/PTM_RATIO);

	actorBodyDef.userData = _heroWrapperSprite;


	_heroBody = _application->_world->CreateBody(&actorBodyDef);

	b2PolygonShape actorShape;
	actorShape.SetAsBox(_heroSprite->getContentSize().width/3/PTM_RATIO, _heroSprite->getContentSize().height/3/PTM_RATIO);
	/*b2CircleShape actorShape;
	actorShape.m_radius = _heroSprite->getContentSize().width/2/PTM_RATIO;*/


	b2FixtureDef actorShapeDef;
	actorShapeDef.shape = &actorShape;
	//밀도
	actorShapeDef.density = 1;
	//마찰
	actorShapeDef.friction = 0.2;
	//손해배상
	actorShapeDef.restitution = 0.2f;

	_heroBody -> CreateFixture(&actorShapeDef);
}



void Hero::contactReAction(){



}

void Hero::process(float frameVelocity, float dt) {
	processGravity();
	processPosition(frameVelocity, _application->getHeroVelocity(), dt);
	processTransformation();
}


void Hero::processPosition(float vellocity, float heroVellocity, float dt)
{
	if(_heroStatus->checkKeepTime(dt)) {
		_heroAnimation->processAnimation(HERO_STATUS_TYPE_DEFAULT,_heroStatus, _heroSprite);
	}
	
	_heroPosition->processPosition(vellocity, heroVellocity, _heroBody, _heroStatus);
}

void Hero::setStatusType(HERO_STATUS_TYPE status)
{
	interactionObject* object = NULL;
	if(_haveItemList.size() > 0 ) {
		object = _haveItemList[0];
	}
	HERO_STATUS_TYPE before = _heroStatus->getDefaultStatus()._statusType;
	_heroStatus->setStatusType(status, object);
	_heroAnimation->processAnimation(before, _heroStatus, _heroSprite);
}



void Hero::useItem(){
	if(_haveItemList.size() == 0) {

		return;
	}

	if(checkItemRelation(_haveItemList[0]->getInteractionObjectType())) {
		return;
	}
	AGApplication::GetInstance()->getGameData()->increaseItemCount();
    
	_haveItemList[0]->useItem();

	_haveItemList[0]->setCheckHave(false);

	if(_haveItemList[0]->getImageName() == "") {
		delete _haveItemList[0];
	}

	_haveItemList.erase(_haveItemList.begin());

	CCSprite* itemFrame = (CCSprite*)_application->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS)->getChildByTag(PLACE_TYPE_ITEMFRAME_1);
	itemFrame->removeAllChildren();

	if(_haveItemList.size() > 0) {
         
		CCSprite* itemFrame2 = (CCSprite*)_application->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS)->getChildByTag(PLACE_TYPE_ITEMFRAME_2);
		itemFrame2->removeAllChildren();

		string haveSpriteStr = _haveItemList[0]->getImageName();
		//AGUtil::replaceStr(haveSpriteStr, ".png", "_box.png");

		CCSprite* haveSprite = CCSprite::createWithSpriteFrameName(haveSpriteStr.c_str());
		itemFrame->addChild(haveSprite);
		haveSprite->setPosition(ccp(itemFrame->getContentSize().width/2, itemFrame->getContentSize().height/2));

	}
    
}




void Hero::processTilt(CCAcceleration* acceleration) 
{

	if(acceleration == NULL) {
		return;
	}

	if(acceleration->x < 0 && acceleration->x < -MAX_TILT) {
		acceleration->x = -MAX_TILT;
	}
	else if(acceleration->x > 0 && acceleration->x > MAX_TILT) {
		acceleration->x = MAX_TILT;
	}
    
	_heroPosition->processTilt(acceleration, _heroBody);
	
	
	//CCLog("tilt --------------- %f", acceleration->x);
    float standardAccValue = 0;
	if(_application->getIsScroll()) {
        standardAccValue = 0.35;
		if(_heroStatus->isStatus(HERO_STATUS_TYPE_FALL) || _heroStatus->isStatus(HERO_STATUS_TYPE_DROP) 
			|| _heroStatus->isStatus(HERO_STATUS_TYPE_DIE)) {
				return;
		}
    }else {
        standardAccValue = 0.3;
    }



	HERO_TILT_TYPE tempType;
	if(0 <= acceleration->x  && acceleration->x < standardAccValue && _heroStatus->isStatus(HERO_STATUS_TYPE_DEFAULT) == false) {
		//_heroStatus->setTiltType(HERO_TILT_TYPE_CENTER);
		tempType = HERO_TILT_TYPE_CENTER;
	}
	else if(0 >= acceleration->x  && acceleration->x > -standardAccValue  && _heroStatus->isStatus(HERO_STATUS_TYPE_DEFAULT) == false) {

		tempType = HERO_TILT_TYPE_CENTER;
	}
	else if(acceleration->x <= 0 ) {

		tempType = HERO_TILT_TYPE_LEFT;
	}
	else {

		tempType = HERO_TILT_TYPE_RIGHT;
	}

	if(_heroStatus->isTilt(tempType)) {
		return;
	}



	_heroStatus->setTiltType(tempType);
	_heroAnimation->processAnimation(_heroStatus->getDefaultStatus()._statusType,_heroStatus, _heroSprite);



}


void Hero::setItem(interactionObject* object) {


	if(_haveItemList.size() >= 2) {
		return;
	}
    
	int index = _haveItemList.size();
	if(object->getItemHaveType() == ITEM_HAVE_TYPE_YES) {
		CCSprite* itemFrame = NULL;
		if(_haveItemList.size() == 0) {
			itemFrame = (CCSprite*)_application->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS)->getChildByTag(PLACE_TYPE_ITEMFRAME_1);
		}
		else if(_haveItemList.size() == 1) {
			itemFrame = (CCSprite*)_application->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS)->getChildByTag(PLACE_TYPE_ITEMFRAME_2);
		}

		_haveItemList.push_back(object);

		_haveItemList[index]->setCheckHave(true);

		if(_haveItemList[index]->getImageName() == "") {
			return;
		}

		string haveSpriteStr = _haveItemList[index]->getImageName();
		//AGUtil::replaceStr(haveSpriteStr, ".png", "_box.png");
		/*int pos = haveSpriteStr.find(".png");
		haveSpriteStr = haveSpriteStr.replace(pos, 4,"_box.png");*/

		CCSprite* haveSprite = CCSprite::createWithSpriteFrameName(haveSpriteStr.c_str());

		itemFrame->addChild(haveSprite);
		haveSprite->setPosition(ccp(itemFrame->getContentSize().width/2, itemFrame->getContentSize().height/2));
		//_haveSprite->setPosition(ccp(_heroSprite->getPositionX(), _heroSprite->getPositionY()- _heroSprite->getContentSize().height));
	}
    
    
    if(_isFirstTimeGettingItem) {
        if(_application->getGameData()->getItemCount() ==1) {
            GamePlaySceneParts * gpsp = (GamePlaySceneParts*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS);
            gpsp->showTutorial();
        }
    }

}


bool Hero::isStatus(HERO_STATUS_TYPE type) {

	return _heroStatus->isStatus(type);

}


bool Hero::isStatusRelativeVelocity() {
	return _heroStatus->isStatusRelativeVelocity();
}

bool Hero::isStatusUNDecreaseRelativeVelocity() {
	return _heroStatus->isStatusUNDecreaseRelativeVelocity();
}

bool Hero::checkItemType(HERO_STATUS_TYPE& type) {
	return _heroStatus->checkItemType(type);
}



void Hero::processGravity() {
	if(this->isStatusRelativeVelocity() == false) {
		float tempVelocity = 0;
		if(_application->getHeroVelocity() > 0 ) {
			_application->_world->SetGravity(b2Vec2(0, -10.0f));
		}
		else {
			if(_heroStatus->isStatus(HERO_STATUS_TYPE_WEIGHT) == false) {
				_application->_world->SetGravity(b2Vec2(0, -10.0f));
			}else {
				_application->_world->SetGravity(b2Vec2(0, -2.0f));
			}
		}

	}
}

void Hero::processTransformation() { 

	if(this->isStatus(HERO_STATUS_TYPE_WEIGHT)) {

		CCNode* para =_heroWrapperSprite->getChildByTag(INTERACTION_OBJECT_TYPE_WEIGHT);
		if(para == NULL) {
			return;
		}

		if(_application->getHeroVelocity() <= 0 ) {

			if(para->isVisible() == false) {
				para->setVisible(true);
				HiHighAudio::sharedAudio()->playEffect("weight");
			}
		}
		else {
			if(para->isVisible()) {
				para->setVisible(false);
			}
		}

	}

}


bool Hero::checkItemRelation(const INTERACTION_OBJECT_TYPE& type) {

	if(_itemRelationMap.find(type) == _itemRelationMap.end()) {
		return false;
	}

	vector<HERO_STATUS_TYPE>& ioRelationList = _itemRelationMap[type];

	for(int indexI= 0 ; indexI < ioRelationList.size(); ++indexI) {
		if(isStatus(ioRelationList[indexI]) ){
			return true;
		}
	}

	return false;
}

interactionObject* Hero::getFirstItem()
{
    return _haveItemList[0];
}