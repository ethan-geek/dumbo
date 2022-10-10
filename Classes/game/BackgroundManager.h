
#if !defined(HH_BACKGROUND_MANAGER)
#define HH_BACKGROUND_MANAGER

#include "./BackgroundFlow.h"
#include "./BackgroundFull.h"
#include "./BackgroundSub.h"
#include "./ChangeColorUtil.h"

class BackgroundManager
{
public:
	BackgroundManager(void);
	~BackgroundManager(void);

	void init(CCParallaxNode* node);
	void addBackground();
	void removeBackground();
    
    void setBackgroundObjectColor();
    
    
    ccColor3B getColorDivide(ccColor3B c, int count);
    void setColorAndAverage(ccColor3B currentColor, ccColor3B nextColor);
    void changeColor();
private :

	void changeColor(CCSprite * target,ccColor3B color);
	void updateColor(ColorAverage average,ColorVector colorVector,RGB rgb, CCSprite * target);

	BackgroundFull _full;
	BackgroundFlow _flow;
	vector<BackgroundSub> _subList;
    
    ColorAverage averageNear;
    ColorAverage averageNormal;
    ColorAverage averageFar;
    
    
    CCSprite * nearColor;
    CCSprite * normalColor;
    CCSprite * farColor;

	vector<CCSprite*> _parallaxSpriteList;

	CCParallaxNode* _parallaxNode;
};

#endif