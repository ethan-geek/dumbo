#include "HiHighConnector.h"

#include "../helper/AndroidHelper.h"

HiHighConnector* g_connector = NULL;

HiHighConnector::HiHighConnector(void)
{
}


HiHighConnector::~HiHighConnector(void)
{
}



HiHighConnector* HiHighConnector::sharedConnector() {

	if(g_connector == NULL) {
		g_connector = new HiHighConnector();
	}
	return g_connector;
}




void HiHighConnector::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {

	if (!response)
	{
		return;
	}
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	// Check the HTTP Status Code
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);

	// A connection failure
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		return;
	}


	vector<char> *buffer = response->getResponseData();
	std::string rest;
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		rest+=(*buffer)[i];

	}
	rest+='\0';


}



void HiHighConnector::requestServer(CCObject* object, const char* url, const char* postData, SEL_HttpResponse pSelector) {


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	string* str = new string();
	string temp  = SERVER_URL;
	temp += url;
	*str = android_connectServer(temp.c_str(), postData,(int)5000);
	CCLog("android_connectServer after %s", str->c_str());
	(object->*pSelector)(NULL, (CCHttpResponse*)str);

	return;
#endif

	vector<string> headers;
	headers.push_back("Content-Type: application/json; charset=utf-8");


    CCHttpClient::getInstance()->setTimeoutForConnect(5);
	CCHttpRequest* request = new CCHttpRequest();
	CCLog("postData : %s", postData);
	char* test = "{\"maxCombo\" : 200,\"maxScore\" : 99999,\"stage\" : -1}";
	string strUrl = SERVER_URL;
	strUrl += url;
	request->setUrl(strUrl.c_str());
	request->setRequestType(CCHttpRequest::kHttpPost);
	if(object == NULL) {
		object = CCSprite::create();
		request->setUserData(object);
	}
	request->setResponseCallback(object, pSelector);
	request->setRequestData(postData, strlen(postData));
	request->setTag("POST Request");
	request->setHeaders(headers);
	
	CCHttpClient::getInstance()->send(request);
	request->release();
}

bool HiHighConnector::checkRespose(CCHttpResponse* response) {


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	return true;
#endif

	if (!response)
	{
		return false;
	}
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	// Check the HTTP Status Code
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);

	// A connection failure
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		return false;
	}

	return true;
}

void HiHighConnector::convertString(CCHttpResponse* response, string& jsonStr) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLog("android convertString in");
	jsonStr = *((string*)response);
	CCLog("android convertString jsonStr after");
	delete ((string*)response);
	CCLog("android convertString out");
	return;
#endif

	vector<char> *buffer = response->getResponseData();

	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		jsonStr+=(*buffer)[i];


	}
	if(jsonStr.empty() == false) {
		jsonStr+='\0';
	}

}

void HiHighConnector::sendUpgradeInfo(UserUpgradeInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGISTUSERUPGRADE, HiHighJsonConvecter::sharedJsonConverter()->convertStringForUpgradeInfo(info).c_str(), pSelector);
}
void HiHighConnector::sendScore(StageScoreInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGISTSCORE, HiHighJsonConvecter::sharedJsonConverter()->convertStringForStageScoreInfo(info).c_str(), pSelector);
}
void HiHighConnector::sendCrashLog(AGDeviceInfo& info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGISTLOG, HiHighJsonConvecter::sharedJsonConverter()->convertStringForCrashLogInfo(info).c_str(), pSelector);
}



void HiHighConnector::sendUserInfo(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGISTMEMBER, HiHighJsonConvecter::sharedJsonConverter()->convertStringForUserInfo(info).c_str(), pSelector);
}
void HiHighConnector::sendFacebookFriendList(string jsonList, CCObject* object, SEL_HttpResponse pSelector) {

	Value jsonObject;
	jsonObject["fbId"] = AGApplication::GetInstance()->getUserInfo()->getFacebookId();

	Value friendsList;


	//_fbFriendMap
	map<string, FbFriend>::iterator iter;

	CCLog("map size %d", _fbFriendMap.size());

	for(iter = _fbFriendMap.begin(); iter != _fbFriendMap.end() ; ++iter) {
		Value fri;
		fri["id"] = iter->second.id;
		fri["name"] = iter->second.name;

		friendsList.append(fri);
	}


	jsonObject["friendList"] = friendsList;

	StyledWriter writer;

	requestServer(object, FBFRIENDSLIST, writer.write(jsonObject).c_str(), pSelector);
}

//remove
void HiHighConnector::requestRanking(string facebookId, CCObject* object, SEL_HttpResponse pSelector) {
	string temp = "facebookId=";
	temp += facebookId;
	requestServer(object, "url", temp.c_str(), pSelector);
}
void HiHighConnector::requestUserInfo(string facebookId, CCObject* object, SEL_HttpResponse pSelector) {

	requestServer(object, GETMEMBER, facebookId.c_str(), pSelector);
}


