///////////////////////////////////////////////////////////
//  HeartInfo.h
//  Implementation of the Class HeartInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_595A113D_9536_46b4_8A63_7CC9370FAD0F__INCLUDED_)
#define EA_595A113D_9536_46b4_8A63_7CC9370FAD0F__INCLUDED_

#include "../common/HiHighCommon.h"

class HeartInfo
{

public:
	HeartInfo();
	virtual ~HeartInfo();

	void setChargeHeartTime(string time);
	void setChargeHeartTime(long time);
	void setHeartCount(int heartCount);

	void increaseHeart();
	void increaseHeart(int heartCount);
	bool decreaseHeart();

	string getChargeHeartTime();
	long getChargeHeartTimeLong();
	int getHeartCount();
private:

	void saveXml();

	string _chargeHeartTime;
	int _heartCount;

};
#endif // !defined(EA_595A113D_9536_46b4_8A63_7CC9370FAD0F__INCLUDED_)
