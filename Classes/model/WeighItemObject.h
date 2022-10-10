#pragma once

#if !defined(HH_WEIGHTITEMOBJECT)
#define HH_WEIGHTITEMOBJECT

#include "../common/HiHighCommon.h"
#include "./ItemObject.h"



class WeighItemObject : public ItemObject
{
public:
	WeighItemObject(void);
	~WeighItemObject(void);

	virtual void useItem();
	
};

#endif
