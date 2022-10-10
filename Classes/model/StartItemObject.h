#pragma once

#if !defined(HH_STARTITEMOBJECT)
#define HH_STARTITEMOBJECT

#include "./ItemObject.h"

class StartItemObject  : public ItemObject
{
public:
	StartItemObject(void);
	~StartItemObject(void);

	virtual void useItem();
};

#endif