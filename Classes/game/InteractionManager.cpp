#include "InteractionManager.h"
#include "../pattern/GroupPattern.h"
#include "../pattern/ResourcePattern.h"


InteractionManager::InteractionManager(void) : _currentHeight(0), _groupHeight(0),
	_resourceHeight(0), _groupIndex(0), _resourceIndex(0),
	_nextHeight(0), _firstFullCoin(true), _unlimitedStage(0),
	_currentPatternHeight(0),_pattern(NULL), _currentHeightbyCheck(0)
{

	_application = AGApplication::GetInstance();
	_userInfo = _application->getUserInfo();
	_VIEW_HEIGHT = 1200;

	XmlLoader* loader = XmlLoader::getInstance();

	char temp[30];
	int stage = 2;

	if(AGApplication::GetInstance()->getGameData()->getCurrentStage() < 0 ) {
		_unlimitedStage = AGApplication::GetInstance()->getGameData()->getCurrentStage();
	}

	if(_unlimitedStage == 0 ) {
		if(AGApplication::GetInstance()->getGameData()->getCurrentStage() < 4) {
			stage = AGApplication::GetInstance()->getGameData()->getCurrentStage();
		}

		sprintf(temp, "ep01_st%02d.xml" , stage);

		loader->loadingXMLFile(temp);
	}
	else {



	}



	_stagePattern = loader->_stagePattern;
	addObject();


	/*CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
	{
	CCArray *frames = CCArray::create();
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("FootBar_off.png"));
	frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("FootBar_on.png"));
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.1);
	animationCache->addAnimation(animation, "AnimFootBar");
	}*/
}


InteractionManager::~InteractionManager(void)
{
	removeGarbage();

}

void InteractionManager::removeGarbage() {
	GroupPattern* groupPattern = NULL;
	ResourcePattern* resourcePattern = NULL;

	if(_stagePattern != NULL) {
		for(int indexI = _groupIndex; indexI < _stagePattern->_groupList.size(); ++indexI ) {
			groupPattern = _stagePattern->_groupList[indexI];
			delete groupPattern;
		}
	}
	//�����ϱ�

	XmlLoader::getInstance()->_stagePattern = NULL;

}


void InteractionManager::addInteractionObject()
{


	if(_application->_hero->isStatus(HERO_STATUS_TYPE_FULLCOIN)) {
		if(_firstFullCoin) {
			AGApplication::GetInstance()->removeBodys();
			_currentHeight = -_application->_parallaxNode->getPositionY() * INTERACTION_OBJECT_SPEED;
			_currentHeightbyCheck = -_application->_parallaxNode->getPositionY() * INTERACTION_OBJECT_SPEED;
			_currentPatternHeight = 0;
			if(_pattern != NULL) delete _pattern;
			_pattern = NULL;
			_firstFullCoin = false;

			ResourcePattern* rp = XmlLoader::getInstance()->getFullCoinPattern();

			createRigidBody(rp->_interactionList, -_application->_winSize.height*0.9);
			delete rp;
		}
	}


	//

	//������� ������ �����ϸ� �ɰ� ����.
	if(_currentHeightbyCheck - _nextHeight - _application->_winSize.height/2 > (-_application->_parallaxNode->getPositionY() * INTERACTION_OBJECT_SPEED) || -_application->_parallaxNode->getPositionY() == 0) {
		//CCLog("%f %f", _currentHeightbyCheck- _nextHeight- _application->_winSize.height/2, -_application->_parallaxNode->getPositionY()* INTERACTION_OBJECT_SPEED);
		return;
	}

	if(_application->_hero->isStatus(HERO_STATUS_TYPE_FULLCOIN) == false) {
		addObject();
		_firstFullCoin = true;
	}
	else {
		addFullCoinObject();
	}


}
void InteractionManager::removeInteractionObject()
{
	b2Body* body;
	for(int indexI = 0 ; indexI < _removeList.size(); ++indexI) {
		body = _removeList[indexI];
		interactionObject* pObject = (interactionObject*)body->GetUserData();

		pObject->removeGameObject();
		delete pObject;
	}
	_removeList.clear();
}
void InteractionManager::processPosition(float frameVelocity, b2Body* body)
{
	interactionObject* object = (interactionObject*)body->GetUserData();

	if(object->processMagnet()) {
		return;
	}

	if(_application->_parallaxNode->getPositionY() != 0) {
		object->processPosition(frameVelocity, body);
	}

	object->processPosition();

}
void InteractionManager::processContact(b2Body* body)
{
	interactionObject* object = (interactionObject*)body->GetUserData();

	object->processContact();
}

b2BodyType InteractionManager::getType() {
	return b2_kinematicBody;
}


void InteractionManager::addUnLimitedObject() {

	_nextHeight = 0;

	do {
		if(_pattern == NULL) {
			_pattern = XmlLoader::getInstance()->getUnlimitedPattern();
			//newPattern = true;
		}

		//1136 ��ŭ�� ��
		createRigidBody(_pattern->_interactionList);
		_currentPatternHeight += _VIEW_HEIGHT;
		//1136 ���� Ŭ���� 1136���� +=
		if(_VIEW_HEIGHT > _pattern->_height) {
			_currentHeightbyCheck += _pattern->_height;	
			_nextHeight += _pattern->_height;
		}
		else {

			if(_currentPatternHeight > _pattern->_height) {
				_currentHeightbyCheck += (_pattern->_height - (_currentPatternHeight - _VIEW_HEIGHT) );	
				_nextHeight += (_pattern->_height - (_currentPatternHeight - _VIEW_HEIGHT));	
			}
			else {
				_currentHeightbyCheck += _VIEW_HEIGHT;	
				_nextHeight += _VIEW_HEIGHT;
			}

		}

		//���������� ������ ����
		if(_currentPatternHeight > _pattern->_height) {
			_currentHeight += _pattern->_height;	
			delete _pattern;
			_pattern = NULL;
			_currentPatternHeight = 0;
		}


	} while(AGApplication::GetInstance()->_winSize.height > _nextHeight);

}

