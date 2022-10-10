
#if !defined(HH_SHIELDITEMOBJECT)
#define HH_SHIELDITEMOBJECT

#include "./ItemObject.h"
#include "../common/HiHighCommon.h"

class ShieldItemObject : public ItemObject
{
public:
	ShieldItemObject(void);
	~ShieldItemObject(void);

	virtual void useItem();
	
};

#endif