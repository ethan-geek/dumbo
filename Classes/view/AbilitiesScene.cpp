///////////////////////////////////////////////////////////
//  AbilitiesScene.cpp
//  Implementation of the Class AbilitiesScene
//  Created on:      19-3-2014 ø¿¿¸ 11:55:01
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "AbilitiesScene.h"
#include "MainMenuScene.h"
#include "IAPScene.h"
#include <string>

#include "../dao/HiHighDao.h"
#include "./GameLoadingScene.h"
#include "../model/UserInfo.h"

#include "../model/ItemInfo.h"

#include "../common/XmlLoader.h"
#include "../common/XmlCreator.h"

#include "../common/HHButton.h"
#include "../helper/AndroidHelper.h"

#include "../network/HHNetwork.h"

#define ABILITIES_TABLE_CELL_WIDTH	m_winSize.width
#define ABILITIES_TABLE_CELL_HEIGHT 200.0f

#define ABILITIES_TABLE_TOP_POSITION        m_winSize.height - 146
#define ABILITIES_TABLE_BOTTOM_POSITION     256


AbilitiesScene::AbilitiesScene(){

}



AbilitiesScene::~AbilitiesScene(){

}

CCScene* AbilitiesScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	AbilitiesScene *layer = AbilitiesScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	CCLog("scene");

	// return the scene
	return scene;
}

bool AbilitiesScene::init()
{
    
	//////////////////////////////
	// 1. super init first
	if ( !CCLayerColor::initWithColor(ccc4(10, 10, 10, 255)) )
	{
		return false;
	}

	preparedAbilitiList();
	this->setKeypadEnabled(true);

	m_winSize = CCDirector::sharedDirector()->getWinSize();
	m_application = AGApplication::GetInstance();
	m_userInfo = m_application->getHiHighDao()->selectUserInfo();


	configureNavigatorView();


	pTableView = CCTableView::create(this, CCSizeMake(m_winSize.width, m_winSize.height - 150 - ABILITIES_TABLE_BOTTOM_POSITION));
    pTableView->setAnchorPoint(ccp(0, 0));
    pTableView->setPosition(ccp(0, ABILITIES_TABLE_BOTTOM_POSITION));
	pTableView->setDelegate(this);
	pTableView->setDirection(kCCScrollViewDirectionVertical);
	pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	addChild(pTableView);

	//pTableView->reloadData();
    
    CCMenuItemLabel * backBtn = AGUtil::createLabelButton("B A C K", TEXT_FONT_NORMAL, "", "btn_bg_02.png", 0,
                                                          this, menu_selector(AbilitiesScene::backClickListener), BUTTON_TEXT_ALIGN_CENTER);
    backBtn->setOpacity(255 * 0.6);
    
    CCMenuItemLabel * startBtn = AGUtil::createLabelButton("P L A Y", TEXT_FONT_NORMAL, "", "btn_bg_02.png", 0,
                                                          this, menu_selector(AbilitiesScene::startClickListener), BUTTON_TEXT_ALIGN_CENTER);
    
    CCMenu *startMenu = CCMenu::create(backBtn, startBtn, NULL);
    startMenu->setPosition(ccp(m_winSize.width / 2, ABILITIES_TABLE_BOTTOM_POSITION - 70));
    startMenu->alignItemsHorizontallyWithPadding(30);
    this->addChild(startMenu);
    
	m_selectedCell = NULL;


	return true;
}

void AbilitiesScene::onEnter()
{
	CCLayer::onEnter();
	CCLog("AbilitiesScene::onEnter");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    android_removeBanner();
    android_showBanner();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
    [notiCenter postNotificationName:@"showBannerNotification" object:nil];
#endif
    
}
void AbilitiesScene::onExit()
{
	CCLayer::onExit();
	CCLog("AbilitiesScene::onExit");
}
void AbilitiesScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCLog("AbilitiesScene::onEnterTransitionDidFinish");

	ostringstream os;
	os << m_application->getUserInfo()->getGold();
	string temp = os.str();
	os.clear();
	AGUtil::calc3point(temp);
	m_hasCoin->setString(temp.c_str());

}

