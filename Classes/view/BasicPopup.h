///////////////////////////////////////////////////////////
//  BasicPopup.h
//  Implementation of the Class BasicPopup
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_A1ECAB1D_87A8_42b4_9E1C_6EA942102497__INCLUDED_)
#define EA_A1ECAB1D_87A8_42b4_9E1C_6EA942102497__INCLUDED_

#include "../common/HiHighCommon.h"
#define SETTING_BTN_INTERVAL_LENGTH 94

#define BASICPOPUP			20001
#define MAINLAYER			20002



class BasicPopup : public CCLayerColor
{

public:
    BasicPopup();
    virtual ~BasicPopup();
    virtual void menuCloseCallback(CCObject* pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void initPopup(CCSize size);
    void initPopup();
    void show();
    
    CCLayerColor *mainLayer;
    CCMenu* closeMenu;
    CCSize mWinSize;
};
#endif // !defined(EA_A1ECAB1D_87A8_42b4_9E1C_6EA942102497__INCLUDED_)