void InteractionManager::addObject() {

	if(_unlimitedStage != 0 ) {
		addUnLimitedObject();
		return;
	}


	if(_groupHeight <= _resourceHeight && (_currentHeight != 0) ) {
		++_groupIndex;
		_resourceHeight = 0;
		_resourceIndex = 0;
	}

	if( _stagePattern->_groupList.size() <= _groupIndex) {
		return;
	}

	GroupPattern* groupPattern = _stagePattern->_groupList[_groupIndex];
	ResourcePattern* resourcePatter = groupPattern->_resourceList[_resourceIndex];

	createRigidBody(resourcePatter->_interactionList);


	_groupHeight = groupPattern->_height;
	_resourceHeight += resourcePatter->_height;
	++_resourceIndex;

	_currentHeight += resourcePatter->_height;
	_nextHeight = resourcePatter->_height;
}

void InteractionManager::checkRemoveList(b2Body* body)
{
	interactionObject* pObject = (interactionObject*)body->GetUserData();
	CCSprite* pSprite = pObject->getSprite();

	if(pObject->getCheckHave()) {
		return;
	}

	if(pObject->getCheckRemove()) {
		_removeList.push_back(body);
		return;
	}

	if (pSprite->getTag() == SPRITE_TYPE_OBJECT)
	{
		if(0 > body->GetPosition().y + (_application->_winSize.height * 0.4 / PTM_RATIO) ) {
			_removeList.push_back(body);
		}


	}


}

void InteractionManager::createRigidBody(vector<interactionObject*>& pattern, float height) {

	CCSprite* pSprite;

	vector<int> deleteIndex;
	CCLog("createRigidBody in");
	for (int i = 0; i < pattern.size(); i++)
	{
		interactionObject* object = pattern[i];

		if((_currentPatternHeight <= object->getPosition().y && object->getPosition().y < (_currentPatternHeight + _VIEW_HEIGHT)) || AGApplication::GetInstance()->_hero->isStatus(HERO_STATUS_TYPE_FULLCOIN) ) {
			pattern[i] = NULL;
			deleteIndex.push_back(i);

			pSprite = CCSprite::createWithSpriteFrameName(object->getImageName().c_str());
			pSprite->setTag(SPRITE_TYPE_OBJECT);
			object->setSprite(pSprite);

			b2BodyDef objectBodyDef;
			objectBodyDef.type = getType();
			objectBodyDef.position.Set(object->getPosition().x/PTM_RATIO, 
				(object->getPosition().y +  _currentHeight+ (_application->_parallaxNode->getPositionY() * INTERACTION_OBJECT_SPEED) + height + _application->_winSize.height/2)/PTM_RATIO);

			objectBodyDef.userData = object;


			b2Body* objectBody = _application->_world->CreateBody(&objectBodyDef);
			object->setBody(objectBody);

			b2PolygonShape objectShape;
			objectShape.SetAsBox(pSprite->getContentSize().width/3/PTM_RATIO,pSprite->getContentSize().height/3/PTM_RATIO);

			b2FixtureDef objectShapeDef;
			objectShapeDef.shape = &objectShape;
			objectShapeDef.density = 0.2f;
			objectShapeDef.friction = 0;
			objectShapeDef.restitution = 0.2f;
			objectShapeDef.isSensor = true;

			objectBody->CreateFixture(&objectShapeDef);

			_application->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE)->addChild(pSprite, ZINDEX_ITEM_OBJECT);
			object->initRigid();

		}
	}

	for(int indexJ = 0 ; indexJ < deleteIndex.size() ; ++indexJ) {
		int index = (deleteIndex[indexJ]-indexJ);

		pattern.erase(pattern.begin() + index);
	}


	CCLog("createRigidBody out");
}

void InteractionManager::addFullCoinObject() {

	ResourcePattern* rp = XmlLoader::getInstance()->getFullCoinPattern();

	createRigidBody(rp->_interactionList);


	_currentHeight += rp->_height;
	_currentHeightbyCheck += rp->_height;
	_nextHeight = rp->_height;

	delete rp;
}

void InteractionManager::process(float frameVelocity, b2Body* body) {

	processPosition(frameVelocity, body);
	processContact(body);
	checkRemoveList(body);

}


void InteractionManager::changeHeight() {
	AGApplication::GetInstance()->removeBodys(CCDirector::sharedDirector()->getWinSize().height/PTM_RATIO);
	_currentHeight = (-_application->_parallaxNode->getPositionY() + CCDirector::sharedDirector()->getWinSize().height*0.3) * INTERACTION_OBJECT_SPEED;
	_currentHeightbyCheck = (-_application->_parallaxNode->getPositionY() + CCDirector::sharedDirector()->getWinSize().height/3) * INTERACTION_OBJECT_SPEED;
	_currentPatternHeight = 0;
}
