//
//  RankingView.cpp
//  HiHigh
//
//  Created by Insanity on 2014. 10. 21..
//
//

#include "RankingView.h"
#include "HighScoreCell.h"
#include "../common/AGApplication.h"
#include "../model/UserInfo.h"
#include "../common/HiHighConnector.h"
#include "../common/HHButton.h"
#include "RankingScreenShotScene.h"
#include "../common/HHAlert.h"
#include "../view/MainMenuScene.h"
#include "../network/HHNetwork.h"
#include "CCActivityIndicator.h"

#define FACEBOOK_TABLE_TAG  0
#define ALL_TABLE_TAG       1

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../fb/FacebookInterface.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../fb/FacebookInterfaceiOS.h"
#endif

Facebook::REQUEST_TYPE RankingView::reqType = Facebook::NONE;

RankingView::RankingView() : mSelectedTab(1), mFbTableView(NULL), mCompleteCount(0),
isDrawComplete(false), isFacebookConnected(false), isPaging(false),
pageIndex(0), cellLastIndex(0),isListFull(false)
{
}



RankingView::~RankingView()
{
	delete m_util;
	
}


bool RankingView::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 255)))
	{
		return false;
	}


    
	mAlert = NULL;

	mWinSize = CCDirector::sharedDirector()->getWinSize();

	this->setContentSize(CCSizeMake(572, 564));

	mAllBG = CCSprite::createWithSpriteFrameName("score_bg_all.png");
	mAllBG->setAnchorPoint(CCPointZero);
	mFBBG = CCSprite::createWithSpriteFrameName("score_bg_facebook.png");
	mFBBG->setAnchorPoint(CCPointZero);

	this->addChild(mAllBG);
	this->addChild(mFBBG);

	if(CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {
		isFacebookConnected = true;
	}else {
		isFacebookConnected = false;
	}

	initMenuArea();
	initContentsArea();

	CCSprite* tempObj = CCSprite::create();
	if(isFacebookConnected) {
		tempObj->setTag(1);
		tabListener(tempObj);
	}else {
		tempObj->setTag(0);
		tabListener(tempObj);
	}

	return true;
}


void RankingView::initMenuArea()
{
	mTab1Layer = CCLayerColor::create(ccc4(0, 0, 0, 0), this->getContentSize().width/2 , 60);
	mTab1Layer->setAnchorPoint(CCPointZero);
	mTab1Layer->setPosition(ccp(0, this->getContentSize().height-70));

	mTab2Layer = CCLayerColor::create(ccc4(0, 0, 0, 0), this->getContentSize().width/2, 60);
	mTab2Layer->setAnchorPoint(CCPointZero);
	mTab2Layer->setPosition(ccp(this->getContentSize().width/2, mTab1Layer->getPositionY()));


	CCMenuItemLabel *allItem = CCMenuItemLabel::create(CCLabelBMFont::create("A L L", TEXT_FONT_SMALL), this, menu_selector(RankingView::tabListener));
	allItem->setAnchorPoint(ccp(0.5, 0.5));
	allItem->setContentSize(mTab2Layer->getContentSize());
	allItem->getLabel()->setAnchorPoint(ccp(0.5, 0.5));
	allItem->getLabel()->setPosition(ccp(allItem->getContentSize().width/2, allItem->getContentSize().height/2));
	allItem->setTag(0);

	CCMenuItemLabel *facebookItem = CCMenuItemLabel::create(CCLabelBMFont::create("F A C E B O O K", TEXT_FONT_SMALL), this, menu_selector(RankingView::tabListener));
	facebookItem->setAnchorPoint(ccp(0.5, 0.5));
	facebookItem->setContentSize(mTab1Layer->getContentSize());
	facebookItem->getLabel()->setAnchorPoint(ccp(0.5, 0.5));
	facebookItem->getLabel()->setPosition(ccp(facebookItem->getContentSize().width/2, facebookItem->getContentSize().height/2));
	facebookItem->setTag(1);

	mAllTabBtn = CCMenu::create(allItem, NULL);
	mAllTabBtn->setPosition(ccp(mTab1Layer->getContentSize().width / 2, mTab1Layer->getContentSize().height/2));
	mTab2Layer->addChild(mAllTabBtn);

	mFacebookTabBtn = CCMenu::create(facebookItem, NULL);
	mFacebookTabBtn->setPosition(ccp(mTab1Layer->getContentSize().width / 2, mTab1Layer->getContentSize().height/2));
	mTab1Layer->addChild(mFacebookTabBtn);

	this->addChild(mTab1Layer);
	this->addChild(mTab2Layer);

	AGApplication::GetInstance()->setObjectMap("RANKING_VIEW", this);
	m_util = AGUtil::create(this, callfuncN_selector(RankingView::loadingComplete));
	m_util->m_call = false;
	//	CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
	//	CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
	//

}


