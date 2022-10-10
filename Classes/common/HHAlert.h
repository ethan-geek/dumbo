//
//  HHAlert.h
//  HiHigh
//
//  Created by insanity on 2014. 5. 22..
//
//

#ifndef __HiHigh__HHAlert__
#define __HiHigh__HHAlert__

#include "../common/HiHighCommon.h"

class HHAlert : public CCLayerColor
{
    
public:
    HHAlert();
    virtual ~HHAlert();
    static HHAlert* create(char const* title, char const*  message, char const*  okBtnLabel, char const* cancelBtnLabel);
    void initAlert();
    void show();
	void showPush();
    void close(CCObject* obj);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void cancelBtnListener(CCObject *obj);
    void setImage(CCSprite* sprite);
    
    bool isShow();

    char const* _title;
    char const* _message;
    char const* _okBtnLabel;
    char const* _cancelBtnLabel;
    CCLabelBMFont *titleLabel;
    CCLabelBMFont *messageLabel;
    
    CCLayerColor * _alertlayer;
    CCMenuItemLabel *okayBtn;
    bool _showFlag;
	bool _isPush;
    
};
#endif // !defined(EA_A1ECAB1D_87A8_42b4_9E1C_6EA942102497__INCLUDED_)
