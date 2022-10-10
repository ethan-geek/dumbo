
#if !defined(HH_HiHighDao)
#define HH_HiHighDao

#include "../common/HiHighCommon.h"
#include "../model/UserInfo.h"
#include "../model/UserUpgradeInfo.h"
#include "../model/HeartInfo.h"
#include "../model/StageScoreInfo.h"

#define XML_STORAGE		"HH_XML_STORAGE"

class HiHighDao
{
public:
	HiHighDao(void) {}
	virtual ~HiHighDao(void) {}

	virtual void init() = 0;

	virtual UserInfo* selectUserInfo() = 0;

	virtual vector<UserUpgradeInfo*>* selectUpgradeInfoList() = 0;
	virtual void updateUpgradeInfo(UserUpgradeInfo info) = 0;

	virtual int selectGold() = 0;
	virtual void updateGold(int gold) = 0;

	virtual HeartInfo* selectHeartInfo() = 0;
	virtual void updateHeartInfo(HeartInfo* heartInfo) = 0;

	virtual int selectCurrentStage() = 0;
	virtual void updateCurrentStage(int currentStatge) = 0;

	virtual StageScoreInfo* selectStageScoreInfo() = 0;
	virtual void updateScoreInfo(StageScoreInfo) = 0;

	virtual void updateUserInfo(UserInfo* info) = 0;

};



#endif
