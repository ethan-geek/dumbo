#include "HiHighJsonConvecter.h"

HiHighJsonConvecter* g_JsonConverter = NULL;

HiHighJsonConvecter::HiHighJsonConvecter(void)
{
}


HiHighJsonConvecter::~HiHighJsonConvecter(void)
{
}

HiHighJsonConvecter* HiHighJsonConvecter::sharedJsonConverter() {
	if( g_JsonConverter == NULL) {
		g_JsonConverter = new HiHighJsonConvecter();
	}
	return g_JsonConverter;
}


UserInfo* HiHighJsonConvecter::convertUserInfo(string jsonString) {
    
	UserInfo* info = NULL;
	Value userInfo;
	Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, userInfo);
    
	if (! parsingSuccessful)
	{
		CCLog("parser failed : \n %s", jsonString.c_str());
		return info;
	}
	info = new UserInfo();
	convertJsonForUserInfo(userInfo, info);
    
	return info;
}


string HiHighJsonConvecter::convertStringForUpgradeInfo(UserUpgradeInfo* info) {
    
	Value userUpgradeInfo;
	userUpgradeInfo["upgradeCount"] = info->getUpgradeCount();
    
	Value member;
	member["facebookId"] = AGApplication::GetInstance()->getUserInfo()->getFacebookId();
    
	userUpgradeInfo["member"] = member;
    
	Value itemInfo;
    
	itemInfo["description"] = info->getItemInfo()->getDescription();
	itemInfo["name"] = info->getItemInfo()->getName();
	itemInfo["price"] = info->getItemInfo()->getPrice();
	itemInfo["id"] = info->getItemInfo()->getId();
    
	userUpgradeInfo["itemInfo"] = itemInfo;
    
	StyledWriter writer;
    
	return writer.write(userUpgradeInfo).c_str();
}

string HiHighJsonConvecter::convertStringForCrashLogInfo(AGDeviceInfo & info) {
    
	Value stageScore;
	stageScore["deviceModel"]  = info.deviceType;
  	stageScore["deviceVersion"]  = info.version;
  	stageScore["log"]  = info.log;
    
	StyledWriter writer;
	return writer.write(stageScore).c_str();
}

string HiHighJsonConvecter::convertStringForStageScoreInfo(StageScoreInfo* info) {
    
	Value stageScore;
    
	stageScore["stage"]  = info->getStage();
	stageScore["maxCombo"]  = info->getMaxCombo();
	//stageScore["maxScore"]  = info->getMaxScore();
	stageScore["maxMeter"]  = info->getMiter();
	//stageScore["useItemCount"]  = info->getItemCount();
    
	Value member;
	member["facebookId"] = AGApplication::GetInstance()->getUserInfo()->getFacebookId();
	member["guestId"] = AGApplication::GetInstance()->getUserInfo()->getGuestId();
	char temp[20];
	sprintf(temp, "%ld", AGApplication::GetInstance()->getUserInfo()->getId());
	member["id"] = temp;
    
	stageScore["member"] = member;
    

	StyledWriter writer;
	return writer.write(stageScore).c_str();
}

string HiHighJsonConvecter::convertStringForUserInfo(UserInfo* info) {
    
	Value userInfo = convertUserInfoForJson(info);
        
	StyledWriter writer;
	return writer.write(userInfo).c_str();
}

vector<UserInfo>* HiHighJsonConvecter::convertUserInfoList(string jsonString) {
    
	vector<UserInfo>* infoList = NULL;
	Value userInfoListJson;
	Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, userInfoListJson);
    
	if (! parsingSuccessful)
	{
		CCLog("parser failed : \n %s", jsonString.c_str());
		return NULL;
	}
    
	UserInfo userInfo;
	for(int indexI = 0; indexI < userInfoListJson.size(); ++indexI ) {
		userInfo = UserInfo();
        
		convertJsonForUserInfo(userInfoListJson[indexI], &userInfo);
        
		if(infoList == NULL) infoList = new vector<UserInfo>();
        
		infoList->push_back(userInfo);
	}
    
	return infoList;
}

