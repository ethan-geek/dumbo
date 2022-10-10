#include "GamePlaySceneParts.h"
#include "../common/HHButton.h"
#include "../model/interactionObject.h"
#include "../model/UserInfo.h"
#include "../game/Hero.h"

#define FACEBOOK_PROFILE_TAG		9519

GamePlaySceneParts::GamePlaySceneParts(void) : _application(NULL)
{

	_application = AGApplication::GetInstance();

}


GamePlaySceneParts::~GamePlaySceneParts(void)
{
}

void GamePlaySceneParts::draw() {
	CCLayer::draw();

	if(HH_DEBUG) {
		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
		kmGLPushMatrix();
		_application->_world->DrawDebugData();
		kmGLPopMatrix();
	}

}

void GamePlaySceneParts::initFriendsScores() {

    
    vector<UserInfo> & list = AGApplication::GetInstance()->getGameData()->getFbFriendRecordList();
	int renewalIndex = AGApplication::GetInstance()->getGameData()->getRenewalIndex();
    char val[30];


    
    
    for(int i = 0 ; i < renewalIndex+1 ; ++i) {
    
        UserInfo * user = &list[i];

        int userDistance = (int)user->getEndlessScoreInfo().getMiter();
        sprintf(val, "%d M", userDistance);
        CCSprite* friendHeighBG = CCSprite::createWithSpriteFrameName("game_bg_hight_02.png");
        friendHeighBG->setAnchorPoint(ccp(0, 1));
        friendHeighBG->setUserData(user);
		
        _friendMeterLabel = CCLabelBMFont::create(val, TEXT_FONT_SMALL);
        _friendMeterLabel->setAnchorPoint(ccp(1, 0.5));
        _friendMeterLabel->setPosition(ccp(friendHeighBG->getContentSize().width - 10, friendHeighBG->getContentSize().height/2));
		CCSprite* friendProfile = AGUtil::createSpriteFromUrl(user->getFacebookId().c_str() , AGUtil::createFBProfileUrl(user->getFacebookId().c_str()).c_str());
		friendProfile->setPosition(CCPointZero);
		friendProfile->setAnchorPoint(CCPointZero);
		friendProfile->setScale(friendHeighBG->getContentSize().height/50);
        friendHeighBG->addChild(_friendMeterLabel, ZINDEX_HERO);
		friendHeighBG->addChild(friendProfile, ZINDEX_HERO);
        friendHeighBG->setVisible(false);
		
        AGApplication::GetInstance()->_parallaxNode->addChild(friendHeighBG, ZINDEX_HERO,ccp(0.0,1.0),ccp(12,user->getEndlessScoreInfo().getMiter() * 32));
        
        _friendRankLabels.push_back(friendHeighBG);
    }
    

}

