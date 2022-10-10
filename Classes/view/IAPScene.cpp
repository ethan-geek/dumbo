///////////////////////////////////////////////////////////
//  IAPScene.cpp
//  Implementation of the Class IAPScene
//  Created on:      19-3-2014 ø¿¿¸ 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "IAPScene.h"



#include "MainMenuScene.h"
#include <string>
#include "../model/UserInfo.h"
#include "../dao/HiHighDaoSharedUserDefault.h"
#include "AbilitiesScene.h"


#define TABLE_CELL_WIDTH	m_winSize.width
#define TABLE_CELL_HEIGHT 200.0f

#define TABLE_TOP_POSITION        m_winSize.height - 146
#define TABLE_BOTTOM_POSITION     156

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
IAPScene * iapScene;
#endif

IAPScene::IAPScene(){

}



IAPScene::~IAPScene(){

}





CCScene* IAPScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	IAPScene *layer = IAPScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//	setDelegate((AbilitiesScene*)(scene->getUserData()));
	// return the scene
	return scene;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void setAndroidInApp(const char * method)
{
	CCLog("android inapp status - %s",method);
	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,"net/atgame/dumbo/Dumbo",method,"()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
	}
}
#endif



bool IAPScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	m_application = AGApplication::GetInstance();
	IAPData data;

	data.name = "";
	data.imagePath = "";
	data.price = "";
	data.gold = 0;

	preparedAbilitiList();
	//	ccColor4B c = ccc4(255,0,0,255);
	//	if ( !CCLayerColor::initWithColor(c))
	//    {
	//        return false;
	//    }

	m_winSize = CCDirector::sharedDirector()->getWinSize();

	configureNavigatorView();

	CCTableView *pTableView = CCTableView::create(this, CCSizeMake(m_winSize.width, m_winSize.height - 150 - TABLE_BOTTOM_POSITION));
	pTableView->setAnchorPoint(ccp(0, 0));
	pTableView->setPosition(ccp(0, TABLE_BOTTOM_POSITION));
	pTableView->setDelegate(this);
	pTableView->setDirection(kCCScrollViewDirectionVertical);
	pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	addChild(pTableView);

	pTableView->reloadData();

	CCMenuItemLabel * backBtn = AGUtil::createLabelButton("B A C K", TEXT_FONT_NORMAL, "", "btn_bg_02.png", 0,
			this, menu_selector(IAPScene::backClickListener), BUTTON_TEXT_ALIGN_CENTER);
	CCMenu *m = CCMenu::create(backBtn, NULL);
	m->setPosition(ccp(m_winSize.width / 2, TABLE_BOTTOM_POSITION - 70));
	m->alignItemsHorizontallyWithPadding(30);
	this->addChild(m);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	CCNotificationCenter *notificationCenter = CCNotificationCenter::sharedNotificationCenter();
	notificationCenter->addObserver(this, callfuncO_selector(IAPScene::readyToSale), "appleIapReadyToSaleNotification", NULL);
    notificationCenter->addObserver(this, callfuncO_selector(IAPScene::appleIapComplete), "appleIapCompleteNotification", NULL);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    iapScene = this;
    //setAndroidInApp("startInapp");
#endif
	return true;
}

void IAPScene::onEnter()
{
	CCLayer::onEnter();
	CCLog("IAPScene::onEnter");
}
void IAPScene::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
	CCLayer::onExit();
	CCLog("IAPScene::onExit");
}

void IAPScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCLog("IAPScene::onEnterTransitionDidFinish");
}

void IAPScene::configureNavigatorView() {

	CCLabelBMFont *upgradeLabel = CCLabelBMFont::create("S H O P", TEXT_FONT_NORMAL);
	upgradeLabel->setAnchorPoint(CCPointZero);
	upgradeLabel->setPosition(ccp(50, m_winSize.height - 110));
	this->addChild(upgradeLabel);


	CCSprite *jewelCountBG = CCSprite::createWithSpriteFrameName("jewel_score_bg.png");
	jewelCountBG->setPosition(ccp(m_winSize.width - jewelCountBG->getContentSize().width/2 - 20 , m_winSize.height - 73));
	this->addChild(jewelCountBG);


	ostringstream os;
	os << m_application->getUserInfo()->getGold();
	string temp = os.str();
	AGUtil::calc3point(temp);
	m_hasCoin = CCLabelBMFont::create(temp.c_str(), TEXT_FONT_SMALL);
	os.clear();
	m_hasCoin->setAnchorPoint(ccp(1, 0.5));
	m_hasCoin->setPosition(ccp(m_winSize.width - 40, jewelCountBG->getPositionY()));
	this->addChild(m_hasCoin);


	CCSprite* topLine = CCSprite::createWithSpriteFrameName("sub_titlebar_top.png");
	topLine->setAnchorPoint(ccp(0, 1));
	topLine->setPosition(ccp(0, m_winSize.height - 146));
	this->addChild(topLine);

	CCSprite* botttomLine = CCSprite::createWithSpriteFrameName("sub_titlebar_bottom.png");
	botttomLine->setAnchorPoint(ccp(0, 1));
	botttomLine->setPosition(ccp(0, TABLE_BOTTOM_POSITION));
	this->addChild(botttomLine);

}