void HiHighJsonConvecter::convertJsonForUserInfo(Value& userInfo, UserInfo* info) {
    
    
	info->setCurrentStage(userInfo.get("currentStage", 0).asInt());
	info->setFacebookId(userInfo.get("facebookId", "").asString());
	info->setGold(userInfo.get("gold", 0).asInt());
	info->setTotalGold(userInfo.get("totalGold", 0).asInt());
	info->setLastVisitDate(userInfo.get("lastVisitDate", 0).asFloat());
	info->setGuestId(userInfo.get("guestId", "").asString());
	info->setId(userInfo.get("id", 0).asUInt());

	Value endlessScoreInfo = userInfo["endlessScoreInfo"];
    
	if(endlessScoreInfo.empty() == false) {
		info->getEndlessScoreInfo().setStage(endlessScoreInfo.get("stage", 0).asInt());
		info->getEndlessScoreInfo().setMaxCombo(endlessScoreInfo.get("maxCombo", 0).asInt());
		info->getEndlessScoreInfo().setMaxScore(endlessScoreInfo.get("maxScore", 0).asInt());
		info->getEndlessScoreInfo().setMiter(endlessScoreInfo.get("maxMeter", 0).asFloat());
		info->getEndlessScoreInfo().setRank(endlessScoreInfo.get("rank", 0).asDouble());

	//	info->getEndlessScoreInfo().setItemCount(endlessScoreInfo.get("useItemCount", 0).asInt());
	}
	
	Value userUpgradeInfoArray = userInfo["userUpgradeInfoList"];
    
	if(userUpgradeInfoArray.empty() == false) {
		for(int indexI = 0; indexI < userUpgradeInfoArray.size(); ++indexI ) {
			Value upgradeInfoJson = userUpgradeInfoArray[indexI];
			Value itemInfoJson = upgradeInfoJson["itemInfo"];
            
			UserUpgradeInfo upgradeInfo;
			upgradeInfo.setUpgradeCount(upgradeInfoJson.get("upgradeCount", 0).asInt());
			ItemInfo itemInfo;
			itemInfo.setDescription(itemInfoJson.get("description", "").asString());
			itemInfo.setName(itemInfoJson.get("name", "").asString());
			itemInfo.setPrice(itemInfoJson.get("price", 0).asUInt());
			itemInfo.setId(itemInfoJson.get("id", 0).asUInt());
			upgradeInfo.setItemInfo(itemInfo);
            
			info->getUserUpgradeInfoMap()[itemInfo.getName()] = upgradeInfo;
            
		}
	}
	
    
}



vector<UserInfo>* HiHighJsonConvecter::convertScoreInfoList(string jsonString) {
    
	vector<UserInfo>* infoList = NULL;
	Value scoreInfoListJson;
	Reader reader;
	bool parsingSuccessful = reader.parse(jsonString, scoreInfoListJson);
    
	if (! parsingSuccessful)
	{
		CCLog("parser convertScoreInfoList failed : \n %s", jsonString.c_str());
		return NULL;
	}
    
	if(scoreInfoListJson.empty() || scoreInfoListJson.size() <= 0) {
		return NULL;
	}
    
	UserInfo userInfo;
    
	for(int indexI = 0 ; indexI < scoreInfoListJson.size(); ++indexI) {
        
		if(infoList == NULL) infoList = new vector<UserInfo>();
        
		Value scoreInfo = scoreInfoListJson[indexI];
		Value member = scoreInfo["member"];
		userInfo = UserInfo();
        
		userInfo.getEndlessScoreInfo().setStage(scoreInfo.get("stage", 0).asInt());
		userInfo.getEndlessScoreInfo().setMaxCombo(scoreInfo.get("maxCombo", 0).asInt());
		userInfo.getEndlessScoreInfo().setMaxScore(scoreInfo.get("maxScore", 0).asInt());
		userInfo.getEndlessScoreInfo().setMiter(scoreInfo.get("maxMeter", 0).asFloat());
		//userInfo.getEndlessScoreInfo().setItemCount(scoreInfo.get("useItemCount", 0).asInt());
		userInfo.getEndlessScoreInfo().setRank(scoreInfo.get("rank", 0).asDouble());

		convertJsonForUserInfo(member, &userInfo);
        
		infoList->push_back(userInfo);
	}
    
    
	return infoList;
}


string HiHighJsonConvecter::convertStringForUserInfoByPaging(UserInfo* info, int pageIndex) {

	Value dto;

	dto["member"] = convertUserInfoForJson(info);
	dto["pageIndex"] = pageIndex;

	StyledWriter writer;
	return writer.write(dto).c_str();

}


Value HiHighJsonConvecter::convertUserInfoForJson(UserInfo* info) {
	Value userInfo;
	userInfo["currentStage"] = info->getCurrentStage();
	
	if(info->getFacebookId().compare("") != 0) {
		userInfo["facebookId"] = info->getFacebookId();
	}

	if(info->getGuestId().compare("") != 0) {
		userInfo["guestId"] = info->getGuestId();
	}
	if(info->getId() > 0 ) {
		char temp[20];
		sprintf(temp, "%ld",  info->getId());
		userInfo["id"] = temp;
	}
	
	
	
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


	return userInfo;
}