bool GamePlaySceneParts::init() {

	if(!CCLayerColor::initWithColor(ccc4(86,183,243,0))) {
		return false;
	}

	this->setKeypadEnabled(true);
	AGApplication::GetInstance()->getGameData()->initMeter();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	CCSprite *jewelBG = CCSprite::createWithSpriteFrameName("game_bg_score.png");
	jewelBG->setAnchorPoint(ccp(1, 1));
	jewelBG->setPosition(ccp(winSize.width-12, winSize.height - 12));
	this->addChild(jewelBG, ZINDEX_HERO);

	_goldLabel = CCLabelBMFont::create("0", TEXT_FONT_SMALL, kCCTextAlignmentRight);
	_goldLabel->setAnchorPoint(ccp(1, 1));
	_goldLabel->setPosition(ccp(winSize.width - 20, winSize.height - 17));
	this->addChild(_goldLabel, ZINDEX_HERO);
    
    CCSprite* myHeightBG = CCSprite::createWithSpriteFrameName("game_bg_hight_01.png");
    myHeightBG->setAnchorPoint(ccp(0, 1));
    myHeightBG->setPosition(ccp(12, winSize.height-12));
    this->addChild(myHeightBG, ZINDEX_HERO);
    
    _friendHeighBG = CCSprite::createWithSpriteFrameName("game_bg_hight_02.png");
    _friendHeighBG->setAnchorPoint(ccp(0, 1));
    _friendHeighBG->setPosition(ccp(12, winSize.height-60));
    this->addChild(_friendHeighBG, ZINDEX_HERO);

    initFriendsScores();
    
	_meterLabel = CCLabelBMFont::create("0 M", TEXT_FONT_SMALL);
	_meterLabel->setAnchorPoint(ccp(1, 0.5));
	_meterLabel->setPosition(ccp(myHeightBG->getContentSize().width - 10, myHeightBG->getContentSize().height/2));
	myHeightBG->addChild(_meterLabel, ZINDEX_HERO);
    
    _friendMeterLabel = CCLabelBMFont::create("0 M", TEXT_FONT_SMALL);
    _friendMeterLabel->setAnchorPoint(ccp(1, 0.5));
    _friendMeterLabel->setPosition(ccp(_friendHeighBG->getContentSize().width - 10, _friendHeighBG->getContentSize().height/2));
    _friendHeighBG->addChild(_friendMeterLabel, ZINDEX_HERO);

    CCMenuItemImage *pauseBtn = CCMenuItemImage::create("button/btn_pause.png", "button/btn_pause.png", this, menu_selector(GamePlaySceneParts::pauseMenuListener));
    pauseBtn->setAnchorPoint(CCPointZero);
    CCMenu *pauseMenu = CCMenu::create(pauseBtn, NULL);
    pauseMenu->setAnchorPoint(CCPointZero);
    pauseMenu->setPosition(ccp(12, 12));
    this->addChild(pauseMenu, ZINDEX_HERO);

	CCSprite* itemFrame1 = CCSprite::createWithSpriteFrameName("item_frame.png");
    itemFrame1->setAnchorPoint(ccp(1, 0));
	itemFrame1->setPosition(ccp(winSize.width-12, 12));
	itemFrame1->setTag(PLACE_TYPE_ITEMFRAME_1);
	this->addChild(itemFrame1, ZINDEX_HERO);

	CCSprite *itemFrame2 = CCSprite::createWithSpriteFrameName("item_frame.png");
    itemFrame2->setAnchorPoint(ccp(1, 0));
    itemFrame2->setScale(0.8);
	itemFrame2->setPosition(ccp(winSize.width-12, itemFrame1->getPositionY() + itemFrame1->getContentSize().height + 10));
	itemFrame2->setTag(PLACE_TYPE_ITEMFRAME_2);
	this->addChild(itemFrame2, ZINDEX_HERO);


	_readyText = CCSprite::createWithSpriteFrameName("game_tutorial_start.png");
	_readyText->setPosition(ccp(winSize.width / 2, winSize.height * 0.55));
	_readyText->setScale(0.3);
	this->addChild(_readyText, 60);
	

	_tiltManual = CCSprite::createWithSpriteFrameName("game_tutotial_tilt.png");
	_tiltManual->setPosition(ccp(winSize.width / 2, winSize.height *0.55 -_readyText->getContentSize().height  ));
	//_tiltManual->setScale(0.3);
	this->addChild(_tiltManual, 60);

	CCScaleTo *scale = CCScaleTo::create(0.5, 1);
	CCEaseIn *easeIn = CCEaseIn::create(scale, 0.5);
	_readyText->runAction(easeIn);
	

	CCLabelBMFont *bmLabelName = CCLabelBMFont::create("patternName", TEXT_FONT_SMALL);
	__labelName = CCMenuItemLabel::create(bmLabelName);

	CCLabelBMFont *bmLabelHeight = CCLabelBMFont::create("patternHeight", TEXT_FONT_SMALL);
	__labelHeight = CCMenuItemLabel::create(bmLabelHeight);

	CCLabelBMFont *bmLabelCount = CCLabelBMFont::create("patternCount", TEXT_FONT_SMALL);
	__labelCount = CCMenuItemLabel::create(bmLabelCount);
	
	
//	CCMenu* menu = CCMenu::create(__labelHeight, __labelCount,__labelName, NULL);
//  	CCMenu* menu = CCMenu::create(__labelHeight, __labelCount,__labelName, NULL);
//	menu->alignItemsHorizontally();
//	this->addChild(menu);
//	
//	menu->setPosition(ccp(250,160));

	CCSprite *ground = CCSprite::createWithSpriteFrameName("parallax_bottom.png");
	ground->setTag(SPRITE_TYPE_FLOW_BACKGROUND);
    ground->setScale(1.2);
    ground->setAnchorPoint(CCPointZero);
    AGApplication::GetInstance()->_parallaxNode->addChild(ground, ZINDEX_PATICLE, ccp(0.0, 1), ccp(-30, -30));


	//fbRecord Setting
	if(AGApplication::GetInstance()->checkFacebook()) {
		UserInfo* recordFriend = AGApplication::GetInstance()->getGameData()->getCurrentRecordFriend();
		if(recordFriend != NULL) {
			char temp[20];
			sprintf(temp, "%.f M", recordFriend->getEndlessScoreInfo().getMiter());
			_friendMeterLabel->setString(temp);

			CCSprite* friendProfile = AGUtil::createSpriteFromUrl(recordFriend->getFacebookId().c_str() , AGUtil::createFBProfileUrl(recordFriend->getFacebookId().c_str()).c_str());
			friendProfile->setPosition(CCPointZero);
			friendProfile->setAnchorPoint(CCPointZero);
			friendProfile->setScale(_friendHeighBG->getContentSize().height/50);
			_friendHeighBG->addChild(friendProfile, ZINDEX_HERO);
			friendProfile->setTag(FACEBOOK_PROFILE_TAG);
		}
		//  i am top
		else {

			CCSprite* friendProfile = AGUtil::createSpriteFromUrl(AGApplication::GetInstance()->getUserInfo()->getFacebookId().c_str() , AGUtil::createFBProfileUrl(AGApplication::GetInstance()->getUserInfo()->getFacebookId().c_str()).c_str());
			friendProfile->setPosition(CCPointZero);
			friendProfile->setAnchorPoint(CCPointZero);
			friendProfile->setScale(_friendHeighBG->getContentSize().height/50);
			_friendHeighBG->addChild(friendProfile, ZINDEX_HERO);

			char temp[20];
			sprintf(temp, "%.f M", AGApplication::GetInstance()->getUserInfo()->getEndlessScoreInfo().getMiter());
			_friendMeterLabel->setString(temp);
		}
		
	}
	else {
		char temp[20];
		sprintf(temp, "%.f M", AGApplication::GetInstance()->getUserInfo()->getEndlessScoreInfo().getMiter());
		_friendMeterLabel->setString(temp);
	}

	
	


	if(HH_DEBUG) {
		_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_application->_world->SetDebugDraw(_debugDraw);

		uint32 flags= 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_centerOfMassBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		_debugDraw->SetFlags(flags);
	}

	return true;
}