void RankingView::initContentsArea()
{
	mFbRankingLayer = CCLayer::create();
	//	mFbRankingLayer = CCLayerColor::create(ccc4(0, 255, 0, 255));
	mFbRankingLayer->setAnchorPoint(CCPointZero);
	mFbRankingLayer->setContentSize(CCSizeMake(this->getContentSize().width, this->getContentSize().height - 60));
	mFbRankingLayer->setPosition(ccp(0, 0));
	this->addChild(mFbRankingLayer);

	if(isFacebookConnected) {
		//table for facebook rank
		//		mFbTableView = CCTableView::create(this, CCSizeMake(mFbRankingLayer->getContentSize().width,  mFbRankingLayer->getContentSize().height - 110));
		mFbTableView = CCTableView::create(this, CCSizeMake(mFbRankingLayer->getContentSize().width,  mFbRankingLayer->getContentSize().height - 20 - 105));
		mFbTableView->setTag(FACEBOOK_TABLE_TAG);
		mFbTableView->setPosition(ccp(0, 96));
		mFbTableView->setTouchPriority(-200);
		mFbTableView->setDelegate(this);
		mFbTableView->setBounceable(false);
		mFbTableView->setDirection(kCCScrollViewDirectionVertical);
		mFbTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
		mFbRankingLayer->addChild(mFbTableView);

		CCSprite *line = CCSprite::createWithSpriteFrameName("score_line_facebook.png");
		line->setPosition(ccp(mFbRankingLayer->getContentSize().width/2, 94));
		mFbRankingLayer->addChild(line);
		line->setTag(4556);
		CCMenuItemLabel *inviteBtn = AGUtil::createLabelButton("I N V I T E", TEXT_FONT_SMALL, "", "btn_bg_04.png", 0, this, menu_selector(RankingView::fbInviteBtnListener));
		CCMenuItemLabel *shareBtn = AGUtil::createLabelButton("S H A R E", TEXT_FONT_SMALL, "", "btn_bg_04.png", 0, this, menu_selector(RankingView::fbShareBtnListener));

		CCMenu *fbMenu = CCMenu::create(inviteBtn, shareBtn, NULL);
		fbMenu->setPosition(ccp(mFbRankingLayer->getContentSize().width/2, 50));
		fbMenu->alignItemsHorizontallyWithPadding(30);
		fbMenu->setTag(2556);
		mFbRankingLayer->addChild(fbMenu);
	}else {

		CCLabelBMFont *message1 = CCLabelBMFont::create("YOU MUST BE CONNECTED IN", TEXT_FONT_SMALL);
		CCLabelBMFont *message2 = CCLabelBMFont::create("WITH A FACEBOOK ACCOUNT.", TEXT_FONT_SMALL);
		message1->setPosition(ccp(mFbRankingLayer->getContentSize().width/2, mFbRankingLayer->getContentSize().height/2 + 45));
		message2->setPosition(ccp(mFbRankingLayer->getContentSize().width/2, mFbRankingLayer->getContentSize().height/2 + 10));
		mFbRankingLayer->addChild(message1);
		mFbRankingLayer->addChild(message2);

		CCMenuItemLabel *mainBtn = AGUtil::createLabelButton("GO TO CONNECT", TEXT_FONT_SMALL, "", "btn_bg_02.png", 0, this, menu_selector(RankingView::goToConnect));
		CCMenu *m = CCMenu::create(mainBtn, NULL);
		m->setPosition(ccp(mFbRankingLayer->getContentSize().width/2, mFbRankingLayer->getContentSize().height/2 - 66));
		mFbRankingLayer->addChild(m);
	}

	mAllRankingLayer = CCLayer::create();
	mAllRankingLayer->setAnchorPoint(CCPointZero);
	mAllRankingLayer->setContentSize(CCSizeMake(this->getContentSize().width, this->getContentSize().height - 60));
	mAllRankingLayer->setPosition(ccp(0, 0));
	this->addChild(mAllRankingLayer);

	mAllRankingLayer->setVisible(false);


	//table for all user rank
	mAllTableView = CCTableView::create(this, CCSizeMake(mFbRankingLayer->getContentSize().width,  mFbRankingLayer->getContentSize().height - 33));
	mAllTableView->setTag(ALL_TABLE_TAG);
	mAllTableView->setPosition(ccp(0, 4));
	mAllTableView->setTouchPriority(-200);
	mAllTableView->setDelegate(this);
	mAllTableView->setDirection(kCCScrollViewDirectionVertical);
	mAllTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	mAllTableView->setBounceable(false);
	mAllRankingLayer->addChild(mAllTableView);


	if(AGApplication::GetInstance()->checkFacebook() && HiHighConnector::sharedConnector()->getFbFriendCount() > 0 && HHNetwork::GetInstance()->getNetworkStatus() ) {
		CCLog("sendFacebookFriendList");
		HiHighConnector::sharedConnector()->sendFacebookFriendList(AGApplication::GetInstance()->getUserInfo()->getFacebookId().c_str(), this, httpresponse_selector(RankingView::onHttpRequestCompleted));
	}
	else {
		if (mFbTableView != NULL) {
			mFacebookRanks.clear();
			mFacebookRanks.push_back(*AGApplication::GetInstance()->getUserInfo());
			mFbTableView->reloadData();
		}

		/*mAllRanks.clear();
		mAllRanks.push_back(*AGApplication::GetInstance()->getUserInfo());
		mAllTableView->reloadData();*/
	}

	if(HHNetwork::GetInstance()->getNetworkStatus()) {
		HiHighConnector::sharedConnector()->allRankList(AGApplication::GetInstance()->getUserInfo(), this->pageIndex, this,httpresponse_selector(RankingView::onAllRanksRequestCompleted));
	}
	else {
		mAllRanks.clear();
		mAllRanks.push_back(*AGApplication::GetInstance()->getUserInfo());
		mAllTableView->reloadData();
	}
	

}

