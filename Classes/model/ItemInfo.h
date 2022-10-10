///////////////////////////////////////////////////////////
//  ItemInfo.h
//  Implementation of the Class ItemInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_2A667D5C_FEF5_456d_AE0D_F753A16CA26F__INCLUDED_)
#define EA_2A667D5C_FEF5_456d_AE0D_F753A16CA26F__INCLUDED_

#include "../common/HiHighCommon.h"

class ItemInfo
{

public:
	ItemInfo();
	virtual ~ItemInfo();

	void setDescription(string description);
	void setIconName(string iconName);
	void setName(string name);
	void setPrice(int price);
	void setId(int id);

	string getDescription();
	string getIconName();
	string getName();
	int getPrice();
	int getId();
	
	int getUpgradePrice(int upgradeCount);

private:
	string _description;
	string _iconName;
	string _name;
	int _price;
	int _id;

};
#endif // !defined(EA_2A667D5C_FEF5_456d_AE0D_F753A16CA26F__INCLUDED_)