#include "../common/XmlLoader.h"
void GamePlaySceneParts::tick(float dt) {
	char val[50];
	/*sprintf(val, "%d", _application->getGameData()->getCombo());
	_comboLabel->setString(val);*/

	sprintf(val, "%.f", _application->getGameData()->getGoldAmount());
	_goldLabel->setString(val);
    
    if(!_application->_hero->isStatus(HERO_STATUS_TYPE_DIE)) {
        sprintf(val, "%.f M", _application->getGameData()->getMiter());
        _meterLabel->setString(val);
    }

//	sprintf(val, " %s ", XmlLoader::getInstance()->getPatternData()._patternName.c_str());
//	__labelName->setString(val);
//
//	sprintf(val, "height : %.f", XmlLoader::getInstance()->getPatternData()._patternHeight);
//	__labelHeight->setString(val);
//
//	sprintf(val, "count : %d", XmlLoader::getInstance()->getPatternData()._patternCount);
//	__labelCount->setString(val);
    checkFriendRankVisibility();
    removeFriendRank();
	RenewalRescord();

	/*float percentage = _progressTimeBar->getPercentage() - (dt*10) ;
	_progressTimeBar->setPercentage(percentage);*/

}

void GamePlaySceneParts::checkFriendRankVisibility() {

    CCSprite * rankSprite = NULL;
    UserInfo * friendInfo = NULL;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float myMeter = AGApplication::GetInstance()->getGameData()->getMiter();
    
    for(int i = 0 ; i < _friendRankLabels.size() ; ++i) {
        
        rankSprite = _friendRankLabels[i];
        friendInfo = (UserInfo*)rankSprite->getUserData();
        
        if(friendInfo->getEndlessScoreInfo().getMiter() - myMeter > winSize.height / 32) {
            rankSprite->setVisible(true);
            _removeRankLabels.push_back(rankSprite);
            _friendRankLabels.erase(_friendRankLabels.begin() + i);
            
        }
    }
}

