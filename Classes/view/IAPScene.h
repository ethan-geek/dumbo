///////////////////////////////////////////////////////////
//  IAPScene.h
//  Implementation of the Class IAPScene
//  Created on:      19-3-2014 ���� 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_DD139CDE_647F_4355_B897_0468503F3977__INCLUDED_)
#define EA_DD139CDE_647F_4355_B897_0468503F3977__INCLUDED_

#include "../common/HiHighCommon.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "InAppPurchase_iOS.h"
#endif

typedef struct _IAPData
{
	string name;
    string imagePath;
	string price;
	int gold;
	string androidItemId;
}IAPData;

class IAPScene: public cocos2d::CCLayer,public CCTableViewDataSource, public CCTableViewDelegate
{
    
public:
	IAPScene();
	virtual ~IAPScene();
	
    void configureNavigatorView();
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	
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
    CREATE_FUNC(IAPScene);
    
    
    void backClickListener(CCObject* pSender);
    void refreshJewel(string itemId) ;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NSMutableArray *m_products_iOS;
    //vector<SKProduct*> m_products_iOS;
#endif
    CCLabelBMFont *m_hasCoin;    
private:
	vector<IAPData> m_IAPList;
    

	CCSize m_winSize;

    AGApplication* m_application;

    
    void readyToSale(CCObject* obj);
    void appleIapComplete(CCObject* obj);
};
#endif // !defined(EA_DD139CDE_647F_4355_B897_0468503F3977__INCLUDED_)
