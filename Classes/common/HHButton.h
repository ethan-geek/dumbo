//
//  HHButton.h
//  HiHigh
//
//  Created by Insanity on 2014. 10. 17..
//
//

#include "../common/HiHighCommon.h"

class HHButton : public CCMenuItemLabel
{
    
public:
    
    ccColor3B mColor;
    float mWidth;
    float mHeight;
    CCSprite *mBackgroundImage;
    bool mHasBorder;

    HHButton();
    virtual ~HHButton();
    virtual void draw();
    static HHButton * create(CCNode*label, CCObject* target, SEL_MenuHandler selector);
    virtual void setString(const char * label);
    virtual void setColor(ccColor3B color);
    void setSize(float width, float height);
    void setIcon(const char *fileName, bool bContainOff);
    void setBackgroundImage(const char *fileName);
    virtual void selected();
    void setBorder();
};
