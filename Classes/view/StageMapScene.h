///////////////////////////////////////////////////////////
//  StageMapScene.h
//  Implementation of the Class StageMapScene
//  Created on:      19-3-2014 ¿ÀÀü 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_190DEC85_04E0_461a_B4B9_D992BE155DBD__INCLUDED_)
#define EA_190DEC85_04E0_461a_B4B9_D992BE155DBD__INCLUDED_

#include "../common/HiHighCommon.h"

class StageMapScene : CCLayer
{

public:
    virtual bool init();
	StageMapScene();
	virtual ~StageMapScene();
    static CCScene* scene();
    CREATE_FUNC(StageMapScene);
    
    void makeStageMap();
    void makeTopBar();
    
    void settingClickListener(CCObject *obj, CCControlEvent event);
    void abilityClickListener(CCObject *obj, CCControlEvent event);
    void stageSelectListener(CCObject *obj);
    void mailBoxListener(CCObject *obj, CCControlEvent event);
    
    CCSize _winSize;
    
    CCControlButton* settingBtn;
    CCControlButton* abilityBtn;
    
};
#endif // !defined(EA_190DEC85_04E0_461a_B4B9_D992BE155DBD__INCLUDED_)
