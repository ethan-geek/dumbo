///////////////////////////////////////////////////////////
//
//  Implementation of the Class ClearPopup
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "ClearPopup.h"
#include "HighScoreCell.h"
#include "../view/StageMapScene.h"
#include "../view/MainMenuScene.h"
#include "../model/HeartInfo.h"
#include "../helper/AndroidHelper.h"
#include "../common/HHButton.h"
#include "RankingView.h"


#define MIN_SCORE_SCHEDULE_COUNT 100
#define MIN_RECORD_SCHEDULE_COUNT 100

CCScene* ClearPopup::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ClearPopup *layer = ClearPopup::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

ClearPopup::ClearPopup(){

}



ClearPopup::~ClearPopup(){
	//_scoreTable->removeAllChildren();
}



bool ClearPopup::init()  {

	if ( !CCLayerColor::initWithColor(ccc4(0,0,0,255)) )
	{
		return false;
	}
    
    HiHighAudio::sharedAudio()->playMusic("ending_bgm");
    
    CCParticleSystem *ptc = CCParticleSystemQuad::create("paticle/score_star2.plist");
    ptc->setScale(1.5);
    ptc->setAutoRemoveOnFinish(true);
    ptc->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(ptc, 99);

	showAdvertisement();
	this->setKeypadEnabled(true);
	_winSize = CCDirector::sharedDirector()->getWinSize();
    m_application = AGApplication::GetInstance();

    initScoreView();
    initRankingView();


	

	this->scheduleOnce(schedule_selector(ClearPopup::renewalCallbackFunc), 3.0);
	
   
	return true;
}

void ClearPopup::renewalCallbackFunc(float dt) {
	if(AGApplication::GetInstance()->checkFacebook()) {
		if(AGApplication::GetInstance()->getGameData()->isRenewal()) {
			_renewalAlert = HHAlert::create(NULL, "Share on Facebook?", "OK", "Cancel");
			_renewalAlert->okayBtn->setTarget(this, menu_selector(ClearPopup::facebookShare));
			_renewalAlert->showPush();
		}
	}
}


void ClearPopup::initScoreView()
{
    //top area
    CCLayer *topLayer = CCLayer::create();
    topLayer->setAnchorPoint(CCPointZero);
    topLayer->setContentSize(CCSizeMake(_winSize.width, 145));
    topLayer->setPosition(ccp(0, _winSize.height - 145));
    this->addChild(topLayer);
    
    CCSprite* line = CCSprite::createWithSpriteFrameName("sub_titlebar_top.png");
    line->setAnchorPoint(CCPointZero);
    line->setPosition(ccp(0, 0));
    topLayer->addChild(line);
    
    CCLabelBMFont *scoreLabel = CCLabelBMFont::create("S C O R E", TEXT_FONT_NORMAL);
    scoreLabel->setPosition(ccp(50 + scoreLabel->getContentSize().width/2, topLayer->getContentSize().height/2));
    topLayer->addChild(scoreLabel);
    
    CCSprite* jewelBG = CCSprite::createWithSpriteFrameName("jewel_score_bg.png");
    jewelBG->setAnchorPoint(ccp(1, 0.5));
    jewelBG->setPosition(ccp(topLayer->getContentSize().width-30, topLayer->getContentSize().height/2));
    topLayer->addChild(jewelBG);
    
    ostringstream os;
    os << m_application->getUserInfo()->getGold();
    string temp = os.str();
    AGUtil::calc3point(temp);
    m_hasCoin = CCLabelBMFont::create(temp.c_str(), TEXT_FONT_SMALL);
    m_hasCoin->setAnchorPoint(ccp(1, 0.5));
    os.clear();
    m_hasCoin->setPosition(ccp(topLayer->getContentSize().width-50, topLayer->getContentSize().height/2));
    topLayer->addChild(m_hasCoin);
    //top area
    
    
    //score box
    CCLayer *scoreLayer = CCLayer::create();
    scoreLayer->setAnchorPoint(CCPointZero);
    scoreLayer->setContentSize(CCSizeMake(_winSize.width, 190));
    scoreLayer->setPosition(ccp(0, _winSize.height-146 - 190));
    this->addChild(scoreLayer);
    
    CCLabelBMFont *jewelLabel = CCLabelBMFont::create("J E W E L", TEXT_FONT_SMALL);
    jewelLabel->setAnchorPoint(CCPointZero);
    jewelLabel->setPosition(ccp(120, 130));
    scoreLayer->addChild(jewelLabel);
    
    jewelValue = CCLabelBMFont::create("0", TEXT_FONT_SMALL, kCCTextAlignmentRight);
    jewelValue->setAnchorPoint(ccp(1 ,0));
    jewelValue->setPosition(ccp(topLayer->getContentSize().width - 120, 130));
    scoreLayer->addChild(jewelValue);
    
    CCLabelBMFont *maxComboLabel = CCLabelBMFont::create("MAX COMBO", TEXT_FONT_SMALL);
    maxComboLabel->setAnchorPoint(CCPointZero);
    maxComboLabel->setPosition(ccp(120, 90));
    scoreLayer->addChild(maxComboLabel);
    
    maxComboValue = CCLabelBMFont::create("0", TEXT_FONT_SMALL, kCCTextAlignmentRight);
    maxComboValue->setAnchorPoint(ccp(1 ,0));
    maxComboValue->setPosition(ccp(topLayer->getContentSize().width - 120, 90));
    scoreLayer->addChild(maxComboValue);
    
    CCLabelBMFont *recordLabel = CCLabelBMFont::create("R E C O R D", TEXT_FONT_SMALL);
    recordLabel->setAnchorPoint(CCPointZero);
    recordLabel->setPosition(ccp(120, 20));
    recordLabel->setColor(ccc3(221, 183, 7));
    scoreLayer->addChild(recordLabel);
    
    recordValue = CCLabelBMFont::create("0m", TEXT_FONT_NORMAL, kCCTextAlignmentRight);
    recordValue->setAnchorPoint(ccp(1, 0));
    recordValue->setPosition(ccp(topLayer->getContentSize().width - 110, 14));
    recordValue->setColor(ccc3(221, 183, 7));
    scoreLayer->addChild(recordValue);
    
    //score box
    CCMenuItemLabel* menuBtn = AGUtil::createLabelButton("M E N U", TEXT_FONT_NORMAL, "", "btn_bg_02.png", 0, this, menu_selector(ClearPopup::homeBtnListener));
    menuBtn->setOpacity(255*0.6);
    CCMenuItemLabel* restartBtn = AGUtil::createLabelButton("R E S T A R T", TEXT_FONT_NORMAL, "", "btn_bg_03.png", 0, this, menu_selector(ClearPopup::replayBtnListener));
    
    CCMenu * menu = CCMenu::create(menuBtn, restartBtn, NULL);
    menu->setPosition(ccp(_winSize.width/2, _winSize.height-403));
    menu->alignItemsHorizontallyWithPadding(20);
    this->addChild(menu);
    
    
    //Setting score
    ostringstream ossJewel;
    ossJewel << m_application->getGameData()->getGoldAmount();
    jewelValue->setString(ossJewel.str().c_str());
    ossJewel.clear();
    
    ostringstream ossCombo;
    ossCombo << m_application->getGameData()->getMaxCombo();
    maxComboValue->setString(ossCombo.str().c_str());
    ossCombo.clear();
    
    ostringstream ossRecord;
    int meterInt = (int)(m_application->getGameData()->getMiter()+0.5) - (m_application->getGameData()->getMaxCombo());
    ossRecord << meterInt;
    recordValue->setString(ossRecord.str().append("M").c_str());
    ossRecord.clear();
    
    int scheduleCount = m_application->getGameData()->getMaxCombo();
    this->schedule(schedule_selector(ClearPopup::earnedComboAnimation), 0.0001, scheduleCount-1, 0.5);

}