void RankingView::tabListener(CCObject* obj)
{
	CCMenuItemLabel *sender = (CCMenuItemLabel*)obj;

	if(sender->getTag() == 0) {
		mFbRankingLayer->setVisible(false);
		mAllRankingLayer->setVisible(true);
		mFBBG->setVisible(false);
		mAllBG->setVisible(true);
		if(mFbTableView) mFbTableView->setTouchEnabled(false);
		if(mAllTableView) mAllTableView->setTouchEnabled(true);

		mSelectedTab = 0;
	}else if(sender->getTag() == 1) {
		mFbRankingLayer->setVisible(true);
		mAllRankingLayer->setVisible(false);
		mFBBG->setVisible(true);
		mAllBG->setVisible(false);
		if(mFbTableView) mFbTableView->setTouchEnabled(true);
		if(mAllTableView) mAllTableView->setTouchEnabled(false);

		mSelectedTab = 1;
	}else {
		return;
	}
}

#define CELL_HEIGHT 80.0

CCSize RankingView::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(mAllTableView->getContentSize().width, CELL_HEIGHT);
}

CCTableViewCell* RankingView::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	//HighScoreCell* cell = (HighScoreCell*)table->dequeueCell();
	HighScoreCell* cell = (HighScoreCell*)table->cellAtIndex(idx);
	m_util->m_call = false;
	if (cell == NULL) {
		cell = new HighScoreCell();
		cell->setContentSize(CCSizeMake(table->getContentSize().width, 80));
		
		if(table->getTag() == FACEBOOK_TABLE_TAG) {
			UserInfo *userInfo = &mFacebookRanks[idx];
			cell->setData(userInfo, idx);
			if(userInfo->getFacebookId() == AGApplication::GetInstance()->getUserInfo()->getFacebookId())
			{
				cell->isMyScore(true);
			}

		}
		else if (table->getTag() == ALL_TABLE_TAG) {
			cell->setData(&mAllRanks[idx], idx);
			if(idx == 0) {
				cell->isMyScore(true);
			}
		}

		/*UserInfo& data = mFacebookRanks[idx];
		cell->setData(&data, idx);*/
	}

	m_util->m_call = false;

	return cell;
}


#define MAX_ALLRANKS 500

unsigned int RankingView::numberOfCellsInTableView(CCTableView *table)
{
	if(table->getTag() == FACEBOOK_TABLE_TAG) {
		return mFacebookRanks.size();
	}else {
		return mAllRanks.size();
	}
}

