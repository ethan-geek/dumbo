#include "HiHighDaoSharedUserDefault.h"
#include "../model/UserInfo.h"
#include "../model/HeartInfo.h"
#include "../model/StageScoreInfo.h"
#include "../model/UserUpgradeInfo.h"
#include "../model/ItemInfo.h"
#include "../common/XmlCreator.h"
//#include "../lib/base64.h"
//#include "../lib/McbDES2.hpp"
#include "../common/HHSecurity.h"


#define DES_SIZE		"SAVE_SIZE"
#define TEMP			"TEMP"
#define SAVE_FILE		"sv.dt"

HiHighDaoSharedUserDefault::HiHighDaoSharedUserDefault(void)
{
	_application = AGApplication::GetInstance();
}


HiHighDaoSharedUserDefault::~HiHighDaoSharedUserDefault(void)
{
}

void HiHighDaoSharedUserDefault::init() {

	string userInfoStr =loadFile();
	CCLog("HiHighDaoSharedUserDefault init %s", userInfoStr.c_str());
	//userInfoStr = base64_decode(userInfoStr);
	
	if (userInfoStr.c_str() == NULL || userInfoStr.c_str() == 0 || userInfoStr == ""){
		CCLog("HiHighDaoSharedUserDefault init if");
		UserInfo userInfo;
		userInfoStr = XmlCreator::getInstance()->convertString(&userInfo);

		//string userInfoStr = base64_encode(reinterpret_cast<const unsigned char*>(userInfoStr.c_str()), userInfoStr.length());

		saveFile(userInfoStr);

		//CCUserDefault::sharedUserDefault()->setStringForKey(XML_STORAGE, userInfoStr);
	}

		UserInfo* userInfo = new UserInfo();
		_application->setUserInfo(userInfo);

		xml_document userInfoDoc;

		userInfoDoc.load_buffer(userInfoStr.c_str(), userInfoStr.size());
		xml_node rootNode = userInfoDoc.child("userInfo");
		userInfo->setCurrentStage(rootNode.attribute("currentStage").as_int());

		userInfo->setFacebookId(rootNode.attribute("facebookId").as_string());
		userInfo->setGold(rootNode.attribute("gold").as_int());
		userInfo->setTotalGold(rootNode.attribute("totalGold").as_int());
		userInfo->setLastVisitDate(rootNode.attribute("lastVisitDate").as_float());
		userInfo->setName(rootNode.attribute("name").as_string());
		userInfo->setGuestId(rootNode.attribute("guestId").as_string());
		userInfo->setId(rootNode.attribute("id").as_uint());

		xml_node heartNode = rootNode.child("heartInfo");
		HeartInfo* heartInfo = userInfo->getHeartInfo();
		heartInfo->setHeartCount(heartNode.attribute("heartCount").as_int());
		heartInfo->setChargeHeartTime(heartNode.attribute("chargeHeartTime").as_string());


		xml_node stageScoreNode = rootNode.child("stageScoreInfo");



		StageScoreInfo stageInfo;
		UserUpgradeInfo upgradeInfo;

		for (xml_node scoreInfoNode = stageScoreNode.child("scoreInfo"); scoreInfoNode; scoreInfoNode = scoreInfoNode.next_sibling("scoreInfo"))
		{
			stageInfo.setStage(scoreInfoNode.attribute("stage").as_int());
			stageInfo.setMaxCombo(scoreInfoNode.attribute("maxCombo").as_int());
			stageInfo.setMaxScore(scoreInfoNode.attribute("maxScore").as_int());

			userInfo->setStageScoreInfo(stageInfo);
		}

		xml_node endlessScoreNode = rootNode.child("endlessScoreInfo");
		userInfo->getEndlessScoreInfo().setStage(endlessScoreNode.attribute("stage").as_int());
		userInfo->getEndlessScoreInfo().setMaxScore(endlessScoreNode.attribute("maxScore").as_int());
		userInfo->getEndlessScoreInfo().setMaxCombo(endlessScoreNode.attribute("maxCombo").as_int());
		userInfo->getEndlessScoreInfo().setMiter(endlessScoreNode.attribute("miter").as_int());
		userInfo->getEndlessScoreInfo().setItemCount(endlessScoreNode.attribute("useItemCount").as_int());
		
		xml_node userUpgradeNode = rootNode.child("userUpgradeInfo");

		ItemInfo itemInfo;

		for (xml_node upgradeInfoNode = userUpgradeNode.child("upgradeInfo"); upgradeInfoNode; upgradeInfoNode = upgradeInfoNode.next_sibling("upgradeInfo"))
		{
			itemInfo.setName(upgradeInfoNode.attribute("name").as_string());
			itemInfo.setIconName(upgradeInfoNode.attribute("iconName").as_string());
			itemInfo.setDescription(upgradeInfoNode.attribute("description").as_string());
			itemInfo.setPrice(upgradeInfoNode.attribute("price").as_int());
			itemInfo.setId(upgradeInfoNode.attribute("id").as_int());


			upgradeInfo.setUpgradeCount(upgradeInfoNode.attribute("upgradeCount").as_int());
			upgradeInfo.setItemInfo(itemInfo);

			userInfo->setUserUpgradeInfo(upgradeInfo);
		}
}

UserInfo* HiHighDaoSharedUserDefault::selectUserInfo() {

	UserInfo* userInfo = NULL;

	//string xmlStr = CCUserDefault::sharedUserDefault()->getStringForKey(XML_STORAGE);
	int bSize = CCUserDefault::sharedUserDefault()->getIntegerForKey(DES_SIZE, 0);
	if(bSize <= 0) {
		init();
	}

	//call create UserInfo
	userInfo = _application->getUserInfo();

	return userInfo;
;
}