void IAPScene::preparedAbilitiList()
{
	m_IAPList.clear();

	IAPData data;

	data.name = "10,000 Jewels";
	data.imagePath = "shop_item_01.png";
	data.price = "0.99";
	data.gold = 10000;
	m_IAPList.push_back(data);


	data.name = "55,000 Jewels";
	data.imagePath = "shop_item_02.png";
	data.price = "4.99";
	data.gold = 55000;
	m_IAPList.push_back(data);

	data.name = "110,000 Jewels";
	data.imagePath = "shop_item_03.png";
	data.price = "9.99";
	data.gold = 110000;
	m_IAPList.push_back(data);


	data.name = "260,000 Jewels";
	data.imagePath = "shop_item_04.png";
	data.price = "20.99";
	data.gold = 260000;
	m_IAPList.push_back(data);


	data.name = "510,000 Jewels";
	data.imagePath = "shop_item_05.png";
	data.price = "39.99";
	data.gold = 510000;
	m_IAPList.push_back(data);

	data.name = "1,400,000 Jewels";
	data.imagePath = "shop_item_06.png";
	data.price = "99.99";
	data.gold = 1400000;
	m_IAPList.push_back(data);

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_IAPList[0].androidItemId = "net.atgame.dumbo.iap.jewel01";
	m_IAPList[1].androidItemId = "net.atgame.dumbo.iap.jewel02";
	m_IAPList[2].androidItemId = "net.atgame.dumbo.iap.jewel03";
	m_IAPList[3].androidItemId = "net.atgame.dumbo.iap.jewel04";
	m_IAPList[4].androidItemId = "net.atgame.dumbo.iap.jewel05";
	m_IAPList[5].androidItemId = "net.atgame.dumbo.iap.jewel06";
//#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    m_products_iOS = [[NSMutableArray alloc] init];
    InAppPurchase_iOS *iap = [InAppPurchase_iOS sharedInstance];
    if([iap initIAP]) {
        [iap requestProductData];
    }
#endif

}

//datasource method
void IAPScene::scrollViewDidScroll(CCScrollView* view)
{

}
void IAPScene::scrollViewDidZoom(CCScrollView* view)
{

}

unsigned int IAPScene::numberOfCellsInTableView(CCTableView *table)
{
    return m_IAPList.size();
}

CCSize IAPScene::cellSizeForTable(CCTableView *table)
{
	return CCSizeMake(TABLE_CELL_WIDTH, TABLE_CELL_HEIGHT);
}

CCTableViewCell* IAPScene::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell* cell = table->cellAtIndex(idx);

    if (cell == NULL) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        IAPData& data = m_IAPList[idx];
        
        
        CCSprite* item = CCSprite::createWithSpriteFrameName(data.imagePath.c_str());
        //        item->setAnchorPoint(ccp(0, 1));
        //        item->setPosition(ccp(40, 164));
        item->setAnchorPoint(ccp(0.5, 0.5));
        item->setPosition(ccp(100, 104));
        item->setTag(0);
        cell->addChild(item);
        
        CCLabelBMFont* descLabel = CCLabelBMFont::create(data.name.c_str(), TEXT_FONT_SMALL);
        descLabel->setAlignment(kCCTextAlignmentLeft);
        descLabel->setAnchorPoint(ccp(0, 1));
        descLabel->setPosition(ccp(220, 160));
        descLabel->setTag(2);
        cell->addChild(descLabel);
        
        CCSprite *buyBtn = CCSprite::createWithSpriteFrameName("shop_price_bg.png");
        buyBtn->setAnchorPoint(ccp(0, 1));
        buyBtn->setPosition(ccp(330, 108));
        cell->addChild(buyBtn);
        
        CCLabelBMFont *priceLabel = CCLabelBMFont::create("0", TEXT_FONT_SMALL, 230, kCCTextAlignmentRight);
        priceLabel->setAnchorPoint(ccp(1, 1));
        priceLabel->setPosition(ccp(buyBtn->getPositionX() + buyBtn->getContentSize().width - 30, buyBtn->getPositionY() - 4));
        priceLabel->setTag(4);
        cell->addChild(priceLabel);
        
        priceLabel->setString(data.price.c_str());
        cell->setUserData(&data);
    }
    else
    {
        IAPData& data = m_IAPList[idx];
        
        CCLabelBMFont* nameLabel = (CCLabelBMFont*)cell->getChildByTag(2);
        nameLabel->setString(data.name.c_str());
        
        CCLabelBMFont* priceLabel = (CCLabelBMFont*)cell->getChildByTag(4);
        priceLabel->setString(data.price.c_str());
        
        
    }

	return cell;
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void callAndroidInAppBuy(const char * param)
{

	cocos2d::JniMethodInfo t;
	if (cocos2d::JniHelper::getStaticMethodInfo(t,"net/atgame/dumbo/Dumbo","callInApp","(Ljava/lang/String;)V")) {

		jstring item = t.env->NewStringUTF(param);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, item);
		t.env->DeleteLocalRef(item);

	}
}

