///////////////////////////////////////////////////////////
//  UserInfo.h
//  Implementation of the Class UserInfo
//  Created on:      19-3-2014 ���� 11:55:07
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_DD7D3545_504F_43ee_B785_C352481DAAD9__INCLUDED_)
#define EA_DD7D3545_504F_43ee_B785_C352481DAAD9__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../model/StageScoreInfo.h"
#include "../model/UserUpgradeInfo.h"
#include "../model/HeartInfo.h"

class UserInfo
{

public:
	UserInfo();
	virtual ~UserInfo();

	void setCurrentStage(int currentState);
	void setFacebookId(string id);
	void setGold(int gold);
	void setHeartInfo(HeartInfo* heartInfo);
	void setStageScoreInfo(StageScoreInfo& stageScoreInfo);
	void setEndlessScoreInfo(StageScoreInfo& endlessScoreInfo);
	void setTotalGold(int totalGold);
	void setUserUpgradeInfo(UserUpgradeInfo& userUpgradeInfo);
	void setLastVisitDate(float date);
	void setName(string name);
	void setProfileUrl(string profileUrl);
	void setGuestId(string guestId);
	void setId(long id);
	

	int getCurrentStage();
	string getFacebookId();
	int getGold();
	HeartInfo* getHeartInfo();
	StageScoreInfo* getStageScoreInfo(int stage);
	int getTotalGold();
	UserUpgradeInfo* getUserUpgradeInfo(string name);

	vector<StageScoreInfo>& getStageScoreInfoList();
	StageScoreInfo& getEndlessScoreInfo();
	map<string, UserUpgradeInfo>& getUserUpgradeInfoMap();
	float getLastVisitDate();
	string getProfileUrl();
	string getName();
	string getGuestId();
	long getId();
private:
	int _currentStage;
	string _facebookId;
	int _gold;
	HeartInfo _heartInfo;
	vector<StageScoreInfo> _stageScoreInfoList;
	StageScoreInfo _endlessScoreInfo;
	int _totalGold;
	map<string, UserUpgradeInfo> _userUpgradeInfoMap;
	float _lastVisitDate;
    string _name;
	string _profileUrl;
	string _guestId;
	long _id;
};
#endif // !defined(EA_DD7D3545_504F_43ee_B785_C352481DAAD9__INCLUDED_)
