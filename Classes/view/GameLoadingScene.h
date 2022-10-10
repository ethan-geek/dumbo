//
//  GameLoadingScene.h
//  HiHigh
//
//  Created by Jackdaw on 2014. 4. 7..
//
//

#ifndef __HiHigh__GameLoadingScene__
#define __HiHigh__GameLoadingScene__

#include "../common/HiHighCommon.h"


class GameLoadingScene : public CCLayerColor
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameLoadingScene);
    
	void onFbRecordRequestCompleted(CCHttpClient* client, CCHttpResponse* response);

private:
    vector<CCSprite*> mLoadingArray;
    int mLoadCount;
    int mTotalBoxCount;
    bool mEnded;

    void loadResourcesStart(float dt);
    void loadResourcesEnded(float dt);
    

};


#endif /* defined(__HiHigh__GameLoadingScene__) */
