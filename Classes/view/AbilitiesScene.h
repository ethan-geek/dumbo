///////////////////////////////////////////////////////////
//  AbilitiesScene.h
//  Implementation of the Class AbilitiesScene
//  Created on:      19-3-2014 ø¿¿¸ 11:55:01
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_0D6983FE_59B4_4390_B283_DEA154E8D266__INCLUDED_)
#define EA_0D6983FE_59B4_4390_B283_DEA154E8D266__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../common/HHAlert.h"
#include "../common/HiHighConnector.h"

#define ITEM_OBJECTS_PATH "itemObject/itemObjects.xml"

#define ITEM_SPRITE_TAG		0
#define LEVEL_LABEL_TAG		1
#define NAME_LABEL_TAG		2
#define DESCRIPT_LABEL_TAG 	3
#define PRICE_LABEL_TAG		4
#define UPGRADE_BUTTON_TAG	5

class ItemInfo;

class AbilitiesScene : public cocos2d::CCLayerColor,public CCTableViewDataSource, public CCTableViewDelegate
{

public:
	AbilitiesScene();
	virtual ~AbilitiesScene();
	
    void configureNavigatorView();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
    virtual void onExitTransitionDidStart();
	
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
	
	void preparedAbilitiList();
	
	//datasource method
	void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
	
	CCSize cellSizeForTable(CCTableView *table);
    
	CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);

    unsigned int numberOfCellsInTableView(CCTableView *table);
	
	
	//delegate method
	void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
	
	// implement the "static node()" method manually
    CREATE_FUNC(AbilitiesScene);

    void backClickListener(CCObject* pSender);
    void shopClickListener(CCObject* pSender);
    void startClickListener(CCObject* pSender);
    void notEnoughClickListener(CCObject* pSender);

	void setUpgradeInfo(CCTableViewCell* cell, bool isBuy);
    void doUpgrade(CCObject *obj);

	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    void displayUpgradeGage(CCTableViewCell *cell, int upgradeCount);
    void checkUpgradeAvailable(CCTableViewCell *cell, int price, int upgradeCount);
    void reloadTableView();

    HHAlert *alert;

	virtual void keyBackClicked();

private:
	vector<ItemInfo> m_abilitiesList;
	CCSize m_winSize;
	AGApplication* m_application;
	CCLabelBMFont * m_hasCoin;
	
	UserInfo* m_userInfo;

	CCTableView* pTableView;
	CCTableViewCell *m_selectedCell;
};



#endif // !defined(EA_0D6983FE_59B4_4390_B283_DEA154E8D266__INCLUDED_)
