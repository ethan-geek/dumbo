///////////////////////////////////////////////////////////
//  MainMenuScene.h
//  Implementation of the Class MainMenuScene
//  Created on:      19-3-2014 ���� 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_08716EDF_46D5_4d5a_8EE6_0130BDF86EAE__INCLUDED_)
#define EA_08716EDF_46D5_4d5a_8EE6_0130BDF86EAE__INCLUDED_

#include "../common/HiHighCommon.h"
#include "./SettingPopup.h"
#include "../model/UserInfo.h"
#include "../common/HiHighConnector.h"
#include "../model/MainPallaxManager.h"
#include "../network/HHNetworkReceiver.h"

using namespace CSJson;

class HHAlert;
class HHButton;

class MainMenuScene : public cocos2d::CCLayerColor
{

public:

	static MainMenuScene* g_main;
	static MainMenuScene* GetInstance();
	
    CCSize winSize;
    
	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(MainMenuScene);
    
    void guestBtnListener(CCObject* obj);
    void facebookConnectBtnListener(CCObject* obj);

    static void facebookCallback(Facebook::REQUEST_TYPE requestType, string params);
	static void facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message);
	
    //void didAccelerate(CCAcceleration* pAccelerationValue);
    
    virtual void keyBackClicked();
    void backBtnOkListener(CCObject* obj);

    
    void abilityClickListener(CCObject* pSender, CCControlEvent event);

    void settingClickListener(CCObject* pSender);
    
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
	
	void authServerAfter(float);
   
	void facebookStateChange();

	void tick(float dt);

    void addJewel(int width, int height);
    
	void onRegistGuestCompleted(CCHttpClient* client, CCHttpResponse* response);
	void onModifyGuestCompleted(CCHttpClient* client, CCHttpResponse* response);
	
private :

	CCMenuItemLabel *fbBtn;
	CCMenuItemLabel *guestBtn;
	CCMenuItemLabel *playBtn;
	
	HHAlert* _backAlert;
	MainPallaxManager _pallaxManager;
};
#endif // !defined(EA_08716EDF_46D5_4d5a_8EE6_0130BDF86EAE__INCLUDED_)
