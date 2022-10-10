///////////////////////////////////////////////////////////
//  StageScoreInfo.cpp
//  Implementation of the Class StageScoreInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "StageScoreInfo.h"


StageScoreInfo::StageScoreInfo() : _stage(-1), _maxCombo(0) , _miter(0), _useItemCount(0), _maxScore(0), _rank(0){

}



StageScoreInfo::~StageScoreInfo(){

}


void StageScoreInfo::setStage(int stage) {
	_stage = stage;
}
void StageScoreInfo::setMaxCombo(int maxCombo) {
	_maxCombo = maxCombo;
}


void StageScoreInfo::setMaxScore(int score) {
	_maxScore = score;
}

int StageScoreInfo::getMaxScore() {
	return _maxScore;
}

int StageScoreInfo::getStage() {
	return _stage;
}
int StageScoreInfo::getMaxCombo() {
	return _maxCombo;
}


void StageScoreInfo::setMiter(float miter) {
	_miter = miter;
}
void StageScoreInfo::setItemCount(int itemCount)  {
	_useItemCount = itemCount;
}
float StageScoreInfo::getMiter() 
{
	return _miter;
}
int StageScoreInfo::getItemCount() {
	return _useItemCount;
}
void StageScoreInfo::setRank(long rank) {
	_rank = rank;
}
long StageScoreInfo::getRank() {
	return _rank;
}