///////////////////////////////////////////////////////////
//  UserInfo.cpp
//  Implementation of the Class UserInfo
//  Created on:      19-3-2014 ���� 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "UserInfo.h"


UserInfo::UserInfo() : _currentStage(1), _facebookId(""), _gold(0), _totalGold(0), _lastVisitDate(0), _guestId(""), _id(0){

}



UserInfo::~UserInfo(){

}


void UserInfo::setCurrentStage(int currentState) {
	_currentStage = currentState;
}
void UserInfo::setFacebookId(string id) {
	_facebookId = id;
}
void UserInfo::setGold(int gold){
	_gold = gold;
}
void UserInfo::setHeartInfo(HeartInfo* heartInfo){
	_heartInfo = *heartInfo;
}
void UserInfo::setStageScoreInfo(StageScoreInfo& stageScoreInfo) { 

	//endless
	if(_stageScoreInfoList.size() > 0 ) {
		_stageScoreInfoList[0] = stageScoreInfo;
	}

	else {
		_stageScoreInfoList.push_back(stageScoreInfo);
	}


}
void UserInfo::setTotalGold(int totalGold) {
	_totalGold = totalGold;
}
void UserInfo::setUserUpgradeInfo(UserUpgradeInfo& userUpgradeInfo) {

	_userUpgradeInfoMap[userUpgradeInfo.getItemInfo()->getName()] = userUpgradeInfo;

}

int UserInfo::getCurrentStage() {
	return _currentStage;
}
string UserInfo::getFacebookId() { 
	return _facebookId;
}
int UserInfo::getGold() {
	return _gold;
}
HeartInfo* UserInfo::getHeartInfo() {
	return &_heartInfo;
}

StageScoreInfo* UserInfo::getStageScoreInfo(int stage) {

	if(_stageScoreInfoList.size() < stage) {
		return NULL;
	}


	return &_stageScoreInfoList[stage-1];
}
int UserInfo::getTotalGold() {
	return _totalGold;
}
UserUpgradeInfo* UserInfo::getUserUpgradeInfo(string name) {

	if( _userUpgradeInfoMap.count(name) == 0 ){
		return NULL;
	}

	return &_userUpgradeInfoMap[name];
}

vector<StageScoreInfo>& UserInfo::getStageScoreInfoList() {
	return _stageScoreInfoList;
}
map<string, UserUpgradeInfo>& UserInfo::getUserUpgradeInfoMap() {
	return _userUpgradeInfoMap;
}

StageScoreInfo& UserInfo::getEndlessScoreInfo() {
	return _endlessScoreInfo;
}

void UserInfo::setEndlessScoreInfo(StageScoreInfo& endlessScoreInfo) {
	_endlessScoreInfo = endlessScoreInfo;
}
void UserInfo::setLastVisitDate(float date) {
	_lastVisitDate = date;
}
float UserInfo::getLastVisitDate() {
	return _lastVisitDate;
}

string UserInfo::getProfileUrl() {
	return _profileUrl;
}
string UserInfo::getName() {
	return _name;
}
void UserInfo::setName(string name) {
	_name = name;
}
void UserInfo::setProfileUrl(string profileUrl) {
	_profileUrl = profileUrl;
}
void UserInfo::setGuestId(string guestId) {
	_guestId = guestId;
}
string UserInfo::getGuestId() {
	return _guestId;
}
void UserInfo::setId(long id) {
	_id = id;
}
long UserInfo::getId() {
	return _id;
}
