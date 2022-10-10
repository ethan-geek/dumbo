
#if !defined(HH_DOUBLE_ITEMOBJECT)
#define HH_DOUBLE_ITEMOBJECT

#include "./ItemObject.h"


class DoubleItemObject : public ItemObject
{
public:
	DoubleItemObject(void);
	~DoubleItemObject(void);

	virtual void useItem();
};

#endif