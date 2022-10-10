///////////////////////////////////////////////////////////
//  UserUpgradeInfo.h
//  Implementation of the Class UserUpgradeInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_2EB7977C_09E9_414f_9C2F_C69977AF7E31__INCLUDED_)
#define EA_2EB7977C_09E9_414f_9C2F_C69977AF7E31__INCLUDED_

#include "../common/HiHighCommon.h"
#include "ItemInfo.h"

class UserUpgradeInfo
{

public:
	UserUpgradeInfo();
	virtual ~UserUpgradeInfo();

	void setUpgradeCount(int upgradeCount);
	void setItemInfo(ItemInfo& itemInfo);

	ItemInfo* getItemInfo();
	int getUpgradeCount();
	float getUpgradeTime();

private:
	ItemInfo _itemInfo;
	int _upgradeCount;

};
#endif // !defined(EA_2EB7977C_09E9_414f_9C2F_C69977AF7E31__INCLUDED_)
