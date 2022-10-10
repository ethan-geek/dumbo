

#if !defined(HH_HiHighDaoSharedUserDefault)
#define HH_HiHighDaoSharedUserDefault



#include "../common/HiHighCommon.h"
#include "./HiHighDao.h"
#include "../common/XmlCreator.h"

class HiHighDaoSharedUserDefault :	public HiHighDao
{
public:
	HiHighDaoSharedUserDefault(void);
	~HiHighDaoSharedUserDefault(void);

	virtual void init();

	virtual UserInfo* selectUserInfo();

	virtual vector<UserUpgradeInfo*>* selectUpgradeInfoList();
	virtual void updateUpgradeInfo(UserUpgradeInfo info);

	virtual int selectGold();
	virtual void updateGold(int gold);

	virtual HeartInfo* selectHeartInfo();
	virtual void updateHeartInfo(HeartInfo* heartInfo);

	virtual int selectCurrentStage();
	virtual void updateCurrentStage(int currentStatge);

	virtual StageScoreInfo* selectStageScoreInfo();
	virtual void updateScoreInfo(StageScoreInfo);

	virtual void updateUserInfo(UserInfo* info);

private:

	void updateXml();

	void saveFile(string str);
	string loadFile();

	AGApplication* _application;
	time_t _current;
};

#endif