void GamePlaySceneParts::removeFriendRank() {

    CCSprite * rankSprite = NULL;
    UserInfo * friendInfo = NULL;
    
    for(int i = 0 ; i < _removeRankLabels.size() ; ++i) {
        
        rankSprite = _removeRankLabels[i];
        friendInfo = (UserInfo*)rankSprite->getUserData();

        if(-AGApplication::GetInstance()->_parallaxNode->getPositionY() > rankSprite->getPositionY() + CCDirector::sharedDirector()->getWinSize().height) {
            _removeRankLabels.erase(_removeRankLabels.begin() + i);
            rankSprite->removeAllChildren();
            rankSprite->removeFromParentAndCleanup(true);
        }
    }
}

void GamePlaySceneParts::RenewalRescord()  {

	char val[30];

	//if(AGApplication::GetInstance()->checkFacebook()) {
		//next friend record
		UserInfo* recordFriend = AGApplication::GetInstance()->getGameData()->getCurrentRecordFriend();
		if(recordFriend != NULL) {
            
			if(recordFriend->getEndlessScoreInfo().getMiter() < _application->getGameData()->getMiter()) {
				recordFriend = AGApplication::GetInstance()->getGameData()->getNextRecordFriend();
				// friend record renewal!!
				if(recordFriend != NULL) {
					sprintf(val, "%.f M", recordFriend->getEndlessScoreInfo().getMiter());
					_friendMeterLabel->setString(val);

					CCSprite* friendProfile = AGUtil::createSpriteFromUrl(recordFriend->getFacebookId().c_str() , AGUtil::createFBProfileUrl(recordFriend->getFacebookId().c_str()).c_str());
					friendProfile->setPosition(CCPointZero);
					friendProfile->setAnchorPoint(CCPointZero);
					friendProfile->setScale(_friendHeighBG->getContentSize().height/50);
					friendProfile->setTag(FACEBOOK_PROFILE_TAG);

					CCNode* node = _friendHeighBG->getChildByTag(FACEBOOK_PROFILE_TAG);
					if(node != NULL) node->removeFromParentAndCleanup(true);

					_friendHeighBG->addChild(friendProfile, ZINDEX_HERO);

				}
				// when.. me top!!
				else {
					recordFriend = AGApplication::GetInstance()->getUserInfo();
					CCSprite* friendProfile = AGUtil::createSpriteFromUrl(recordFriend->getFacebookId().c_str() , AGUtil::createFBProfileUrl(recordFriend->getFacebookId().c_str()).c_str());
					friendProfile->setPosition(CCPointZero);
					friendProfile->setAnchorPoint(CCPointZero);
					friendProfile->setScale(_friendHeighBG->getContentSize().height/50);
					friendProfile->setTag(FACEBOOK_PROFILE_TAG);
					_friendHeighBG->addChild(friendProfile, ZINDEX_HERO);
                    sprintf(val, "%.f M", AGApplication::GetInstance()->getGameData()->getMiter());
                    _friendMeterLabel->setString(val);
				}
			}
		}
		//  i am top
		else {
			if(AGApplication::GetInstance()->getUserInfo()->getEndlessScoreInfo().getMiter() < AGApplication::GetInstance()->getGameData()->getMiter()) {

				/*CCNode* node = _friendHeighBG->getChildByTag(FACEBOOK_PROFILE_TAG);
				if(node != NULL) node->removeFromParentAndCleanup(true);*/

				sprintf(val, "%.f M", AGApplication::GetInstance()->getGameData()->getMiter());
				_friendMeterLabel->setString(val);
			}
			
		}
	}