void ClearPopup::earnedComboAnimation(float dt)
{
    int earnedCombo = atof(maxComboValue->getString());
    earnedCombo -= 1;
    ostringstream oss;
    oss << earnedCombo;
    maxComboValue->setString(oss.str().c_str());
    oss.clear();
    
    string distanceStr = recordValue->getString();
    distanceStr = distanceStr.substr(0, distanceStr.size()-1);
    int distance = atof(distanceStr.c_str());
    distance += 1;
    
    ostringstream oss2;
    oss2 << distance;
    recordValue->setString(oss2.str().append("M").c_str());
    oss2.clear();
}

void ClearPopup::initRankingView()
{
	_rankingView = RankingView::create();
	_rankingView->setAnchorPoint(CCPointZero);
	_rankingView->setPosition((_winSize.width - 572)/2, 110);
    this->addChild(_rankingView, 299);
}


void ClearPopup::replayBtnListener(cocos2d::CCObject *pSender)
{
	SceneManager::replaceScene("AbilitiesScene");
	/*CCScene *loading = GameLoadingScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, loading);
	CCDirector::sharedDirector()->replaceScene(transition);*/
}

void ClearPopup::homeBtnListener(cocos2d::CCObject *pSender)
{
	SceneManager::replaceScene("MainMenuScene");

	/*CCScene *home = MainMenuScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, home);
	CCDirector::sharedDirector()->replaceScene(transition);*/
}


void ClearPopup::showAdvertisement()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	android_showBanner();
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
    [notiCenter postNotificationName:@"showBannerNotification" object:nil];
#endif
}

void ClearPopup::onExitTransitionDidStart()
{
    CCLog("onExitTransitionDidStart");
    CCLayer::onExitTransitionDidStart();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    android_removeBanner();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
    [notiCenter postNotificationName:@"removeBannerNotification" object:nil];
#endif
    
    
}

static int int_width(int num)
{
    int ret;
    if (num < 0) num = -num;
    for (ret = 0; num > 0; num /= 10, ret ++);
    return ret;
}


void ClearPopup::keyBackClicked() {
	SceneManager::replaceScene("MainMenuScene");
	/*CCScene* main = MainMenuScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
    CCDirector::sharedDirector()->replaceScene(transition);*/
}


void ClearPopup::facebookShare(CCObject* obj)  {
	_renewalAlert->close(obj);

	_rankingView->fbShareBtnListener(NULL);
}
