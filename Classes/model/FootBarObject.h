///////////////////////////////////////////////////////////
//  FootBarObject.h
//  Implementation of the Class FootBarObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_1B30A844_8EFC_44ff_8043_7303CD36684D__INCLUDED_)
#define EA_1B30A844_8EFC_44ff_8043_7303CD36684D__INCLUDED_

#include "../common/HiHighCommon.h"
#include "interactionObject.h"

class FootBarObject : public interactionObject
{

public:
	FootBarObject();
	virtual ~FootBarObject();

	void setAngle(float angle);
	float getAngle();

	virtual void processContact();
	virtual void processAnimation();
    virtual void setSprite(CCSprite* sprite);
private:
	float _angle;

};
#endif // !defined(EA_1B30A844_8EFC_44ff_8043_7303CD36684D__INCLUDED_)