void RankingView::tableCellTouched(CCTableView* table, CCTableViewCell* cell){

}

void RankingView::scrollViewDidScroll(CCScrollView* view)
{

	CCLog("offset %f, height %f , size %f", view->getContentOffset().y,view->getContentSize().height, view->getContainer()->getContentSize().height);


	if (view->getTag() == FACEBOOK_TABLE_TAG) {
		CCLog("FACEBOOK_TABLE_TAG offset %f, height %f , size %f", view->getContentOffset().y,view->getContentSize().height, view->getContainer()->getContentSize().height);
		cellLastIndex = floor((view->getContentSize().height + view->getContentOffset().y)/80);
		CCLOG("cellLastIndex = %d",cellLastIndex);
	}

	if(view != mAllTableView) {
		return;
	}


	if(isListFull) {
		return;
	}

	if(HHNetwork::GetInstance()->getNetworkStatus() == false) {
		return;
	}

	if(view->getContentOffset().y >= 0 && isPaging == false) {

		isPaging = true;
		CCLog("current Page - %d",this->pageIndex );
		HiHighConnector::sharedConnector()->allRankList(AGApplication::GetInstance()->getUserInfo(), this->pageIndex, this,httpresponse_selector(RankingView::onAllRanksRequestCompleted));
	}
}
void RankingView::scrollViewDidZoom(CCScrollView* view)
{

}


//void RankingView::initData()
//{
//    mFacebookRanks.clear();
//    
//    /*UserInfo *localUser = new UserInfo();
//     localUser->setFacebookId("LocalUser");
//     StageScoreInfo localUserInfo;
//     localUserInfo.setStage(AGApplication::GetInstance()->getCurrentStage());
//     localUserInfo.setMaxCombo(AGApplication::GetInstance()->getMaxCombo());
//     localUserInfo.setMaxScore(AGApplication::GetInstance()->getMaxCombo() * AGApplication::GetInstance()->getGoldAmount());
//     localUser->setStageScoreInfo(localUserInfo);*/
//    
//    mFacebookRanks.push_back(*AGApplication::GetInstance()->getUserInfo());
//    
//    if(AGApplication::GetInstance()->getGameData()->getCurrentStage() != 1 ) {
//        return;
//    }
//    
//}

