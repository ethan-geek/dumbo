///////////////////////////////////////////////////////////
//  UserUpgradeInfo.cpp
//  Implementation of the Class UserUpgradeInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "UserUpgradeInfo.h"

vector<float> g_upgradeTime;


UserUpgradeInfo::UserUpgradeInfo() : _upgradeCount(0){
	if(g_upgradeTime.size() == 0) {
		float time = 0.5;
		g_upgradeTime.push_back(time);
		time += 0.5;
		g_upgradeTime.push_back(time);
		time += 0.5;
		g_upgradeTime.push_back(time);
		time += 0.5;
		g_upgradeTime.push_back(time);
		time += 0.5;
		g_upgradeTime.push_back(time);

		time += 0.4;
		g_upgradeTime.push_back(time);
		time += 0.4;
		g_upgradeTime.push_back(time);
		time += 0.4;
		g_upgradeTime.push_back(time);
		time += 0.4;
		g_upgradeTime.push_back(time);
		time += 0.4;
		g_upgradeTime.push_back(time);

		time += 0.3;
		g_upgradeTime.push_back(time);
		time += 0.3;
		g_upgradeTime.push_back(time);
		time += 0.3;
		g_upgradeTime.push_back(time);
		time += 0.3;
		g_upgradeTime.push_back(time);
		time += 0.3;
		g_upgradeTime.push_back(time);

		time += 0.2;
		g_upgradeTime.push_back(time);
		time += 0.2;
		g_upgradeTime.push_back(time);
		time += 0.2;
		g_upgradeTime.push_back(time);
		time += 0.2;
		g_upgradeTime.push_back(time);
		time += 0.2;
		g_upgradeTime.push_back(time);
	}
}



UserUpgradeInfo::~UserUpgradeInfo(){

}


void UserUpgradeInfo::setUpgradeCount(int upgradeCount) {
	_upgradeCount = upgradeCount;
}
void UserUpgradeInfo::setItemInfo(ItemInfo& itemInfo) {
	_itemInfo = itemInfo;
}

ItemInfo* UserUpgradeInfo::getItemInfo() {
	return &_itemInfo;
}
int UserUpgradeInfo::getUpgradeCount() {
	return _upgradeCount;
}

float UserUpgradeInfo::getUpgradeTime() {
	return g_upgradeTime[_upgradeCount-1];
}