///////////////////////////////////////////////////////////
//  LogoScene.h
//  Implementation of the Class LogoScene
//  Created on:      19-3-2014 ¿ÀÀü 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_8CEDE518_BB58_41dc_B8B8_7430751BC5E2__INCLUDED_)
#define EA_8CEDE518_BB58_41dc_B8B8_7430751BC5E2__INCLUDED_

#include "../common/HiHighCommon.h"

class LogoScene : public CCLayerColor
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(LogoScene);
    
    void loadResourcesStart(float dt);
    void loadResourcesEnded();
    
    void loadMusic();
    void loadSound();
	void loadResource();
	void loadUserInfo();
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);
};
#endif // !defined(EA_8CEDE518_BB58_41dc_B8B8_7430751BC5E2__INCLUDED_)