bool CompareObject(UserInfo first, UserInfo second )
{
	// vector 내에서 앞에 놓이는 녀석은 뒤에 놓이는 녀석보다 다음과 같은 조건을 만족한다
	return first.getEndlessScoreInfo().getMaxScore() > second.getEndlessScoreInfo().getMaxScore();

	// 만약 vector의 index 0부터 끝까지 getInt()의 값에 따라 오름차순이 되게 하려면
	// return first.getInt() < second.getInt(); 가 되야 할 것이다.
}
void RankingView::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {



	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	//CCMessageBox(resStr.c_str(), "response");
	if(resStr.compare("") == 0) return;

	//string temp = "[{\"id\":2,\"facebookId\":\"1234\",\"currentStage\":1,\"gold\":10000,\"totalGold\":100000,\"lastVisitDate\":1403584385855,\"registDate\":1403584386145,\"userUpgradeInfoList\":null,\"endlessScoreInfo\":{ \"id\":1, \"stage\":-1, \"maxCombo\":123, \"maxScore\":123123, \"member\":{ \"id\":5, \"facebookId\":\"123123\", \"currentStage\":0, \"gold\":11200, \"totalGold\":46200, \"lastVisitDate\":null, \"registDate\":1403599741464, \"userUpgradeInfoList\":null, \"endlessScoreInfo\":null }, \"registDate\":1403599750347 }}, {\"id\":5,\"facebookId\":\"localUser\",\"currentStage\":0,\"gold\":11200,\"totalGold\":46200,\"lastVisitDate\":null,\"registDate\":1403599741464,\"userUpgradeInfoList\":null,\"endlessScoreInfo\":{ \"id\":2, \"stage\":-1, \"maxCombo\":456, \"maxScore\":456456, \"member\":{ \"id\":5, \"facebookId\":\"456456\", \"currentStage\":0, \"gold\":11200, \"totalGold\":46200, \"lastVisitDate\":null, \"registDate\":1403599741464, \"userUpgradeInfoList\":null, \"endlessScoreInfo\":null }, \"registDate\":1403599750347 }}, {\"id\":9,\"facebookId\":\"test1234\",\"currentStage\":1,\"gold\":8000000,\"totalGold\":100000000,\"lastVisitDate\":1403663429554,\"registDate\":1403661604986,\"userUpgradeInfoList\":null,\"endlessScoreInfo\":{ \"id\":3, \"stage\":-1, \"maxCombo\":789, \"maxScore\":789789, \"member\":{ \"id\":5, \"facebookId\":\"789789\", \"currentStage\":0, \"gold\":11200, \"totalGold\":46200, \"lastVisitDate\":null, \"registDate\":1403599741464, \"userUpgradeInfoList\":null, \"endlessScoreInfo\":null }, \"registDate\":1403599750347 }}]";
	vector<UserInfo>* list = HiHighJsonConvecter::sharedJsonConverter()->convertScoreInfoList(resStr);
	if(list == NULL) return;
	CCLog("convertScoreInfoList after ");

//	static int indexI = 1;
//	vector<UserInfo>* list = new vector<UserInfo>();
//
//	UserInfo testInfo;
//	StageScoreInfo testScoreInfo;
//	int size = indexI + 11;
//	for(indexI ; indexI < size; ++indexI) {
//
//		testScoreInfo.setMaxCombo(rand() % 300);
//		testScoreInfo.setMiter(rand() % 1000);
//		testScoreInfo.setRank(indexI);
//
//
//		testInfo.setCurrentStage(-1);
//		testInfo.setEndlessScoreInfo(testScoreInfo);
//		testInfo.setFacebookId(AGApplication::GetInstance()->getUserInfo()->getFacebookId());
//		testInfo.setId(indexI);
//
//		list->push_back(testInfo);
//	}

	mFacebookRanks.clear();
	mFbids.clear();

	for(int indexI = 0 ; indexI < list->size(); ++indexI) {
		UserInfo user = list->at(indexI);
		mFacebookRanks.push_back(user);
		mFbids.push_back(user.getFacebookId());
		//mAllRanks.push_back(list->at(indexI));
	}

	delete list;

	sort(mFacebookRanks.begin(), mFacebookRanks.end(), CompareObject);
	if (mFbTableView != NULL)  mFbTableView->reloadData();
	//mAllTableView->reloadData();
	//doAnimationResult();

	CCLog("doAnimationResult after ");

	//	CCSprite* profileImage;
	//AGUtil::create(this, callfunc_selector(RankingView::callbackTest));
	////	AGUtil::setTarget(this, callfunc_selector(RankingView::callbackTest));
	//	string fbid;
	//
	//	for (int indexI = 0; indexI < mFacebookRanks.size(); indexI++) {
	//		UserInfo& data = mFacebookRanks[indexI];
	//		fbid = data.getFacebookId();
	//
	//		profileImage = AGUtil::createSpriteFromUrl(fbid.c_str(), AGUtil::createFBProfileUrl(fbid.c_str()).c_str());
	//		profileImage->setAnchorPoint(ccp(0, 0));
	//		//		profileImage->setPosition(ccp(124, size.height - ((120*indexI)+120)));
	//
	//	}
}

void RankingView::onSendScoreCompleted(CCHttpClient* client, CCHttpResponse* response) {

}


