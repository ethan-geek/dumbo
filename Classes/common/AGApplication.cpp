

#include "HiHighCommon.h"
#include "../game/Hero.h"
#include "../dao/HiHighDaoSharedUserDefault.h"
#include "HiHighConnector.h"
#include "./AGApplication.h"

#define MAX_RAND_COUNT		5000

AGApplication* AGApplication::g_Application = NULL;


AGApplication::AGApplication() : _hihighDao(NULL),_parallaxNode(NULL), _comboDt(0), _isStop(false), _node(NULL){

	initData();
    _currentGameState = OTHERSCENE;
	_winSize = CCDirector::sharedDirector()->getWinSize();
}

AGApplication::~AGApplication() {

	delete _userInfo;
	delete _hihighDao;
}

void AGApplication::initData() {
	//	_goldAmount = 0;
	_heroVellocity =0;
	_gravity = 0;
	_isScroll = false;
	//	_combo = 0;
	//	_maxCombo =0 ;
	_weightMultiple = 1;
	_comboDt = 0;
	//	_gameData.initData();

}

void AGApplication::initGame() {

	initData();
	
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	_world = new b2World(gravity);

	_winSize = CCDirector::sharedDirector()->getWinSize();
	_parallaxNode = CCParallaxNode::create();
	_parallaxNode->retain();
}

void AGApplication::initRand() {

	 srand( time( NULL));
	_randIndex = -1;
	_randList.clear();

	for(int indexI = 0; indexI < MAX_RAND_COUNT; ++indexI) {
		_randList.push_back(rand());
	}
	
}

int AGApplication::getRand() {
	
	++_randIndex;

	if(_randIndex >= MAX_RAND_COUNT) {
		_randIndex = 0;
	}
	return _randList[_randIndex];
}

void AGApplication::destoryGame() {
	_parallaxNode->release();
	if(_world != NULL) {
		delete _world;
		_world = NULL;
	}

	_node = NULL;
	_parallaxNode = NULL;
}



//
AGApplication* AGApplication::GetInstance() {
	if (g_Application == NULL)
	{
		g_Application = new AGApplication();

	}

	return g_Application;
};

//void AGApplication::setGoldAmount(float amount)
//{
//	_goldAmount = amount;
//}
void AGApplication::setHeroVelocity(float velocity)
{
	/*if(velocity < 0) {
	initCombo();
	}*/

	_heroVellocity = velocity;
}
void AGApplication::setGravity(float g)
{
	if(g > 20) {
		return;
	}
	_gravity = g;
}
void AGApplication::setIsScroll(bool type)
{
	_isScroll = type;
}


bool AGApplication::setSpeed(HERO_STATUS_TYPE type)
{

	//	increaseCombo();
	_gameData.increaseCombo();

	if(_hero->isStatusUNDecreaseRelativeVelocity() && AGUtil::getSpeed(type) < 0 ) {
		return false;
	}

	if(_hero->isStatusRelativeVelocity() && _hero->checkItemType(type) == false) {
		return false;
	}

	if(_hero->isStatus(HERO_STATUS_TYPE_STARFISH) && _hero->checkItemType(type) == false
		&& getHeroVelocity() > AGUtil::getSpeed(type)) {
			return false;
	}



	this->_heroVellocity = AGUtil::getSpeed(type);
	_hero->_heroBody->SetLinearVelocity(b2Vec2(0,AGUtil::getSpeed(type)));
	this->_gravity = 0;


	if(type == HERO_STATUS_TYPE_FOOTBAR) {
		type = HERO_STATUS_TYPE_JUMP;
	}

	if(_hero->isStatus(HERO_STATUS_TYPE_NOREACTION) && type == HERO_STATUS_TYPE_JUMP) {

	}else {
		_hero->setStatusType(type);
	}

	return true;
}


float AGApplication::getHeroVelocity()
{
	return _hero->_heroBody->GetLinearVelocity().y;
}
float AGApplication::getGravity()
{
	return _gravity;
}
bool AGApplication::getIsScroll()
{
	return _isScroll;
}

//void AGApplication::increaseGold(float amount)
//{
//	this->_goldAmount += amount;
//}
//void AGApplication::decreaseGold(float amount)
//{
//	this->_goldAmount -= amount;
//}

