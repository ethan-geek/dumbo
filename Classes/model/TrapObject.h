///////////////////////////////////////////////////////////
//  TrapObject.h
//  Implementation of the Class TrapObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_40A3B301_C2F3_4135_AC8D_4389589C1F6C__INCLUDED_)
#define EA_40A3B301_C2F3_4135_AC8D_4389589C1F6C__INCLUDED_

#include "../common/HiHighCommon.h"
#include "interactionObject.h"

class TrapObject : public interactionObject
{

public:
	TrapObject();
	virtual ~TrapObject();

	virtual void processContact();

	void sprayInk();
	void removeInk(CCObject* obj);
	void fadeoutInk(CCObject*);
private:
	int _goldAmount;
	CCSprite *ink;
};
#endif // !defined(EA_40A3B301_C2F3_4135_AC8D_4389589C1F6C__INCLUDED_)
