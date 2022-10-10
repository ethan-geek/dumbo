///////////////////////////////////////////////////////////
//  StageMapInfo.h
//  Implementation of the Class StageMapInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_C403FB9B_EA84_4af8_91CF_F43AC3627373__INCLUDED_)
#define EA_C403FB9B_EA84_4af8_91CF_F43AC3627373__INCLUDED_

#include "../common/HiHighCommon.h"

class StageMapInfo
{

public:
	StageMapInfo();
	virtual ~StageMapInfo();

private:
	vector<CCPoint> _position;

};
#endif // !defined(EA_C403FB9B_EA84_4af8_91CF_F43AC3627373__INCLUDED_)
