
#if !defined(HH_MAGNETITEMOBJECT)
#define HH_MAGNETITEMOBJECT

#include "./ItemObject.h"
#include "../common/HiHighCommon.h"


class MagnetItemObject : public ItemObject
{
public:
	MagnetItemObject(void);
	~MagnetItemObject(void);

	virtual void useItem();
	
};

#endif
