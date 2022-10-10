

#if !defined(HH_HIHIGHCONNECTOR)
#define HH_HIHIGHCONNECTOR



#include "./HiHighCommon.h"

#include "../model/UserInfo.h"
#include "../model/AGDeviceInfo.h"
#include "./HiHighJsonConvecter.h"

using namespace CSJson;

//#define SERVER_URL			"http://192.168.1.80:8380/dumbo/dumbo"
#define SERVER_URL			"https://www.atgame.net/dumbo/api/dumbo"
//#define SERVER_URL			"https://dumbo.atgame.net/api/dumbo"
//#define SERVER_URL			"https://hihigh.atgame.net/hihigh_api/"

#define	FBFRIENDSLIST			"/fb/friendsList"
#define REGISTUSERUPGRADE		"/regist/userUpgrade"
#define REGISTSCORE				"/regist/score"
#define GETMEMBER				"/read/member"
#define REGISTMEMBER			"/regist/member"
#define REGISTLOG				"/regist/crashlog"

#define REGIST_GUEST_MEMBER		"/regist/registGuestMember"
#define MODIFY_MEMBER			"/modify/modifyMember"
#define REGIST_GUEST_SCORE		"/regist/guestScore"
#define ALL_RANK_LIST			"/list/allRankList"


struct FbFriend {
	FbFriend() : id(""), name(""), profileUrl("") {

	}
	string id;
	string name;
	string profileUrl; 
};

class HiHighConnector : public CCObject
{
public:
	static HiHighConnector* sharedConnector();
	~HiHighConnector(void);

	void requestServer(CCObject* object, const char* url, const char* postData, SEL_HttpResponse pSelector);
	bool checkRespose(CCHttpResponse* response);
	void convertString(CCHttpResponse* response, string& jsonStr);


	void sendCrashLog(AGDeviceInfo& info, CCObject* object, SEL_HttpResponse pSelector);
	void sendUpgradeInfo(UserUpgradeInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void sendScore(StageScoreInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void sendUserInfo(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void sendFacebookFriendList(string jsonList, CCObject* object, SEL_HttpResponse pSelector);
	void requestRanking(string facebookId, CCObject* object, SEL_HttpResponse pSelector);
	void requestUserInfo(string facebookId, CCObject* object, SEL_HttpResponse pSelector);

	string convertJsonForFbFriends(string json);

	string getFBName(string& fbId);
	

	int getFbFriendCount();

	void initFbFriends();


	void registGuestMember(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void modifyMember(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void registGuestScore(StageScoreInfo* info, CCObject* object, SEL_HttpResponse pSelector);
	void allRankList(UserInfo* info, int pageIndex, CCObject* object, SEL_HttpResponse pSelector);

private :



	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response);



	HiHighConnector(void);


	map<string, FbFriend> _fbFriendMap;
};

#endif