string HiHighConnector::convertJsonForFbFriends(string json) {

	CCLog("convertJsonForFbFriends");
	Value root;
	Reader reader;
	bool parsingSuccessful = reader.parse(json, root);

	if (! parsingSuccessful)
	{
		CCLog("parser failed : \n %s", json.c_str());
		return "";
	}

	Value datas  = root["data"];
	Value paging = root["paging"];

	for(int indexI = 0 ; indexI < datas.size() ;++indexI) {
		Value data = datas[indexI];
		FbFriend ff;

		ff.id = data.get("id", "").asString();
		ff.name = data.get("name", "").asString();


		_fbFriendMap[ff.id] = ff;
	}
	CCLog("map insert size %d", _fbFriendMap.size());

	return paging.get("next", "").asString();
}


string HiHighConnector::getFBName(string& fbId)  {

	if(AGApplication::GetInstance()->getUserInfo()->getFacebookId().compare(fbId) == 0) {
		return AGApplication::GetInstance()->getUserInfo()->getName();
	}

	return _fbFriendMap[fbId].name;

}

int HiHighConnector::getFbFriendCount() {
	return _fbFriendMap.size();
}

void HiHighConnector::initFbFriends() {
	_fbFriendMap.clear();
}


void HiHighConnector::registGuestMember(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGIST_GUEST_MEMBER, HiHighJsonConvecter::sharedJsonConverter()->convertStringForUserInfo(info).c_str(), pSelector);
}
void HiHighConnector::modifyMember(UserInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, MODIFY_MEMBER, HiHighJsonConvecter::sharedJsonConverter()->convertStringForUserInfo(info).c_str(), pSelector);
}
void HiHighConnector::registGuestScore(StageScoreInfo* info, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, REGIST_GUEST_SCORE, HiHighJsonConvecter::sharedJsonConverter()->convertStringForStageScoreInfo(info).c_str(), pSelector);
}

string test(UserInfo* info) {

	Value userInfo;
    
	userInfo["currentStage"] = info->getCurrentStage();
	
	if(info->getFacebookId().compare("") != 0) {
		userInfo["facebookId"] = info->getFacebookId();
	}
	
	userInfo["guestId"] = info->getGuestId();
	char temp[20];
	sprintf(temp, "%ld",  info->getId());
	userInfo["id"] = temp;

	
	
	userInfo["gold"] = info->getGold();
	userInfo["totalGold"] = info->getTotalGold();

    
	Value member;
	member["facebookId"] = info->getFacebookId();
	
    
	StageScoreInfo& scoreInfo = info->getEndlessScoreInfo();
    
	Value endlessScoreInfo;
	endlessScoreInfo["stage"] = scoreInfo.getStage();
	endlessScoreInfo["maxCombo"] = scoreInfo.getMaxCombo();
	//endlessScoreInfo["maxScore"] = scoreInfo.getMaxScore();
	endlessScoreInfo["maxMeter"] = scoreInfo.getMiter();
	//endlessScoreInfo["useItemCount"] = scoreInfo.getItemCount();
	endlessScoreInfo["member"] = member;
    

	userInfo["endlessScoreInfo"] = endlessScoreInfo;
    

    
	map< string, UserUpgradeInfo >::iterator Iter_Pos;
    
	Value userUpgradeInfoList;
    
	for( Iter_Pos = info->getUserUpgradeInfoMap().begin(); Iter_Pos != info->getUserUpgradeInfoMap().end(); ++Iter_Pos) {
		Value userUpgradeInfo;
		userUpgradeInfo["upgradeCount"] = info->getUserUpgradeInfoMap().at(Iter_Pos->first).getUpgradeCount();
		Value valInfo;
		valInfo["description"] = info->getUserUpgradeInfoMap().at(Iter_Pos->first).getItemInfo()->getDescription();
		valInfo["name"] = info->getUserUpgradeInfoMap().at(Iter_Pos->first).getItemInfo()->getName();
		valInfo["price"] = info->getUserUpgradeInfoMap().at(Iter_Pos->first).getItemInfo()->getPrice();
		valInfo["id"] = info->getUserUpgradeInfoMap().at(Iter_Pos->first).getItemInfo()->getId();
		userUpgradeInfo["itemInfo"] = valInfo;
		userUpgradeInfo["member"] = member;
		userUpgradeInfoList.append(userUpgradeInfo);
	}
    
	userInfo["userUpgradeInfoList"] = userUpgradeInfoList;
    

	Value dto;

	dto["member"] = userInfo;
	dto["pageIndex"] = 0;

	StyledWriter writer;
	return writer.write(dto).c_str();
}

void HiHighConnector::allRankList(UserInfo* info, int pageIndex, CCObject* object, SEL_HttpResponse pSelector) {
	requestServer(object, ALL_RANK_LIST, HiHighJsonConvecter::sharedJsonConverter()->convertStringForUserInfoByPaging(info, pageIndex).c_str(), pSelector);
}
