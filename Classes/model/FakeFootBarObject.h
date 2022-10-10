///////////////////////////////////////////////////////////
//  FakeFootBarObject.h
//  Implementation of the Class FakeFootBarObject
//  Created on:      19-3-2014 ���� 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_CF1CD58A_6D24_428c_AF4F_C984B78DC87E__INCLUDED_)
#define EA_CF1CD58A_6D24_428c_AF4F_C984B78DC87E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "interactionObject.h"


class FakeFootBarObject : public interactionObject
{

public:
	FakeFootBarObject();
	virtual ~FakeFootBarObject();

	void setAngle(float angle);
	float getAngle();
	void removeFakeFootBar();

	virtual void processContact();
	virtual void processAnimation();

private:
	float _angle;
	bool _isAnimation;

};
#endif // !defined(EA_CF1CD58A_6D24_428c_AF4F_C984B78DC87E__INCLUDED_)
