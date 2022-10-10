
#if !defined(HH_STARFISHOBJECT)
#define HH_STARFISHOBJECT

#include "../common/HiHighCommon.h"
#include "interactionObject.h"



class StarFishObject : public interactionObject
{
public:
	StarFishObject(void);
	~StarFishObject(void);

	virtual void processContact();
	virtual void setSprite(CCSprite* sprite);
    virtual void useItem();
};

#endif