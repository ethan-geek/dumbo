

#if !defined(HH_JSON_CONVERTER)
#define HH_JSON_CONVERTER

#include "./HiHighCommon.h"
#include "../model/UserInfo.h"
#include "../model/AGDeviceInfo.h"

using namespace CSJson;

class HiHighJsonConvecter
{
public:

	static HiHighJsonConvecter* sharedJsonConverter();

	HiHighJsonConvecter(void);
	~HiHighJsonConvecter(void);

	UserInfo* convertUserInfo(string jsonString);
	vector<UserInfo>* convertUserInfoList(string jsonString);

	vector<UserInfo>* convertScoreInfoList(string jsonString);

	
	string convertStringForUserInfo(UserInfo* info);

	string convertStringForUpgradeInfo(UserUpgradeInfo* info);
	string convertStringForStageScoreInfo(StageScoreInfo* info);
	string convertStringForCrashLogInfo(AGDeviceInfo & info) ;

	void convertJsonForUserInfo(Value& json, UserInfo* info);

	string convertStringForUserInfoByPaging(UserInfo* info, int pageIndex);
	Value convertUserInfoForJson(UserInfo* info);
};

#endif