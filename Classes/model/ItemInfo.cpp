///////////////////////////////////////////////////////////
//  ItemInfo.cpp
//  Implementation of the Class ItemInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "ItemInfo.h"

vector<int> g_upgradePrice;

ItemInfo::ItemInfo() : _price(0) , _description("") , _iconName("") , _name(""){
	if(g_upgradePrice.size() == 0){

		g_upgradePrice.push_back(500);
		g_upgradePrice.push_back(1000);
		g_upgradePrice.push_back(1500);
		g_upgradePrice.push_back(2000);
		g_upgradePrice.push_back(2500);

		g_upgradePrice.push_back(3500);
		g_upgradePrice.push_back(4500);
		g_upgradePrice.push_back(5500);
		g_upgradePrice.push_back(6500);
		g_upgradePrice.push_back(7500);

		g_upgradePrice.push_back(10000);
		g_upgradePrice.push_back(12000);
		g_upgradePrice.push_back(14000);
		g_upgradePrice.push_back(16000);
		g_upgradePrice.push_back(18000);

		g_upgradePrice.push_back(22000);
		g_upgradePrice.push_back(26000);
		g_upgradePrice.push_back(30000);
		g_upgradePrice.push_back(34000);
		g_upgradePrice.push_back(40000);

	}
}



ItemInfo::~ItemInfo(){

}


void ItemInfo::setDescription(string description){
	_description = description;
}
void ItemInfo::setIconName(string iconName) {
	_iconName = iconName;
}
void ItemInfo::setName(string name) {
	_name = name;
}
void ItemInfo::setPrice(int price) {
	_price = price;
}

string ItemInfo::getDescription() {
	return _description;
}
string ItemInfo::getIconName() {
	return _iconName;
}
string ItemInfo::getName() {
	return _name;
}
int ItemInfo::getPrice() {
	return _price;
}
int ItemInfo::getId() {
	return _id;
}
void ItemInfo::setId(int id) {
	_id = id;
}
int ItemInfo::getUpgradePrice(int upgradeCount) {
	return g_upgradePrice[upgradeCount];
}