extern "C" {
	void Java_net_atgame_dumbo_HiHigh_resultInApp(JNIEnv* env,jstring param) {

        const char * tempStr = env->GetStringUTFChars(param, 0);
        string itemId(tempStr);
        
        CCLog("inapp success id = %s", itemId.c_str());
        // 인앱처리
        iapScene->refreshJewel(itemId);
	}
}
#endif

//delegate method
void IAPScene::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
	/*
	IAPData* data = (IAPData*)cell->getUserData();

	// userInfo 가져오기
	UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
	// gold 증가
	userInfo->setGold(userInfo->getGold() + data->gold);
	userInfo->setTotalGold(userInfo->getTotalGold() + data->gold);
	// gold refesh

	ostringstream os;
	os << userInfo->getGold();

	m_hasCoin->setString(os.str().c_str());

	AGApplication::GetInstance()->getHiHighDao()->updateGold(userInfo->getGold());
	 */
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if(m_products_iOS.count != 6) return;
    NSUInteger idx = cell->getIdx();
    SKProduct *product = (SKProduct*)[m_products_iOS objectAtIndex:idx];
    if(product != nil && product != NULL) {
        [[InAppPurchase_iOS sharedInstance] buyProduct:product];
    }
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	IAPData* data = (IAPData*)cell->getUserData();
	callAndroidInAppBuy(data->androidItemId.c_str());
#endif



}
void IAPScene::refreshJewel(string itemId) {
    // userInfo 가져오기
    
    int gold = 0;

    for(int i  =0 ; i < m_IAPList.size() ; ++i) {
        if(m_IAPList[i].androidItemId == itemId) {
            gold = m_IAPList[i].gold;
            break;
        }
    }
    
    CCLog("iap id = %s, add gold = %d", itemId.c_str(), gold);

    UserInfo* userInfo = AGApplication::GetInstance()->getUserInfo();
    // gold 증가
    userInfo->setGold(userInfo->getGold() + gold);
    userInfo->setTotalGold(userInfo->getTotalGold() + gold);
    // gold refesh
    ostringstream os;
    os << m_application->getUserInfo()->getGold();
    string temp = os.str();
    os.clear();
    AGUtil::calc3point(temp);
    m_hasCoin->setString(temp.c_str());
    
    AGApplication::GetInstance()->getHiHighDao()->updateGold(userInfo->getGold());
    
    // 어빌리티씬???
}

void IAPScene::appleIapComplete(CCObject *obj)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    SKPaymentTransaction *t = (SKPaymentTransaction*)obj;
    CCLog("$$$$ %s", [t.payment.productIdentifier UTF8String]);
    refreshJewel([t.payment.productIdentifier UTF8String]);
#endif
}


void IAPScene::backClickListener(CCObject* pSender){

	//	this->getDelegate()->callbackPaymentInfo();
	//CCDirector::sharedDirector()->popScene();

	CCScene* abilitiesScene = AbilitiesScene::scene();

	CCTransitionScene* transition = CCTransitionFlipX::create(0.3, abilitiesScene);

	CCDirector::sharedDirector()->replaceScene(transition);

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	setAndroidInApp("endInapp");
//#endif

}

void IAPScene::readyToSale(cocos2d::CCObject *obj)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
	SKProductsResponse *response = (SKProductsResponse*)obj;
	for (NSString *invalidProductId in response.invalidProductIdentifiers)
	{
		NSLog(@"InAppPurchase Invalid product id: %@", invalidProductId);
	}

	for( SKProduct* product in response.products )
	{
		if( product != nil )
		{
			NSLog(@"InAppPurchase Product title: %@", product.localizedTitle);
			NSLog(@"InAppPurchase Product description: %@", product.localizedDescription);
			NSLog(@"InAppPurchase Product price: %@", product.price);
			NSLog(@"InAppPurchase Product id: %@", product.productIdentifier);
		}
	}
    
    [m_products_iOS addObjectsFromArray:response.products];
    
    CCLog("list size %d", [m_products_iOS count]);
#endif


}
