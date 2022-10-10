///////////////////////////////////////////////////////////
//  StageInfoPopup.cpp
//  Implementation of the Class StageInfoPopup
//  Created on:      19-3-2014 ���� 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "StageInfoPopup.h"
#include "GameLoadingScene.h"
#include "../model/UserInfo.h"

#define SETTING_INFO_POPUP_WIDTH 620
#define SETTING_INFO_POPUP_HEIGHT 1160
#define SCORE_TABLE_WIDTH 580
#define SCORE_TABLE_HEIGHT 310
#define SCORE_TABLECELL_WIDTH 580
#define SCORE_TABLECELL_HEIGHT 100

StageInfoPopup::StageInfoPopup(){

}



StageInfoPopup::~StageInfoPopup(){

}

StageInfoPopup* StageInfoPopup::create()
{
    StageInfoPopup *pRet = new StageInfoPopup();
    pRet->autorelease();
    pRet->initPopup(CCSizeMake(SETTING_INFO_POPUP_WIDTH, SETTING_INFO_POPUP_HEIGHT));
    pRet->initData();
    pRet->initStageInfoPopup();
    
    return pRet;
}



void StageInfoPopup::initStageInfoPopup()
{
    closeMenu->setTouchPriority(-200);
    bottomLayer = CCLayer::create();
    bottomLayer->setContentSize(ccp(SETTING_INFO_POPUP_WIDTH, 570));
    mainLayer->addChild(bottomLayer);
    mainLayer->setAnchorPoint(ccp(0, 0));
    bottomLayer->setPosition(ccp(0, 0));

    
    topLayer = CCLayer::create();
    topLayer->setContentSize(ccp(SETTING_INFO_POPUP_WIDTH, 570));

    topLayer->setPosition(ccp(0, bottomLayer->getContentSize().height+10));
    mainLayer->addChild(topLayer);
    
    CCSprite *topBg = CCSprite::createWithSpriteFrameName("popup_bg_03.png");
    topBg->setPosition(ccp(topLayer->getContentSize().width/2, topLayer->getContentSize().height/2));
    
    CCSprite *bottomBg = CCSprite::createWithSpriteFrameName("popup_bg_03.png");
    bottomBg->setPosition(ccp(bottomLayer->getContentSize().width/2, bottomLayer->getContentSize().height/2));
    
    topLayer->addChild(topBg);
    bottomLayer->addChild(bottomBg);
    
    CCLabelTTF* highScoreLabel = CCLabelTTF::create("High Score", "Marker Felt", 40);
    highScoreLabel->setPosition(ccp(bottomLayer->getContentSize().width/2, bottomLayer->getContentSize().height-30));
    bottomLayer->addChild(highScoreLabel);
    
    CCTableView* scoreTable = CCTableView::create(this, CCSizeMake(SCORE_TABLE_WIDTH,  SCORE_TABLE_HEIGHT));
    scoreTable->setPosition(ccp(10., 0));
	scoreTable->setTouchPriority(-200);

	scoreTable->setDelegate(this);
	scoreTable->setDirection(kCCScrollViewDirectionVertical);
	scoreTable->setVerticalFillOrder(kCCTableViewFillTopDown);
	bottomLayer->addChild(scoreTable);
    scoreTable->reloadData();
    
    
	char tempStage[10];
	char tempPoint[1024];
	char tempCombo[1024];

	UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
	StageScoreInfo* scoreInfo = userInfo->getStageScoreInfo(AGApplication::GetInstance()->getGameData()->getCurrentStage());
	if(scoreInfo == NULL) {
		sprintf(tempPoint, "%d point", 0);
		sprintf(tempCombo, "with %d combo", 0);
	}
	else {
		sprintf(tempPoint, "%d point", scoreInfo->getMaxScore());
		sprintf(tempCombo, "with %d combo", scoreInfo->getMaxCombo());
	}

	sprintf(tempStage, "stage %d", AGApplication::GetInstance()->getGameData()->getCurrentStage());

	
	

	

    CCLabelTTF* stageLabel = CCLabelTTF::create(tempStage, "Marker Felt", 50);
    stageLabel->setPosition(ccp(topLayer->getContentSize().width/2, topLayer->getContentSize().height-50));
    topLayer->addChild(stageLabel);
    
    CCLabelTTF* myRecordLabel = CCLabelTTF::create("My record", "Marker Felt", 40);
    myRecordLabel->setAnchorPoint(CCPointZero);
    myRecordLabel->setPosition(ccp(50, topLayer->getContentSize().height-200));
    topLayer->addChild(myRecordLabel);
    
    CCLabelTTF* pointLabel = CCLabelTTF::create(tempPoint, "Marker Felt", 35);
    pointLabel->setPosition(ccp(topLayer->getContentSize().width/2, topLayer->getContentSize().height-260));
    topLayer->addChild(pointLabel);
    
    CCLabelTTF* comboLabel = CCLabelTTF::create(tempCombo, "Marker Felt", 35);
    comboLabel->setPosition(ccp(topLayer->getContentSize().width/2, topLayer->getContentSize().height-300));
    topLayer->addChild(comboLabel);
    
    CCSprite * play = CCSprite::createWithSpriteFrameName("play.jpg");
    CCMenuItemSprite * playItem = CCMenuItemSprite::create(play, play,this, menu_selector(StageInfoPopup::play));
    CCMenu * playMenu = CCMenu::create(playItem, NULL);
    playMenu->setPosition(ccp(topLayer->getContentSize().width/2, 50));
    topLayer->addChild(playMenu);
    
}