//void AGApplication::increaseCombo() {
//
//	++_combo;
//	_comboDt = 0;
//
//	if(_combo % 10 == 0 && _combo != 0) {
//		char comboTextVal[30];
//		sprintf(comboTextVal, "%d combo!", _combo);
//		CCLabelBMFont* comboText = CCLabelBMFont::create(comboTextVal, TEXT_FONT);
//
//		comboText->setPosition(ccp(_winSize.width / 2, _winSize.height/ 2 - 200));
//        comboText->setColor(ccc3(255, 255, 0));
//        comboText->setScale(1.4);
//		_node->addChild(comboText, ZINDEX_HERO);
//
//
//        CCScaleTo *scale = CCScaleTo::create(1., 2.5);
//		CCFadeOut *fadeout = CCFadeOut::create(1.0);
//		CCCallFunc *removeCallback = CCCallFuncO::create(comboText, callfuncO_selector(AGApplication::removeComboText),comboText);
//        CCSpawn *spawn = CCSpawn::create(scale,fadeout, NULL);
//
//		CCSequence *seq = CCSequence::create(spawn, removeCallback, NULL);
//		comboText->runAction(seq);
//	}
//
//
//	if(_maxCombo < _combo) {
//		_maxCombo = _combo;
//	}
//}



//void AGApplication::initCombo() {
//	_combo = 0;
//}



void AGApplication::setStagePattern(StagePattern *pattern)
{
	this->_stagePattern = pattern;
}
StagePattern* AGApplication::getStagePattern()
{
	return this->_stagePattern;
}

void AGApplication::setObjectMap(string key, CCObject* obj)
{
	_objectMap[key] = obj;
}

CCObject* AGApplication::getObjectMap(string key)
{
	return _objectMap[key];
}

UserInfo* AGApplication::getUserInfo()
{
	return this->_userInfo;
}
void AGApplication::setUserInfo(UserInfo* userInfo)
{
	this->_userInfo = userInfo;
}

HiHighDao* AGApplication::getHiHighDao() {

	if(_hihighDao == NULL) {
		_hihighDao = new HiHighDaoSharedUserDefault();
	}

	return _hihighDao;
}


void AGApplication::removeBodys(float height) {
	for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {

		if(height != 0 && b->GetPosition().y < height) {
			continue;
		}

		if(b == _hero->_heroBody) {

		}
		else {
			((interactionObject*)b->GetUserData())->setCheckRemove(true);
			//remove check!
		}


	}
}

//int AGApplication::getCombo() {
//	return _combo;
//}
//
//int AGApplication::getMaxCombo() {
//	return _maxCombo;
//}
//float AGApplication::getGoldAmount()
//{
//	return _goldAmount;
//}
//
//void AGApplication::setCurrentStage(int stage) {
//	_currentStage = stage;
//}
//
//
//int AGApplication::getCurrentStage() {
//
//	return _currentStage;
//}
//
//void AGApplication::setGameTime(float time) {
//	_gameTime = time;
//}
//
//float AGApplication::getGameTime() {
//	return _gameTime;
//}

void AGApplication::setWeightMultiple(float weightMultiple) {
	_weightMultiple = weightMultiple;
	if(weightMultiple < 1 ){
		if(_gravity > 4 ) {
			_gravity = 2 ;
		}

	}
}
float AGApplication::getWeightMultiple() {
	return _weightMultiple;
}

bool AGApplication::checkFacebook() {
	return CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT);
}

void AGApplication::changedFacebookUser() {

	//userDefault
	delete _userInfo;
	CCUserDefault::sharedUserDefault()->setStringForKey(XML_STORAGE, "");
	/*string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	filePath += "sv.dt";
	remove(filePath.c_str());*/

	AGApplication::GetInstance()->getHiHighDao()->init();
	//facebookFriends
	HiHighConnector::sharedConnector()->initFbFriends();

}


void AGApplication::setDt(float dt) {
	_comboDt += dt;

	if(_comboDt >= COMBO_TIME) {
		_comboDt = 0;
		//		initCombo();
	}

}

HiHighGameData* AGApplication::getGameData() {
	return &_gameData;
}
bool AGApplication::IsStop()  {
	return _isStop;
}
void AGApplication::setStop(bool stop) {
	_isStop = stop;
}


void AGApplication::setInteractionManager(InteractionManager* mgr){ 

	_interactionManager = mgr;
}
InteractionManager* AGApplication::getInteractionManager() {
	return _interactionManager;
}
