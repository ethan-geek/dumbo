
#include "HiHighGameData.h"

#include "HiHighCommon.h"
#include "../game/GamePlayScene.h"
#include "../game/Hero.h"
#include "../model/UserInfo.h"

HiHighGameData::HiHighGameData() : _combo(0), _currentStage(0), _gameTime(0), _goldAmount(0), _maxCombo(0), _miter(0), _comboDt(0),
	_useItemCount(0), _myRecordIndex(-1), _renewalndex(-1){

}
HiHighGameData::~HiHighGameData() {

}

void HiHighGameData::initData() {
	_combo = 0;
	_maxCombo = 0;
	_useItemCount = 0;
	_gameTime = 0;
	_comboDt = 0;
	_goldAmount = 0;
	
	_myRecordIndex = 0;
	_renewalndex = -1;
	initMeter();
	_fbFriendRecordList.clear();
}

void HiHighGameData::initMeter() {
	_miter = 0;
}

void HiHighGameData::increaseGold(float amount) {

	if(AGApplication::GetInstance()->_hero->isStatus(HERO_STATUS_TYPE_DOUBLE)) {
		amount *= 2;
	}

	_goldAmount += amount;
}
void HiHighGameData::decreaseGold(float amount) {
	_goldAmount -= amount;
}
void HiHighGameData::increaseCombo() {
	++_combo;
	_comboDt = 0;

	if(_combo % 50 == 0 && _combo != 0) {
		viewComboCount();
	}


	if(_maxCombo < _combo) {
		_maxCombo = _combo;
	}
}

void HiHighGameData::viewComboCount() {
	char comboTextVal[30];
	sprintf(comboTextVal, "%d COMBO!", _combo);
	CCLabelBMFont* comboText = CCLabelBMFont::create(comboTextVal, TEXT_FONT_SMALL);

	comboText->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height/ 2 - 200));
	comboText->setColor(ccc3(10, 10, 10));
	comboText->setScale(1.4);
	AGApplication::GetInstance()->_node->addChild(comboText, ZINDEX_HERO);


	CCScaleTo *scale = CCScaleTo::create(1., 2.5);
	CCFadeOut *fadeout = CCFadeOut::create(0.6);
	CCCallFunc *removeCallback = CCCallFuncO::create(AGApplication::GetInstance()->_node, callfuncO_selector(GamePlayScene::removeComboText),comboText);
	CCSpawn *spawn = CCSpawn::create(scale,fadeout, NULL);

	CCSequence *seq = CCSequence::create(spawn, removeCallback, NULL);
	comboText->runAction(seq);
}




void HiHighGameData::setCurrentStage(int currentStage) {
	_currentStage = currentStage;
}
void HiHighGameData::addGameTime(float dt) {
	_comboDt += dt;
	_gameTime += dt;

	if(_comboDt >= COMBO_TIME) {
		_comboDt = 0;
		_combo = 0;
	}


}

void HiHighGameData::increaseItemCount() {
	++_useItemCount;
}

void HiHighGameData::setMiter(float miter) {

	if(_miter >= miter) {
		return;
	}

	_miter = miter;
}
void HiHighGameData::setDirectMeter(float meter) {
	_miter = meter * PTM_RATIO;
}

float HiHighGameData::getMiter() {
	return _miter / PTM_RATIO;
}


float HiHighGameData::getGoldAmount() {
	return _goldAmount;
}
int HiHighGameData::getCombo() {
	return _combo;
}
int HiHighGameData::getMaxCombo() {
	return _maxCombo;
}
int HiHighGameData::getCurrentStage() {
	return _currentStage;
}
float HiHighGameData::getGameTime() {
	return _gameTime;
}
int HiHighGameData::getItemCount() {
	return _useItemCount;
}
void HiHighGameData::initCombo() {
	_comboDt = 0;
	_combo = 0;
}

bool CompareUserInfo(UserInfo first, UserInfo second);

void HiHighGameData::setFbFriendRecordList(vector<UserInfo>* fbFriendRecordList) {

	_fbFriendRecordList.clear();
	for(int indexI = 0 ; indexI < fbFriendRecordList->size(); ++indexI) {
		UserInfo& user = fbFriendRecordList->at(indexI);
		_fbFriendRecordList.push_back(user);
	}

	sort(_fbFriendRecordList.begin(), _fbFriendRecordList.end(), CompareUserInfo);

	UserInfo* myRecord = AGApplication::GetInstance()->getUserInfo();

	for(int indexI = _fbFriendRecordList.size() - 1 ; indexI >= 0 ; --indexI) {
		//if(_fbFriendRecordList[indexI].getName().compare(myRecord->getName()) == 0 ) {
		//esttest
		//if(_fbFriendRecordList[indexI].getName().compare("222") == 0 ) {
		if(_fbFriendRecordList[indexI].getFacebookId().compare(myRecord->getFacebookId()) == 0 ) {
			_myRecordIndex = indexI;
			if(_myRecordIndex - 1 >= 0 ) _renewalndex = _myRecordIndex - 1;
			break;
		}
	}

}

vector<UserInfo> & HiHighGameData::getFbFriendRecordList() {
    return _fbFriendRecordList;
}



UserInfo* HiHighGameData::getCurrentRecordFriend() {
	if(_renewalndex < 0 ) {
		return NULL;
	}

	return &_fbFriendRecordList[_renewalndex];
}
UserInfo* HiHighGameData::getNextRecordFriend()
{
	if(_renewalndex < 0 ) {
		return NULL;
	}
	--_renewalndex;

	return getCurrentRecordFriend();

}
int HiHighGameData::getRenewalIndex() {
	return _renewalndex;
}

bool CompareUserInfo(UserInfo first, UserInfo second )
{
	return first.getEndlessScoreInfo().getMiter() > second.getEndlessScoreInfo().getMiter();
}

bool HiHighGameData::isRenewal() {

	if(_renewalndex < 0 ) {
		return false;
	}

	CCLog("my : %d re : %d", _myRecordIndex, _renewalndex);

	if(_myRecordIndex - 1 > _renewalndex ) {
		return true;
	}


	return false;
}