
#if !defined(HH_MAIN_PALLAX_MANAGER)

#define HH_MAIN_PALLAX_MANAGER

#include "../common/HiHighCommon.h"
#include "../game/BackgroundFlow.h"
#include "../game/BackgroundManager.h"

class MainPallaxManager
{
public:
	MainPallaxManager(void);
	~MainPallaxManager(void);

	void init(CCNode* _parent);
	void tick(float dt);

private :
	void addPallax();
	void removePallax();
	void addJewel();
	void removeJewel();

	CCParallaxNode* _pallaxNode;

	BackgroundFlow _flow;

	float _JewelBackgroundHeight;

	BackgroundManager _backgroundManager;
};

#endif