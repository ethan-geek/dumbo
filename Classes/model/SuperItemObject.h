///////////////////////////////////////////////////////////
//  SuperItemObject.h
//  Implementation of the Class SuperItemObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_545EC422_71C7_4ef4_89A1_6FA22A393AE2__INCLUDED_)
#define EA_545EC422_71C7_4ef4_89A1_6FA22A393AE2__INCLUDED_

#include "../common/HiHighCommon.h"
#include "./ItemObject.h"

class SuperItemObject : public ItemObject
{

public:
	SuperItemObject();
	virtual ~SuperItemObject();

	virtual void useItem();


};
#endif // !defined(EA_545EC422_71C7_4ef4_89A1_6FA22A393AE2__INCLUDED_)
