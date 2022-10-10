
#if !defined(HH_BACKGROUND_FULL)
#define HH_BACKGROUND_FULL

#include "./Background.h"

class BackgroundFull : public Background
{
public:
	BackgroundFull(void);
	~BackgroundFull(void);

	virtual void addBackground(CCParallaxNode* node);
	
private :
	virtual void readyBackgroundIndex();

};


#endif