vector<UserUpgradeInfo*>* HiHighDaoSharedUserDefault::selectUpgradeInfoList(){

	return NULL;
}
void HiHighDaoSharedUserDefault::updateUpgradeInfo(UserUpgradeInfo info){
	updateXml();
}

int HiHighDaoSharedUserDefault::selectGold(){
	return 0;
}
void HiHighDaoSharedUserDefault::updateGold(int gold){
	updateXml();
}

HeartInfo* HiHighDaoSharedUserDefault::selectHeartInfo(){
	return NULL;
}

void HiHighDaoSharedUserDefault::updateHeartInfo(HeartInfo* heartInfo){
	updateXml();
}

int HiHighDaoSharedUserDefault::selectCurrentStage(){

	return 0;
}
void HiHighDaoSharedUserDefault::updateCurrentStage(int currentStatge){
	updateXml();
}

StageScoreInfo* HiHighDaoSharedUserDefault::selectStageScoreInfo(){
	return NULL;
}

void HiHighDaoSharedUserDefault::updateScoreInfo(StageScoreInfo info){

	updateXml();
}


unsigned char * lpKey1 = (unsigned char*)"733201513";
unsigned char * lpKey2 = (unsigned char*)"93528010";




void HiHighDaoSharedUserDefault::updateXml() {


	 time(&_current);
	 ostringstream os;
	 os << _current;
	 _application->getUserInfo()->setLastVisitDate(atof(os.str().c_str()));
	 os.clear();

	string str = XmlCreator::getInstance()->convertString(_application->getUserInfo());
	CCLog("updateXml %s", str.c_str());

	saveFile(str);

}


void HiHighDaoSharedUserDefault::updateUserInfo(UserInfo* info) 
{
	updateXml();
}


void HiHighDaoSharedUserDefault::saveFile(string str) {
CCLog("HiHighDaoSharedUserDefault saveFile");
	
CCLog("before %s", str.c_str());
	string end = HHSecurity::getInstance()->Encryption("", str);
	CCLog("after %s", end.c_str());
	CCUserDefault::sharedUserDefault()->setStringForKey(XML_STORAGE, end);

	
	/*string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	filePath += SAVE_FILE;

	ofstream ofs;
	ofs.open(filePath.c_str(), ios::out | ios::binary);

	if(ofs.is_open()) {
		ofs << str << endl;
		ofs.close();
	}*/



	//const unsigned char* result = HHSecurity::getInstance()->Encryption(DES_SIZE,str);
	//int bSize = CCUserDefault::sharedUserDefault()->getIntegerForKey(DES_SIZE);
	//string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	//CCLog("des result size : %d, value :  %s", bSize, result);
	//
	//filePath += "dumbo.dat";
	//

	//string temp = HHSecurity::getInstance()->Decryption(DES_SIZE,result);
	//CCLog("save after des %s", temp.c_str());

	//typedef std::basic_ofstream<unsigned char, std::char_traits<unsigned char> > uofstream ;
	////basic_ofstream<unsigned char> file_stream;
	//uofstream file_stream;

	//file_stream.open(filePath.c_str(),ios::out | ios::binary);
	//if (!file_stream.is_open()) {
	//	CCLog("Can't open input file !\n");
	//	return;
 //   }
 //   else{
	//	file_stream.write(result, bSize);
 //   }
	//delete[] result;

	//if(file_stream.is_open()) {
	//	file_stream.close();
	//}

	//string ddd = loadFile();
	//CCLog("file load after des %s", ddd.c_str());

}
string HiHighDaoSharedUserDefault::loadFile() {
	CCLog("HiHighDaoSharedUserDefault loadFile");
	//string returnStr = "";

	//int bSize = CCUserDefault::sharedUserDefault()->getIntegerForKey(DES_SIZE, 0);
	//if(bSize != 0 ) {
	//	CCLog("HiHighDaoSharedUserDefault loadFile in");
	//	
	//	unsigned char* readData = (unsigned char*)malloc(sizeof(unsigned char) * (bSize+1));
	//	string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	//	filePath += "dumbo.dat";
 // 
	//	typedef std::basic_ifstream<unsigned char, std::char_traits<unsigned char> > iofstream ;
	//	//basic_ifstream<unsigned char> file_stream2;
	//	iofstream file_stream2;


	//	file_stream2.open(filePath.c_str(),ios::in | ios::binary);
	//	if (!file_stream2.is_open()) {
	//		cout << stderr << "Can't open input file !\n";
	//		exit(1);
	//	}
	//	else{
	//		file_stream2.read(readData,bSize);
	//		readData[bSize] = '\0';
	//	}

	//	if(file_stream2.is_open()) {
	//		file_stream2.close();
	//	}

	//	CCLog("load result %s", readData);

	//	returnStr = HHSecurity::getInstance()->Decryption(DES_SIZE,readData);
	//	CCLog("load des %d %s",bSize, returnStr.c_str());
	//	delete[] readData;
	//}

	/*string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	filePath += SAVE_FILE;

	string decodeBefore;

	ifstream ifs;
	ifs.open(filePath.c_str(), ios::in | ios::binary);

	if(ifs.is_open()) {
		ifs >> decodeBefore;
		decodeBefore += '\0';
		ifs.close();
	}*/
	

	string decodeBefore = CCUserDefault::sharedUserDefault()->getStringForKey(XML_STORAGE, "");
	if(decodeBefore.compare("") == 0) {
		return decodeBefore;
	}
	CCLog("before %s", decodeBefore.c_str());
	string end = HHSecurity::getInstance()->Decryption("", decodeBefore);
	CCLog("after %s", end.c_str());
	return end;
}