void StageInfoPopup::initData()
{
    _scoreDatas.clear();
	
	ScoreData data;
	
	data.name = "Sunny";
	data.maxCombo = 61;
    data.point = 60000;
	_scoreDatas.push_back(data);
    
    
	data.name = "Crusader";
	data.maxCombo = 51;
    data.point = 50000;
	_scoreDatas.push_back(data);
    
    
	data.name = "Geek";
	data.maxCombo = 41;
    data.point = 40000;
	_scoreDatas.push_back(data);
    
    
	data.name = "Jackdaw";
	data.maxCombo = 31;
    data.point = 30000;
	_scoreDatas.push_back(data);
    
    
	data.name = "Insanity";
	data.maxCombo = 21;
    data.point = 20000;
	_scoreDatas.push_back(data);
    
    data.name = "Snoop";
	data.maxCombo = 11;
    data.point = 10000;
	_scoreDatas.push_back(data);
}

//datasource method
void StageInfoPopup::scrollViewDidScroll(CCScrollView* view)
{
	
}
void StageInfoPopup::scrollViewDidZoom(CCScrollView* view)
{
	
}

unsigned int StageInfoPopup::numberOfCellsInTableView(CCTableView *table)
{
	return _scoreDatas.size();
}

CCSize StageInfoPopup::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(SCORE_TABLECELL_WIDTH, SCORE_TABLECELL_HEIGHT);
}

CCTableViewCell* StageInfoPopup::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell* cell = table->dequeueCell();
	
	if (cell == NULL) {
		cell = new CCTableViewCell();
		cell->autorelease();
		
		ScoreData& data = _scoreDatas[idx];
        
        CCLabelTTF* nameLabel = CCLabelTTF::create(data.name.c_str(), "Marker Felt", 25.0f);
		nameLabel->setAnchorPoint(CCPointZero);
		nameLabel->setPosition(ccp(SCORE_TABLECELL_WIDTH * 0.1f, 70));
		nameLabel->setTag(1);
		cell->addChild(nameLabel);
        
		
        stringstream strstream;
        strstream << data.point << " Point with " << data.maxCombo << " Combo ";
        
		CCLabelTTF* scoreLabel = CCLabelTTF::create(strstream.str().c_str(), "Marker Felt", 25.0f);
		scoreLabel->setAnchorPoint(CCPointZero);
		scoreLabel->setPosition(ccp(SCORE_TABLECELL_WIDTH * 0.1f, 30));
		scoreLabel->setTag(2);
		cell->addChild(scoreLabel);
        
	}else {
        ScoreData& data = _scoreDatas[idx];
        
		CCLabelTTF* nameLabel = (CCLabelTTF*)cell->getChildByTag(1);
		nameLabel->setString(data.name.c_str());
        
        stringstream strstream;
        strstream << data.point << " Point with " << data.maxCombo << " Combo ";
        
        CCLabelTTF* scoreLabel = (CCLabelTTF*)cell->getChildByTag(2);
		scoreLabel->setString(strstream.str().c_str());
    }
	
	return cell;
}




//delegate method
void StageInfoPopup::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{

}


void StageInfoPopup::play(CCObject* obj)
{
    menuCloseCallback(NULL);
    CCScene *loading = GameLoadingScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, loading);
    CCDirector::sharedDirector()->replaceScene(transition);
}


void StageInfoPopup::show()
{
    
    CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
    
    topLayer->setPosition(ccp(topLayer->getPositionX(), mainLayer->getContentSize().height));
    bottomLayer->setPosition(ccp(0, -bottomLayer->getContentSize().height));
    
    layer->addChild(this);
    
    CCMoveTo *moveTo1 = CCMoveTo::create(0.15, ccp(0, bottomLayer->getContentSize().height+20));
    CCMoveTo *moveTo2 = CCMoveTo::create(0.15, ccp(0, 0));
    
    
    topLayer->runAction(moveTo1);
    bottomLayer->runAction(moveTo2);
}

