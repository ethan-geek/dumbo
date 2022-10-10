///////////////////////////////////////////////////////////
//  IAPInfo.h
//  Implementation of the Class IAPInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_747E40F9_51C5_4654_8463_2F3A6944BC1F__INCLUDED_)
#define EA_747E40F9_51C5_4654_8463_2F3A6944BC1F__INCLUDED_

#include "../common/HiHighCommon.h"

class IAPInfo
{

public:
	IAPInfo();
	virtual ~IAPInfo();

private:
	int _chargeGold;
	string _imageName;
	float _realPrice;

};
#endif // !defined(EA_747E40F9_51C5_4654_8463_2F3A6944BC1F__INCLUDED_)
