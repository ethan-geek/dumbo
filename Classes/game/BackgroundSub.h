
#if !defined(HH_BACKGROUND_SUB)
#define HH_BACKGROUND_SUB

#include "./Background.h"
#include "../common/XmlLoader.h"

class BackgroundSub : public Background
{
public:
	BackgroundSub(void);
	~BackgroundSub(void);

	void init(ParallaxLayer& pLayer, CCParallaxNode* node, vector<CCSprite*>& paraList);

	virtual void addBackground(CCParallaxNode* node);
	virtual void removeBackground(CCParallaxNode* node);

private :
	virtual void readyBackgroundIndex();
	ParallaxLayer _parallaxData;
	vector<CCLayer*> _layerList;
	int index;
	int _lowIndex;
	float _lowHeight;
	float _changeHeight;
};

#endif