void RankingView::fbInviteBtnListener(CCObject* pSender)
{
	if(!isFacebookConnected) {
		showAlertRankingView("Facebook NO", "Facebook 로그인 하여야 친구 초대를 할 수 있습니다.");
		return;
	}

	if (!HHNetwork::GetInstance()->getNetworkStatus()) {
		string message = "Please retry later";
		HHAlert* alert = HHAlert::create("Network Error", message.c_str(), NULL, "OK");
		alert->show();
		return;
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	FacebookInterface::inviteFriends(Facebook::INVITE_REQUEST,"inviteFriends");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	FacebookInterfaceiOS::sharedFacebookiOS().inviteFriends(Facebook::INVITE_REQUEST, "inviteFriends");
#endif
}


void RankingView::fbShareBtnListener(CCObject *pSender)
{
	if(!isFacebookConnected) {
		showAlertRankingView("Facebook NO", "Facebook 로그인 하여야 공유할 수 있습니다.");
		return;
	}
	
	if (!HHNetwork::GetInstance()->getNetworkStatus()) {
		string message = "Please retry later";
		HHAlert* alert = HHAlert::create("Network Error", message.c_str(), NULL, "OK");
		alert->show();
		return;
	}
	
	if (mFacebookRanks.size() == 0) {
		string message = "Please retry later";
		HHAlert* alert = HHAlert::create("Network Error", message.c_str(), NULL, "OK");
		alert->show();
		return;
	}

	mCompleteCount = 0;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	mActivityIndicator = CCActivityIndicator::create();
	mActivityIndicator->setPosition(ccp(size.width/2-30,size.height/2-120));
	this->addChild(mActivityIndicator);


	if (mActivityIndicator->isAnimating()) {
		mActivityIndicator->stopAnimating();
	}else{
		mActivityIndicator->startAnimating();
	}


//	this->scheduleOnce(schedule_selector(RankingView::drawRanking), 2.0);
	drawRanking();
}

void RankingView::screenCaptureCallback()
{
	CCLOG("screenCaptureCallback");
	resizeForCapture(false);
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCLayer *layer = (CCLayer*)this->getParent()->getChildByTag(115577);
	layer->setAnchorPoint(ccp(0.5, 0.5));
	
	CCRenderTexture* texture = CCRenderTexture::create(size.width + layer->getContentSize().width, layer->getContentSize().height);
	texture->setPosition(layer->getPosition());

	texture->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	texture->end();

	std::string dir =  CCFileUtils::sharedFileUtils()->getWritablePath();
	dir.append("screenshot.jpg");

	if (texture->saveToFile("screenshot.jpg", kCCImageFormatJPEG)) {
		CCLOG("screen captured");
		CCLOG("screen path = %s", dir.c_str());
	}else{
		CCLOG("screen no captured");
	}

	//	CCLayer* tempLayer = mFbRankingLayer->getChildByTag(579579);


	resizeForCapture(true);
	if (mActivityIndicator->isAnimating()) {
		mActivityIndicator->stopAnimating();
	}else{
		mActivityIndicator->startAnimating();
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	mFbRankingLayer->removeChildByTag(579579);
	mFbTableView->setVisible(true);

	FacebookInterface::photoFeedShared(Facebook::SHARED_REQUEST,_userScore.c_str());
	//	FacebookInterface::publishFeed(3,_userScore.c_str());
	CCLOG("FacebookInterface::photoFeedShared!!!!!!!!!!!!!!!!!!");
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	FacebookInterfaceiOS::sharedFacebookiOS().publishFeed(Facebook::SHARED_REQUEST,_userScore.c_str());
#endif
}

void RankingView::resizeForCapture(bool isOriginal)
{
	float scaleY;
	float tableHeight;
	float bgPositionY;
	
	CCPoint lineCcp;
	CCPoint fbMenuCcp;
	CCPoint fbTableCcp;
	
	CCSprite* line = (CCSprite*)mFbRankingLayer->getChildByTag(4556);
	CCMenu *fbMenu = (CCMenu *)mFbRankingLayer->getChildByTag(2556);
	
	if (!isOriginal) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
		NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
		[notiCenter postNotificationName:@"removeBannerNotification" object:nil];
#endif
		scaleY = 1.17;
		bgPositionY = -90;
		
		lineCcp = ccp(line->getPositionX(),line->getPositionY()-75);
		fbMenuCcp = ccp(fbMenu->getPositionX(),fbMenu->getPositionY()-85);
		fbTableCcp = ccp(mFbTableView->getPositionX(),mFbTableView->getPositionY()-35);
		tableHeight = mFbTableView->getContentSize().height+50;
	}else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
		NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
		[notiCenter postNotificationName:@"showBannerNotification" object:nil];
#endif
		scaleY = 1.0;
		bgPositionY = 90;
		
		lineCcp = ccp(line->getPositionX(),line->getPositionY()+75);
		fbMenuCcp = ccp(fbMenu->getPositionX(),fbMenu->getPositionY()+85);
		fbTableCcp = ccp(mFbTableView->getPositionX(),mFbTableView->getPositionY()+35);
		tableHeight = mFbTableView->getContentSize().height-50;
	}

	CCLOG("before this width = %f, height = %f",this->getContentSize().width,this->getContentSize().height);
	
	mAllBG->setScaleY(scaleY);
	mFBBG->setScaleY(scaleY);
	mAllBG->setPosition(ccp(mAllBG->getPositionX(),mAllBG->getPositionY()+bgPositionY));
	mFBBG->setPosition(ccp(mFBBG->getPositionX(),mFBBG->getPositionY()+bgPositionY));
	
	
	
	line->setPosition(lineCcp);
	fbMenu->setPosition(fbMenuCcp);
	mFbTableView->setPosition(fbTableCcp);
	mFbTableView->setContentSize(CCSizeMake(mFbTableView->getContentSize().width,  tableHeight));
	CCLOG("after this width = %f, height = %f",this->getContentSize().width,this->getContentSize().height);

}

