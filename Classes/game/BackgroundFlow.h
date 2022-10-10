
#if !defined(HH_BACKGROUND_FLOW)
#define HH_BACKGROUND_FLOW

#include "../common/HiHighCommon.h"
#include "./Background.h"
#include "./ChangeColorUtil.h"

class BackgroundFlow : public Background
{
public:
	BackgroundFlow(void);
	virtual ~BackgroundFlow(void);

    virtual	void addBackground(CCParallaxNode* node){};
    
	void addMainBackground(CCParallaxNode* node);
	void addGameBackground(CCParallaxNode* node);
    void addBackgroundParticle(CCParallaxNode* node);
    
    
    void initBackgroundObjects(CCParallaxNode* node);
    bool checkOverlapHeight(int height , int width, int index, CCParallaxNode* node);
    void removeGameBackground(CCParallaxNode* node);

    void changeColor(CCSprite * target,ccColor3B color);
    void updateColor(ColorAverage average,ColorVector colorVector,RGB rgb, CCSprite * target) ;
    
private :
    
    vector<CCSprite*> backgoundObjects;
	virtual void readyBackgroundIndex();
    cocos2d::CCSprite* getOpaqueSprite(CCSprite* temp, CCRenderTexture *r, ccColor3B c);
    
    int addCount;
    int particleBackgroundHeight;
};

#endif