void AbilitiesScene::onExitTransitionDidStart()
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
    android_removeBanner();
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    NSNotificationCenter* notiCenter = [NSNotificationCenter defaultCenter];
    [notiCenter postNotificationName:@"removeBannerNotification" object:nil];
#endif
    CCLayer::onExitTransitionDidStart();

}

void AbilitiesScene::configureNavigatorView() {
    
    CCLabelBMFont *upgradeLabel = CCLabelBMFont::create("U P G R A D E", TEXT_FONT_NORMAL);
    upgradeLabel->setAnchorPoint(CCPointZero);
    upgradeLabel->setPosition(ccp(50, m_winSize.height - 80));
    this->addChild(upgradeLabel);
    
    CCLabelBMFont *descLabel = CCLabelBMFont::create("Add More Time", TEXT_FONT_SMALL);
    descLabel->setScale(1.2);
    descLabel->setAnchorPoint(CCPointZero);
    descLabel->setPosition(ccp(50, m_winSize.height - 120));
    this->addChild(descLabel);
    
    CCMenuItemLabel *jewelCount = AGUtil::createLabelButton("", TEXT_FONT_SMALL, "", "jewel_score_bg.png", 0, this, menu_selector(AbilitiesScene::shopClickListener));
    CCMenu *m = CCMenu::create(jewelCount, NULL);
    m->setPosition(ccp(m_winSize.width - jewelCount->getContentSize().width/2 - 20 , m_winSize.height - 73));
    this->addChild(m);
    
    ///////warning
    bool isConnect = CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT);
    if(isConnect) {
        UserInfo *user = AGApplication::GetInstance()->getUserInfo();
        CCLog("### %s", user->getFacebookId().c_str());
        if(user->getFacebookId() == "529704107141259") m_application->getUserInfo()->setGold(150000);
    }
    
    ostringstream os;
    os << m_application->getUserInfo()->getGold();
    string temp = os.str();
    AGUtil::calc3point(temp);
    m_hasCoin = CCLabelBMFont::create(temp.c_str(), TEXT_FONT_SMALL);
    os.clear();
    m_hasCoin->setAnchorPoint(ccp(1, 0.5));
    m_hasCoin->setPosition(ccp(m_winSize.width - 40, m->getPositionY()));
    this->addChild(m_hasCoin);
    
    
    CCSprite* topLine = CCSprite::createWithSpriteFrameName("sub_titlebar_top.png");
    topLine->setAnchorPoint(ccp(0, 1));
    topLine->setPosition(ccp(0, m_winSize.height - 146));
    this->addChild(topLine);
    
    CCSprite* botttomLine = CCSprite::createWithSpriteFrameName("sub_titlebar_bottom.png");
    botttomLine->setAnchorPoint(ccp(0, 1));
    botttomLine->setPosition(ccp(0, ABILITIES_TABLE_BOTTOM_POSITION));
    this->addChild(botttomLine);
}


void AbilitiesScene::preparedAbilitiList()
{
	m_abilitiesList.clear();
    
	ItemInfo itemInfo;

	xml_document rootDocument;
	unsigned char* rootBuffer = NULL;
	unsigned long bufferSize = 0;

	rootBuffer = CCFileUtils::sharedFileUtils()->getFileData(((string)ITEM_OBJECTS_PATH).c_str(), "rb", &bufferSize);

	rootDocument.load_buffer(rootBuffer, bufferSize);
	delete rootBuffer;
	xml_node rootNode = rootDocument.child("itemObjects");

	for (xml_node itemInfoNode = rootNode.child("item"); itemInfoNode; itemInfoNode = itemInfoNode.next_sibling("item"))
	{
		itemInfo.setName(itemInfoNode.attribute("name").as_string());
		itemInfo.setDescription(itemInfoNode.attribute("description").as_string());
		itemInfo.setIconName(itemInfoNode.attribute("imagePath").as_string());
		itemInfo.setPrice(itemInfoNode.attribute("price").as_int());
		itemInfo.setId(itemInfoNode.attribute("id").as_int());

		m_abilitiesList.push_back(itemInfo);
	}
    
}