#include "./Hero.h"
void GamePlaySceneParts::pauseMenuListener(CCObject* object) {

    //_application->_hero->setStatusType(HERO_STATUS_TYPE_DIE);
	/*_application->setSpeed(HERO_STATUS_TYPE_JUMP);*/
	//return;

	PausePopup* pausePopup = PausePopup::createWithSize(CCSizeMake(500, 600));
	pausePopup->show();
}

void GamePlaySceneParts::closeManual() {
	if (_readyText) {
		CCFadeOut *fadeOut = CCFadeOut::create(0.2);
		CCScaleTo *scale = CCScaleTo::create(0.2, 6);
		CCSpawn *spawn = CCSpawn::create(fadeOut, scale, NULL);
		CCEaseIn *easeIn = CCEaseIn::create(spawn, 0.2);
		CCCallFunc *readyCallback = CCCallFunc::create(this, callfunc_selector(GamePlaySceneParts::readyCallback));
		CCSequence *seq = CCSequence::create(easeIn, readyCallback, NULL);
		_readyText->runAction(seq);
	}

	if(_tiltManual != NULL) {
		CCFadeOut *fadeOut = CCFadeOut::create(0.2);
		CCScaleTo *scale = CCScaleTo::create(0.2, 6);
		CCSpawn *spawn = CCSpawn::create(fadeOut, scale, NULL);
		CCEaseIn *easeIn = CCEaseIn::create(spawn, 0.2);
		CCCallFunc *readyCallback = CCCallFunc::create(this, callfunc_selector(GamePlaySceneParts::readyCallback));
		CCSequence *seq = CCSequence::create(easeIn, readyCallback, NULL);
		_tiltManual->runAction(seq);
	}
}

void GamePlaySceneParts::readyCallback()
{
	if(_readyText != NULL) {
		_readyText->removeFromParentAndCleanup(true);
		_readyText = NULL;
	}
	if(_tiltManual != NULL) {
		_tiltManual->removeFromParentAndCleanup(true);
		_tiltManual = NULL;
	}

}

void GamePlaySceneParts::showTutorial()
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(IS_FIRST_TIME_GETTING_ITEM, false);
    _application->setStop(true);

    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 130), this->getContentSize().width, this->getContentSize().height);
    layer->setTag(1983);
    layer->setPosition(CCPointZero);
    this->addChild(layer);
    
    CCSprite* touchImage = CCSprite::createWithSpriteFrameName("game_tutorial_touch.png");
    touchImage->setPosition(ccp(layer->getContentSize().width/2 + 35, layer->getContentSize().height/2));
    layer->addChild(touchImage);
    
    CCSprite* itemFrame = (CCSprite*)this->getChildByTag(PLACE_TYPE_ITEMFRAME_1);
    CCSprite* item = (CCSprite*)itemFrame->getChildren()->objectAtIndex(0);
    
    CCFadeIn *fadeIn = CCFadeIn::create(0.5);
    CCFadeOut *fadeOut = CCFadeOut::create(0.5);

    CCSequence *seq = CCSequence::create(fadeOut, fadeIn, NULL);
    CCSequence* totalActionSeq = CCSequence::create(seq, CCCallFuncO::create(this, callfuncO_selector(GamePlaySceneParts::showTutorialCallback), touchImage), NULL);
    
    item->runAction(totalActionSeq);
    
}


void GamePlaySceneParts::showTutorialCallback(CCObject* obj)
{
    CCSprite* touchImage = (CCSprite*)obj;
    
    CCScaleTo *scaleUp = CCScaleTo::create(0.5, 1.2);
    CCScaleTo *scaleDown = CCScaleTo::create(0.5, 0.9);
    
    CCSequence* seq = CCSequence::create(scaleUp, scaleDown, NULL);
    CCRepeatForever *repeat = CCRepeatForever::create(seq);
    
    touchImage->runAction(repeat);
}

void GamePlaySceneParts::keyBackClicked() {


	CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
    CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);

	CCNode* node = layer->getChildByTag(BASICPOPUP);
	if(node != NULL) {
	
		((PausePopup*)node)->menuCloseCallback(NULL);
		AGUtil::gameResume();
		return;
	}

	PausePopup* pausePopup = PausePopup::createWithSize(CCSizeMake(500, 600));
	pausePopup->show();
}
