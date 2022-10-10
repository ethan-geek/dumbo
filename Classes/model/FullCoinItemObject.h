///////////////////////////////////////////////////////////
//  FullCoinItemObject.h
//  Implementation of the Class FullCoinItemObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_B020256A_B86D_4dbb_BE77_E0910C68DA3B__INCLUDED_)
#define EA_B020256A_B86D_4dbb_BE77_E0910C68DA3B__INCLUDED_

#include "../common/HiHighCommon.h"
#include "ItemObject.h"

class FullCoinItemObject : public ItemObject
{

public:
	FullCoinItemObject();
	virtual ~FullCoinItemObject();

	virtual void useItem();
};
#endif // !defined(EA_B020256A_B86D_4dbb_BE77_E0910C68DA3B__INCLUDED_)
