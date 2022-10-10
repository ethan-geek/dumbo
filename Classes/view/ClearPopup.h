///////////////////////////////////////////////////////////
//  ClearPopup.h
//  Implementation of the Class ClearPopup
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_12C6D89B_8EF8_4ae3_9F82_53D155DF4923__INCLUDED_)
#define EA_12C6D89B_8EF8_4ae3_9F82_53D155DF4923__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../model/UserInfo.h"
#include "../common/HiHighConnector.h"
#include "../common/HHAlert.h"
class RankingView;
class ClearPopup : public cocos2d::CCLayerColor
{

public:
	ClearPopup();
	virtual ~ClearPopup();
    virtual void onExitTransitionDidStart();

    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(ClearPopup);

    virtual void keyBackClicked();
	void facebookShare(CCObject* obj);
private:
    AGApplication* m_application;
    CCLabelBMFont * m_hasCoin;

	HHAlert* _renewalAlert;
	RankingView *_rankingView;

    CCSize _winSize;
    
    void initScoreView();
    void initRankingView();
    
    void replayBtnListener(CCObject* pSender);
    //void nextBtnListener(CCObject* pSender, CCControlEvent event);
    void homeBtnListener(CCObject* pSender);
    void fbShareBtnListener(CCObject* pSender);
    
    void showAdvertisement();

	void renewalCallbackFunc(float dt);
    
    void earnedJewelAnimation(float dt);
    void earnedComboAnimation(float dt);
    
    CCLabelBMFont *jewelValue;
    CCLabelBMFont *maxComboValue;
    CCLabelBMFont *recordValue;
    
    static int int_width(int num);
};
#endif // !defined(EA_12C6D89B_8EF8_4ae3_9F82_53D155DF4923__INCLUDED_)
