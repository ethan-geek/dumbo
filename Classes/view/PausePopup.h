///////////////////////////////////////////////////////////
//  PausePopup.h
//  Implementation of the Class PausePopup
//  Created on:      19-3-2014 ¿ÀÀü 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_9B9EE990_A8A5_41b9_9170_7244D2D4C649__INCLUDED_)
#define EA_9B9EE990_A8A5_41b9_9170_7244D2D4C649__INCLUDED_

#include "../common/HiHighCommon.h"

#include "BasicPopup.h"

class PausePopup : public BasicPopup
{

public:
	PausePopup();
	virtual ~PausePopup();

    static PausePopup* createWithSize(CCSize size);
    void initPausePopup();
    void loadConfig();
    void menuSelected(CCObject* obj);
    void continueGame();
    void retryGame();
    void onOffSound();
    void onOffMusic();
    void onOffVibe();
    virtual void show();
    void pauseCallback();
    void changeVisibleSettingXIcon(int tag, bool b);
    void setVisibleButtons(bool b);
    void goPreviousScene();
    
    CCMenu *settingMenu;
    
};
#endif // !defined(EA_9B9EE990_A8A5_41b9_9170_7244D2D4C649__INCLUDED_)
