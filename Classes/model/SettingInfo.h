///////////////////////////////////////////////////////////
//  SettingInfo.h
//  Implementation of the Class SettingInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:05
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_2C76B98C_58A9_4eb8_A357_79A78C62615B__INCLUDED_)
#define EA_2C76B98C_58A9_4eb8_A357_79A78C62615B__INCLUDED_

#include "../common/HiHighCommon.h"
#include "UserInfo.h"

class SettingInfo
{

public:
	SettingInfo();
	virtual ~SettingInfo();

private:
	SETTING_TYPE _music;
	SETTING_TYPE _sound;
	UserInfo _userInfo;
	SETTING_TYPE _vibration;

};
#endif // !defined(EA_2C76B98C_58A9_4eb8_A357_79A78C62615B__INCLUDED_)
