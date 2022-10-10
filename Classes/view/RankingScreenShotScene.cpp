/*
 * RankingScreenShotScene.cpp
 *
 *  Created on: 2014. 10. 16.
 *      Author: geek
 */

#include "RankingScreenShotScene.h"
#include "../model/UserInfo.h"
#include "../common/HiHighConnector.h"
#include "RankingView.h"

/* Disabled class
 * Disabled class
 * Disabled class
 * Disabled class
 * Disabled class
 */

RankingScreenShotScene::RankingScreenShotScene(){
	// TODO Auto-generated constructor stub
}

RankingScreenShotScene::~RankingScreenShotScene() {
	// TODO Auto-generated destructor stub
}

CCScene* RankingScreenShotScene::scene(vector<UserInfo> scoreDatas, RankingView* ranking)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	//	CCLOG("_scoreDatas size 1111111 = %d",scoreDatas.size());

	RankingScreenShotScene *layer = RankingScreenShotScene::create();
	layer->_scoreDatas = scoreDatas;
	layer->_profileDatas.clear();
	layer->rankingView = ranking;
	layer->setTag(99999999999);
	//layer->retain();
	layer->drawRanking();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool RankingScreenShotScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(50,159,222,255)) )
	{
		return false;
	}

	//	_profileDatas.clear();

	_winSize = CCDirector::sharedDirector()->getWinSize();

	CCLOG("_winSize width = %f", _winSize.width );
	CCLOG("_winSize height = %f", _winSize.height );

	return true;
}
void RankingScreenShotScene::drawRanking()
{
	CCLayer* layer;
	CCSprite* bg = NULL;
	CCLabelBMFont* seqLabel = NULL;
	CCSprite* profileImage;
	CCLabelBMFont* nameLabelBM;
	CCLabelTTF* nameLabelTTF;
	CCLabelBMFont* pointLabel;
	CCLabelBMFont* comboLabel;
	CCLabelBMFont* pointWith;
	CCLabelBMFont* combo;
	//	UserInfo* data;

	//	string fbId = "Park Byung Eun";
	//	string fbId = "";

	CCLOG("_scoreDatas.size() = %d", _scoreDatas.size());

	for (int indexI = 0; indexI < _scoreDatas.size(); indexI++) {
		layer = CCLayer::create();

		UserInfo& data = _scoreDatas[indexI];
		string fbId = (data.getFacebookId().compare("") != 0) ? data.getFacebookId() : "localUser" ;

		bg = CCSprite::createWithSpriteFrameName("cell_bg_03.png");
		bg->setAnchorPoint(CCPointZero);
		bg->setPosition(ccp(20, _winSize.height -( (120 * indexI) + 120)));

		layer->addChild(bg);
		layer->setContentSize(CCSizeMake(this->getContentSize().width, 118)) ;

		seqLabel = CCLabelBMFont::create("", TEXT_FONT_SMALL, 40);

		seqLabel->setAnchorPoint(ccp(0, 0.5));
		seqLabel->setPosition(ccp(50,_winSize.height - ((120*indexI)+70)));

		layer->addChild(seqLabel);

		ostringstream os;
		os << indexI + 1;
		os << ".";
		seqLabel->setString(os.str().c_str());
		os.clear();


		if(AGApplication::GetInstance()->checkFacebook()) {

			profileImage = AGUtil::createSpriteFromUrl(fbId.c_str(), AGUtil::createFBProfileUrl(fbId.c_str()).c_str());
			profileImage->setAnchorPoint(ccp(0, 0));
			profileImage->setPosition(ccp(124, _winSize.height - ((120*indexI)+120)));
			_profileDatas.push_back(profileImage);
		}
		else {
			profileImage = CCSprite::createWithSpriteFrameName("profile_bg_108.png");
			profileImage->setAnchorPoint(ccp(0, 0));
			profileImage->setPosition(ccp(124, _winSize.height - ((120*indexI)+3)));
			profileImage->setScale(0.9);
			CCSprite* profile = CCSprite::createWithSpriteFrameName("profile_pic_none.png");
			profile->setScale(0.9);
			profileImage->addChild(profile);
			profile->setPosition(ccp(profileImage->getContentSize().width/2, profileImage->getContentSize().height/2));
		}

		layer->addChild(profileImage);


		HiHighConnector* conn = HiHighConnector::sharedConnector();
		if(AGApplication::GetInstance()->checkFacebook()
				&& AGUtil::isEnglish(conn->getFBName(fbId)) == false ) {

			nameLabelTTF = CCLabelTTF::create(conn->getFBName(fbId).c_str(), "Arial", 30);

			nameLabelTTF->setAnchorPoint(ccp(0, 1));
			nameLabelTTF->setPosition(ccp(244, _winSize.height - ((120*indexI)+58-16)));
			layer->addChild(nameLabelTTF);
		}
		else {
			//    		isEnglish
			if(AGApplication::GetInstance()->checkFacebook()) {
				nameLabelBM = CCLabelBMFont::create(conn->getFBName(fbId).c_str(), TEXT_FONT_NORMAL, 1000);
			}
			else {
				nameLabelBM = CCLabelBMFont::create("Unknown Player", TEXT_FONT_NORMAL, 1000);
			}

			nameLabelBM->setAnchorPoint(ccp(0, 1));
			nameLabelBM->setPosition(ccp(244, _winSize.height - ((120*indexI)+58-16)));
			layer->addChild(nameLabelBM);
		}

		//		if (_scoreDatas.size()-1 <= indexI) {
		//			CCLOG("_scoreDatas.size() <= indexI");
		//
		//		}
		this->addChild(layer);
	}
	CCLOG("end for!!!!!!!!!!!!!!!!!!");

	checkProfileLoding();

}


void RankingScreenShotScene::checkProfileLoding()
{
	int completeCount = 0;

	while(true)
	{
		CCSprite* pf = _profileDatas[completeCount];

		if (pf->getTag() == 1) {
			if (_scoreDatas.size()-1 <= completeCount) {
				CCLOG("CallBack RankinView");
				rankingView->screenCaptureCallback();
				break;
			}
			completeCount += 1;
			CCLOG("Complete Profile = %d", completeCount);
		}
	}
}
