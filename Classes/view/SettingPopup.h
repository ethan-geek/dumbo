///////////////////////////////////////////////////////////
//  SettingPopup.h
//  Implementation of the Class SettingPopup
//  Created on:      19-3-2014 ���� 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_410E6207_97FE_4b9d_8794_716EDE428ED8__INCLUDED_)
#define EA_410E6207_97FE_4b9d_8794_716EDE428ED8__INCLUDED_


#include "../common/HiHighCommon.h"
#include "BasicPopup.h"

enum SETTING_POPUP_TYPE {
	SETTING_POPUP_TYPE_MAIN_MENU,
	SETTING_POPUP_TYPE_STAGE_MAP
};

enum SETTING_POPUP_TAG {
	SETTING_POPUP_TAG_SOUND = 1,
	SETTING_POPUP_TAG_MUSIC = 2,
	SETTING_POPUP_TAG_VIBRATE = 3,
	SETTING_POPUP_TAG_ABOUT = 4,
	SETTING_POPUP_TAG_FACEBOOK = 5,
	SETTING_POPUP_TAG_MAINMENU = 6

};

class SettingPopup : public BasicPopup
{

public:
	SettingPopup();
	virtual ~SettingPopup();

    CREATE_FUNC(SettingPopup);
    
	static void facebookCallback(Facebook::REQUEST_TYPE cbIndex, string params);
	static void facebookErrorCallback(Facebook::REQUEST_TYPE requestType, string message);
	
    static SettingPopup* createWithType(SETTING_POPUP_TYPE type);
    void initSettingPopup();
    void loadConfig();
    void menuSelected(CCObject* obj);
    void addAboutView();
    void back(CCObject*);
    void onOffSound();
    void onOffMusic();
    void onOffVibe();
    void goPreviousScene();

    void changeVisibleSettingXIcon(int tag, bool b);
    void setVisibleButtons(bool b);

	void testMenuSelectedListener(CCObject*);
    void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);

	void menuCloseCallback(CCObject* pSender);
	
    void tick(float dt);

    CCMenu *settingMenu;
    CCLayer *aboutLayer;
    
    SETTING_POPUP_TYPE popupType;
    
    CCMenu *menu;
	
	

};
#endif // !defined(EA_410E6207_97FE_4b9d_8794_716EDE428ED8__INCLUDED_)