void RankingView::facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message)
{
	CCLog("facebookErrorCallback index = %d", requestType);
	CCLog("Error message = %s",message.c_str());
	
	switch (requestType) {
		case Facebook::LOGIN_REQUEST :
		{
			
		}
			break;
		case Facebook::FRIENDS_REQUEST:
		{
			
		}
			break;
		case Facebook::LOGOUT_REQUEST:
		{
			
		}
		break;
		default:
			break;
	}
	
	HHAlert* alert = HHAlert::create(NULL, message.c_str(), NULL, "OK");
	alert->show();
}


void RankingView::facebookCallback(Facebook::REQUEST_TYPE cbIndex, string params)
{
	reqType = cbIndex;

	RankingView* that = (RankingView*)AGApplication::GetInstance()->getObjectMap("RANKING_VIEW");


	if (cbIndex == Facebook::SHARED_CANCEL) {
		that->mActivityIndicator->stopAnimating();
		return;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	that->scheduleOnce(schedule_selector(RankingView::delayFunctionRankingView), 1.0);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	that->scheduleOnce(schedule_selector(RankingView::delayFunctionRankingView), 1.0);
#endif

}

void RankingView::delayFunctionRankingView()
{
	string title = "";
	string message = "";

	switch (reqType) {
		case Facebook::INVITE_REQUEST:
			title = "Completed Successfully";
			message = "The request has been sent to your friend";
			break;
		case Facebook::SHARED_REQUEST:
			title = "Completed Successfully";
			message = "Your Score has been posted to Facebook.";
			break;
		case Facebook::NONE:

			break;
		case Facebook::SHARED_CANCEL :
			CCLOG("SHARED_CANCEL");
			break;
		default:
			break;
	}

	if (title.compare("") != 0 && message.compare("") != 0) {
		if (reqType == Facebook::SHARED_REQUEST) {

			mActivityIndicator->stopAnimating();
		}

		showAlertRankingView(title, message);
	}
}

void RankingView::showAlertRankingView(string title, string message)
{

	if (mAlert != NULL && mAlert->isShow()) {
		mAlert->close(NULL);
	}

	mAlert = HHAlert::create(title.c_str(), message.c_str(), NULL, "OK");
	//_backAlert->okayBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MainMenuScene::backBtnOkListener), CCControlEventTouchUpInside);

	mAlert->show();
}
void RankingView::drawRanking()
{
	CCLayer* layer;


	CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->getParent()->setAnchorPoint(CCPointZero);

	CCLayer* ttlayer = CCLayer::create();
	ttlayer->setTag(115577);
	ttlayer->setContentSize(CCSizeMake(size.width, size.height));
	ttlayer->setPosition(ccp(size.width,0));

	CCSprite* bg = CCSprite::createWithSpriteFrameName("score_bg_facebook_02.png");
	bg->setPosition(ccp(ttlayer->getContentSize().width/2, ttlayer->getContentSize().height/2));
	ttlayer->addChild(bg);

	int loopCount = 0;
	mFacebookRanks.size() > 13 ? loopCount = 13 : loopCount = mFacebookRanks.size();

	for (int indexI = 0; indexI < loopCount; indexI++) {
		layer = CCLayer::create();

		UserInfo& data = mFacebookRanks[indexI];
		string fbId = (data.getFacebookId().compare("") != 0) ? data.getFacebookId() : "localUser" ;
		m_util->m_call = true;

		HighScoreCell* cell = new HighScoreCell();

		cell->setAnchorPoint(CCPointZero);
		cell->setPosition(ccp(20, size.height -( (80 * indexI) + 140)));
		cell->setContentSize(CCSizeMake(cell->getContentSize().width, 80));

		cell->setData(&data, indexI,true);

		ttlayer->addChild(cell);
	}
	//	CCLayerColor* tempLayer = CCLayerColor::create(ccc4(255,255,0,255));
	//	tempLayer->setContentSize(this->getContentSize().width, this->getContentSize().height - 60));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	CCLayer* tempLayer = CCLayerColor::create();
	tempLayer->setContentSize(CCSizeMake(mFbRankingLayer->getContentSize().width, mFbRankingLayer->getContentSize().height - 110));
	tempLayer->setPosition(0,mFbRankingLayer->getContentSize().height/2 - 150);
	tempLayer->setTag(579579);

	CCLOG("cellLastIndex = %d",cellLastIndex);

	int loopIndex = 0;
	mFacebookRanks.size() > 4 ? loopIndex = cellLastIndex-4 : loopCount = 0;

	for (int indexI = loopIndex; indexI < cellLastIndex; indexI++) {
		UserInfo& data = mFacebookRanks[indexI];
		string fbId = (data.getFacebookId().compare("") != 0) ? data.getFacebookId() : "localUser";

		HighScoreCell* cell = new HighScoreCell();

		cell->setAnchorPoint(CCPointZero);
		cell->setPosition(ccp(0, size.height -( (80 * indexI) + (mFbRankingLayer->getContentSize().height + 330))));
		cell->setContentSize(CCSizeMake(cell->getContentSize().width, 80));

		cell->setData(&data, indexI);

		tempLayer->addChild(cell);
	}

	mFbRankingLayer->addChild(tempLayer);
	mFbTableView->setVisible(false);
#endif

	CCLOG("end for!!!!!!!!!!!!!!!!!!");

	this->getParent()->addChild(ttlayer);
	this->getParent()->setAnchorPoint(ccp(0.5,0.5));

	isDrawComplete = true;
}

void RankingView::loadingComplete(CCNode* obj)
{

	CCLOG("loadingComplete = %s", ((string*)obj->getUserData())->c_str());
	
	string* fbId = ((string*)obj->getUserData());

	if(std::find(mFbids.begin(), mFbids.end(), fbId->c_str())!=mFbids.end()){
		// Find the item
		CCLOG("mFacebookRanks.mCompleteCount = %d", mCompleteCount);
		mCompleteCount++;
		delete fbId;
		
		if (mFacebookRanks.size() - 1 <= mCompleteCount) {
			
			this->schedule(schedule_selector(RankingView::checkProfileLoding),1.0);

		}
	}else{
		CCLOG("NON FIND");
	}
}

void RankingView::checkProfileLoding(float dt)
{
	if (isDrawComplete) {

		isDrawComplete = false;
		unschedule(schedule_selector(RankingView::checkProfileLoding));
		mActivityIndicator->stopAnimating();
		screenCaptureCallback();
	}
}




void RankingView::onAllRanksRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {


	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr.compare("") == 0 ) {
		return;
	}

	CCLog("dddd %s", resStr.c_str());

	vector<UserInfo>* list = HiHighJsonConvecter::sharedJsonConverter()->convertScoreInfoList(resStr);

	if(list == NULL) return;
/* test code start */
//	static int indexI = 1;
//	vector<UserInfo>* list = new vector<UserInfo>();
//
//	UserInfo testInfo;
//	StageScoreInfo testScoreInfo;
//	int size = indexI + 11;
//	for(indexI ; indexI < size; ++indexI) {
//
//		testScoreInfo.setMaxCombo(rand() % 300);
//		testScoreInfo.setMiter(rand() % 1000);
//		testScoreInfo.setRank(indexI);
//
//
//		testInfo.setCurrentStage(-1);
//		testInfo.setEndlessScoreInfo(testScoreInfo);
//		testInfo.setFacebookId(AGApplication::GetInstance()->getUserInfo()->getFacebookId());
//		testInfo.setId(indexI);
//
//		list->push_back(testInfo);
//	}

/* test code end */

	if(list->size() != 11) {
		isListFull = true;
	}

	int returnListSize = list->size() - 1;


	for(int indexI = 0 ; indexI < list->size(); ++indexI) {

		if(this->pageIndex != 0 && indexI == 0)
			continue;

		if(mAllRanks.size() != 0 && mAllRanks[0].getId() == list->at(indexI).getId()) continue;

		UserInfo user = list->at(indexI);
		mAllRanks.push_back(user);
	}

	delete list;


	this->pageIndex++;
	this->isPaging = false;

	if(mAllRanks.size() > MAX_ALLRANKS) {
		isListFull = true;
	}
	if (mAllTableView != NULL && pageIndex != 0) {

		mAllTableView->reloadData();
		mAllTableView->setContentOffset(ccp(0, -(CELL_HEIGHT) * returnListSize));

	} else {
		mAllTableView->reloadData();
	}
}

void RankingView::goToConnect(CCObject* object)
{
	CCScene *home = MainMenuScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, home);
	CCDirector::sharedDirector()->replaceScene(transition);
}
