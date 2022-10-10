
#if !defined(HH_ITEM_TIMER)
#define HH_ITEM_TIMER

#include "../common/HiHighCommon.h"

class ItemTimer
{
public:
	ItemTimer(void);
	~ItemTimer(void);

	void timeInit();
	void setData(CCSprite* parent,HERO_STATUS_TYPE type, float totalTime);
	void tick(float dt);
	void release();
	
	HERO_STATUS_TYPE getObjectType();

private :
	CCSprite* _parent;
	HERO_STATUS_TYPE _type;
	CCProgressTimer* _timer;
	float _totalTime;
};

#endif

