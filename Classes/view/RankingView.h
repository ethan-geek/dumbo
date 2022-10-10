//
//  RankingView.h
//  HiHigh
//
//  Created by Insanity on 2014. 10. 21..
//
//

#ifndef __HiHigh__RankingView__
#define __HiHigh__RankingView__

#include "../common/HiHighCommon.h"

class CCActivityIndicator;
class HHAlert;

class RankingView : public CCLayerColor, public CCTableViewDataSource, public CCTableViewDelegate
{
    
public:
    RankingView();
    virtual ~RankingView();
    
    CREATE_FUNC(RankingView);
    
    virtual bool init();
    //virtual void draw();
    void initMenuArea();
    void initContentsArea();

    
    CCSize mWinSize;
    
    void tabListener(CCObject *obj);
    CCMenu *mFacebookTabBtn;
    CCMenu *mAllTabBtn;
    
    CCLayerColor* mTab1Layer;
    CCLayerColor* mTab2Layer;
    
    CCLayer *mFbRankingLayer;
    CCLayer *mAllRankingLayer;
    
    int mSelectedTab;
    
    CCTableView *mFbTableView;
    CCTableView *mAllTableView;
    
    
    //datasource method
    void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
    CCSize cellSizeForTable(CCTableView *table);
    CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    unsigned int numberOfCellsInTableView(CCTableView *table);
    
    //delegate method
    void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    
    //void initData();
    void onSendScoreCompleted(CCHttpClient* client, CCHttpResponse* response);
    void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
	void onAllRanksRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
    
    void fbInviteBtnListener(CCObject* pSender);
    void fbShareBtnListener(CCObject* pSender);

    static void facebookCallback(Facebook::REQUEST_TYPE cbIndex, string params);
    static void facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message);
    void screenCaptureCallback();
private:

	void resizeForCapture(bool isOriginal);

    vector<UserInfo> mFacebookRanks;
    vector<UserInfo> mAllRanks;
    vector<string> mFbids;

    CCSprite *mAllBG;
    CCSprite *mFBBG;
    bool isFacebookConnected;
    
    CCActivityIndicator * mActivityIndicator;

    int mCompleteCount;

    AGUtil* m_util;

	
	
    string _userScore;
	
    CCScene* _rankingScreenShot;

    void drawRanking();

    void checkProfileLoding(float dt);
	
	void loadingComplete(CCNode* obj);
	
	bool isDrawComplete;
   
    
    bool isPaging;
    bool isListFull;
    int pageIndex;
    int cellLastIndex;

	HHAlert* mAlert;
	static Facebook::REQUEST_TYPE reqType;
	void showAlertRankingView(string title, string message);
	void delayFunctionRankingView();
    void goToConnect(CCObject* object);
};

#endif /* defined(__HiHigh__RankingView__) */