//datasource method
void AbilitiesScene::scrollViewDidScroll(CCScrollView* view)
{

}
void AbilitiesScene::scrollViewDidZoom(CCScrollView* view)
{

}

unsigned int AbilitiesScene::numberOfCellsInTableView(CCTableView *table)
{
	return m_abilitiesList.size();
}

CCSize AbilitiesScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(ABILITIES_TABLE_CELL_WIDTH, ABILITIES_TABLE_CELL_HEIGHT);
}

CCTableViewCell* AbilitiesScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    
	CCTableViewCell* cell = table->cellAtIndex(idx);

	if (cell == NULL) {
		cell = new CCTableViewCell();
		cell->autorelease();
		cell->setTag(idx);

		ItemInfo& data = m_abilitiesList[idx];

		CCSprite* item = CCSprite::createWithSpriteFrameName(data.getIconName().c_str());
        //CCSprite *item = CCSprite::createWithSpriteFrameName(data.getIconName().c_str());
		item->setAnchorPoint(ccp(0, 1));
		item->setPosition(ccp(40, 164));
		item->setTag(ITEM_SPRITE_TAG);
		cell->addChild(item);

        
        CCLabelBMFont* descLabel = CCLabelBMFont::create(data.getDescription().c_str(), TEXT_FONT_SMALL);
        descLabel->setScale(0.8);
        descLabel->setAlignment(kCCTextAlignmentLeft);
        descLabel->setAnchorPoint(ccp(0, 1));
        descLabel->setPosition(ccp(196, 164));
        descLabel->setTag(DESCRIPT_LABEL_TAG);
        cell->addChild(descLabel);

		UserUpgradeInfo* tempUpgradeInfo = m_userInfo->getUserUpgradeInfo(data.getName());
		if (tempUpgradeInfo == NULL)
		{
			setUpgradeInfo(cell, false);
			tempUpgradeInfo = m_userInfo->getUserUpgradeInfo(data.getName());
		}
		int upgradeCount = (tempUpgradeInfo->getUpgradeCount() > 0) ? tempUpgradeInfo->getUpgradeCount() : 0;

		CCLog("%s upgradeCount = %d", tempUpgradeInfo->getItemInfo()->getName().c_str(), tempUpgradeInfo->getUpgradeCount());
        
        displayUpgradeGage(cell, upgradeCount);


        CCSprite *upgradeBtn = CCSprite::createWithSpriteFrameName("upgrade_price_bg.png");
        upgradeBtn->setAnchorPoint(ccp(0, 1));
        upgradeBtn->setPosition(ccp(330, 78));
        upgradeBtn->setTag(UPGRADE_BUTTON_TAG);
        cell->addChild(upgradeBtn);
        
        CCLabelBMFont *priceLabel = CCLabelBMFont::create("0", TEXT_FONT_SMALL, 230, kCCTextAlignmentRight);
        priceLabel->setAnchorPoint(ccp(1, 1));
        priceLabel->setPosition(ccp(upgradeBtn->getPositionX() + upgradeBtn->getContentSize().width - 30, upgradeBtn->getPositionY() - 3));
        priceLabel->setTag(PRICE_LABEL_TAG);
        cell->addChild(priceLabel);

		static char temp[8];
		sprintf(temp, "%d", data.getUpgradePrice(upgradeCount));
		string price = temp;
		AGUtil::calc3point(price);
        priceLabel->setString(price.c_str());
        
        checkUpgradeAvailable(cell, data.getUpgradePrice(upgradeCount), upgradeCount);

	}
	else
	{
        ItemInfo& data = m_abilitiesList[idx];
        
        UserUpgradeInfo* tempUpgradeInfo = m_userInfo->getUserUpgradeInfo(data.getName());
        int upgradeCount = (tempUpgradeInfo->getUpgradeCount() > 0) ? tempUpgradeInfo->getUpgradeCount() : 0;
        
        static char temp[8];
        sprintf(temp, "%d", data.getUpgradePrice(upgradeCount));
        string price = temp;
        AGUtil::calc3point(price);
        CCLabelBMFont *priceLabel = (CCLabelBMFont*)cell->getChildByTag(PRICE_LABEL_TAG);
        priceLabel->setString(price.c_str());
        
        checkUpgradeAvailable(cell, data.getUpgradePrice(upgradeCount), upgradeCount);
	}

	return cell;
}




