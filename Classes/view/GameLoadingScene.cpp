//
//  GameLoadingScene.cpp
//  HiHigh
//
//  Created by Jackdaw on 2014. 4. 7..
//
//

#include "GameLoadingScene.h"
#include "../game/GamePlayScene.h"
#include "../network/HHNetwork.h"

bool GameLoadingScene::init()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 255), visibleSize.width, visibleSize.height))
    {
        return false;
    }
	
	

    //CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("character/character.plist");
	AGApplication::GetInstance()->getGameData()->initData();
	AGApplication::GetInstance()->initRand();
	//CCLog("----------------------GameLoadingScene init!!! %.f",AGApplication::GetInstance()->getGameData()->getMiter());

	CCLabelBMFont *loadingMsg = CCLabelBMFont::create("L O A D I N G", TEXT_FONT_NORMAL);
    loadingMsg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 + 50));
    
    mLoadCount = 0;
    mTotalBoxCount = 20;
    
    const float margin = 2;
    const float imageWidth = 16;
    
    float positionX = ((visibleSize.width - ( imageWidth * mTotalBoxCount + ( margin * (mTotalBoxCount - 1) ) ) ) / 2) - (imageWidth + margin);
    for (int i = 0; i< mTotalBoxCount; i++) {
        
        CCSprite *emptyBox = CCSprite::createWithSpriteFrameName("upgrade_level_dot.png");
        emptyBox->setAnchorPoint(CCPointZero);
        emptyBox->setPosition(ccp(positionX + ((margin + imageWidth + margin) * i), visibleSize.height / 2 - 50));
        emptyBox->setOpacity(255*0.3);
        this->addChild(emptyBox);
        
        mLoadingArray.push_back(emptyBox);
    }

    this->addChild(loadingMsg);
    
	
	////testtest
	if(AGApplication::GetInstance()->checkFacebook() && HHNetwork::GetInstance()->getNetworkStatus()) {
		HiHighConnector::sharedConnector()->sendFacebookFriendList(AGApplication::GetInstance()->getUserInfo()->getFacebookId().c_str(), this, httpresponse_selector(GameLoadingScene::onFbRecordRequestCompleted));
		//onFbRecordRequestCompleted(NULL, NULL);
	}
	else {
		this->schedule(schedule_selector(GameLoadingScene::loadResourcesStart), 0.018, mTotalBoxCount-1, 0.3);
	}

    

    return true;
}

CCScene* GameLoadingScene::scene()
{
    CCScene *scene = CCScene::create();
    GameLoadingScene *layer = GameLoadingScene::create();
    scene->addChild(layer);
    return scene;
}

void GameLoadingScene::loadResourcesStart(float dt)
{

    CCSprite *spr =  (CCSprite*)mLoadingArray[mLoadCount];
    spr->setOpacity(255);
    mLoadCount++;
    
    if(mLoadCount == mTotalBoxCount) {
        CCLog("Ended");
        this->scheduleOnce(schedule_selector(GameLoadingScene::loadResourcesEnded), 0.3);
    }
}

void GameLoadingScene::loadResourcesEnded(float dt) {
    

	SceneManager::replaceScene("GamePlayScene");

   /* CCScene* gameScene = GamePlayScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, gameScene);
    CCDirector::sharedDirector()->replaceScene(transition);*/
    

}


void GameLoadingScene::onFbRecordRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {


	////testtest
	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		this->schedule(schedule_selector(GameLoadingScene::loadResourcesStart), 0.018, mTotalBoxCount-1, 0.3);
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr.compare("") == 0) {
		this->schedule(schedule_selector(GameLoadingScene::loadResourcesStart), 0.018, mTotalBoxCount-1, 0.3);
		return;
	}

	CCLog("onFbRecordRequestCompleted %s", resStr.c_str());
	vector<UserInfo>* list = HiHighJsonConvecter::sharedJsonConverter()->convertScoreInfoList(resStr);


	//test start
	/*vector<UserInfo>* list = new vector<UserInfo>();
	
	char temp[10];
	for(int indexI = 0 ; indexI < 4;  ++indexI) {
		list->push_back(UserInfo());

		sprintf(temp, "%d%d%d", indexI+1, indexI+1, indexI+1);

		list->at(indexI).setName(temp);
		list->at(indexI).getEndlessScoreInfo().setMiter((indexI+1)*200);
	}*/
	//test end
	CCLog("onFbRecordRequestCompleted %d", list->size());

	AGApplication::GetInstance()->getGameData()->setFbFriendRecordList(list);
	delete list;


	this->schedule(schedule_selector(GameLoadingScene::loadResourcesStart), 0.018, mTotalBoxCount-1, 0.3);

}