//delegate method
void AbilitiesScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    HiHighAudio::sharedAudio()->playEffect("button");
    
    ItemInfo itemInfo = m_abilitiesList[cell->getTag()];
    
    CCSprite* sprite = (CCSprite*)cell->getChildByTag(UPGRADE_BUTTON_TAG);
    if(sprite->getOpacity() != 255) {
        this->shopClickListener(NULL);
        
    }else {
        m_selectedCell = cell;
        alert = HHAlert::create(NULL, "UPGRADING THIS ITEM", "OK", "CANCEL");
        CCSprite *img = CCSprite::createWithSpriteFrameName(itemInfo.getIconName().c_str());
        img->setScale(0.7);
        alert->setImage(img);
        alert->show();
        //alert->okayBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(AbilitiesScene::doUpgrade), CCControlEventTouchUpInside);
        alert->okayBtn->setTarget(this, menu_selector(AbilitiesScene::doUpgrade));
    }
}

void AbilitiesScene::doUpgrade(cocos2d::CCObject *obj)
{
    HiHighAudio::sharedAudio()->playEffect("button");
	setUpgradeInfo(m_selectedCell, true);
    
    CCParticleSystem *ptc = CCParticleSystemQuad::create("paticle/score_star2.plist");
    ptc->setSpeed(ptc->getSpeed() * 1.6);
    ptc->setAutoRemoveOnFinish(true);
    ptc->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(ptc, 99);
    
	alert->close(obj);
}

void AbilitiesScene::setUpgradeInfo(CCTableViewCell* cell, bool isBuy)
{
    
	ItemInfo itemInfo = m_abilitiesList[cell->getTag()];
	//	CCTableViewCell* targetCell = (CCTableViewCell*)cell->getChildByTag(cell->getTag());

	UserUpgradeInfo* tempUpgradeInfo = m_userInfo->getUserUpgradeInfo(itemInfo.getName());

	if (tempUpgradeInfo == NULL)
	{
		UserUpgradeInfo* tempUpgradeInfo2;
		tempUpgradeInfo = new UserUpgradeInfo();

		tempUpgradeInfo->setItemInfo(itemInfo);
		tempUpgradeInfo->setUpgradeCount(0);

		m_userInfo->setUserUpgradeInfo(*tempUpgradeInfo);
		tempUpgradeInfo2 = m_userInfo->getUserUpgradeInfo(itemInfo.getName());
		delete tempUpgradeInfo;
		tempUpgradeInfo = tempUpgradeInfo2;
	}
	else
	{
		tempUpgradeInfo->setItemInfo(itemInfo);
		
	}
    
	if (isBuy)
	{
		int tempUpgradeCount = (tempUpgradeInfo->getUpgradeCount() > 0) ? tempUpgradeInfo->getUpgradeCount() : 0;
        
		if (itemInfo.getUpgradePrice(tempUpgradeCount) > m_userInfo->getGold())
		{
			CCLog("Gold Charge");

			AGUtil::alert("Not enough Jewels");
			return;

		}

		tempUpgradeInfo->setUpgradeCount(tempUpgradeInfo->getUpgradeCount() + 1);

		static char temp[8];
		sprintf(temp, "%d", itemInfo.getUpgradePrice(tempUpgradeInfo->getUpgradeCount()));
		string tempStr = temp;
		AGUtil::calc3point(tempStr);
		CCLabelBMFont* priceLabel = (CCLabelBMFont*)cell->getChildByTag(PRICE_LABEL_TAG);
		priceLabel->setString(tempStr.c_str());

		m_userInfo->setGold(m_userInfo->getGold() - (itemInfo.getUpgradePrice(tempUpgradeCount)));

		m_application->getHiHighDao()->updateUpgradeInfo(*tempUpgradeInfo);
		if(m_application->checkFacebook()) {
			HiHighConnector::sharedConnector()->sendUserInfo(m_userInfo, this, httpresponse_selector(AbilitiesScene::onHttpRequestCompleted));
			//HiHighConnector::sharedConnector()->sendUpgradeInfo(tempUpgradeInfo, this , httpresponse_selector(AbilitiesScene::onHttpRequestCompleted));
		}
        
        displayUpgradeGage(cell, tempUpgradeCount+1);
        this->reloadTableView();
	}

	ostringstream os;
	os << m_userInfo->getGold();

	m_hasCoin->setString(os.str().c_str());
	os.clear();
    
//    this->reloadTableView();

}

void AbilitiesScene::backClickListener(CCObject* pSender){

	SceneManager::replaceScene("MainMenuScene");

	/*CCScene* main = MainMenuScene::scene();
	CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
	CCDirector::sharedDirector()->replaceScene(transition);*/
}



void AbilitiesScene::shopClickListener(CCObject* pSender){
	
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey(FACEBOOK_CONNECT)) {
        
        return;
    }
    
    if (!HHNetwork::GetInstance()->getNetworkStatus()) {
    	string message = "Please retry later";
    	HHAlert* alert = HHAlert::create(NULL, message.c_str(), NULL, "OK");
    	alert->show();
    	return;
	}

	CCScene* main = IAPScene::scene();
	main->setUserData(this);

    CCTransitionScene* transition = CCTransitionFlipX::create(0.3, main);

	CCDirector::sharedDirector()->replaceScene(transition);
}

void AbilitiesScene::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {
	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr == "") {
		return;
	}

}


void AbilitiesScene::startClickListener(CCObject* pSender)
{
    HiHighAudio::sharedAudio()->stopMusic();
    HiHighAudio::sharedAudio()->playEffect("button");
    
    AGApplication::GetInstance()->getGameData()->setCurrentStage(-1);
    

	SceneManager::replaceScene("GameLoadingScene");

    /*CCScene *loading = GameLoadingScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, loading);
    CCDirector::sharedDirector()->replaceScene(transition);*/
}


void AbilitiesScene::displayUpgradeGage(CCTableViewCell *cell, int upgradeCount)
{

    CCNode *node = cell->getChildByTag(180);
    if(node) {
        node->removeFromParentAndCleanup(true);
    }
    
    CCLayer *gageLayer = CCLayer::create();
    gageLayer->setTag(180);
    gageLayer->setContentSize(CCSizeMake(400, 17));
    const float margin = 4;
    const float imageWidth = 16;
    float positionX = 0;
    for (int i = 0; i< 20; i++) {
        CCSprite *emptyBox = CCSprite::createWithSpriteFrameName("upgrade_level_dot.png");
        emptyBox->setAnchorPoint(CCPointZero);
        emptyBox->setPosition(ccp(positionX + ((imageWidth + margin) * i), 0));
        if(i >= upgradeCount) {
            emptyBox->setOpacity(255 * 0.3);
        }
        
        gageLayer->addChild(emptyBox);
    }
    gageLayer->setAnchorPoint(ccp(0, 1));
    gageLayer->setPosition(ccp(195, 108));
    cell->addChild(gageLayer);
    
    ItemInfo itemInfo = m_abilitiesList[cell->getTag()];
}

void AbilitiesScene::checkUpgradeAvailable(CCTableViewCell *cell, int price, int count)
{
    
    if (price >  m_userInfo->getGold() || count >= 20) {
        CCSprite *btn = (CCSprite*)cell->getChildByTag(UPGRADE_BUTTON_TAG);
        CCLabelBMFont *label = (CCLabelBMFont*)cell->getChildByTag(PRICE_LABEL_TAG);
        
        if(btn && label) {
            btn->setOpacity(255*0.5);
            label->setOpacity(250*0.5);
        }
        if(count >= 20) label->setString("M A X");
    }
}

void AbilitiesScene::reloadTableView()
{
    if(pTableView == NULL) return;
    CCPoint point = pTableView->getContentOffset();
    pTableView->reloadData();
    pTableView->setContentOffset(point);
}


void AbilitiesScene::keyBackClicked() {

	SceneManager::replaceScene("MainMenuScene");

	/*CCScene* main = MainMenuScene::scene();
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, main);
    CCDirector::sharedDirector()->replaceScene(transition);*/
}
