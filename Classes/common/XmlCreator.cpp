#include "XmlCreator.h"


XmlCreator* g_xmlCreator = NULL;

XmlCreator::XmlCreator(void)
{
}


XmlCreator::~XmlCreator(void)
{
}

XmlCreator* XmlCreator::getInstance() {

	if(g_xmlCreator == NULL) {
		g_xmlCreator = new XmlCreator();
	}
	return g_xmlCreator;
}


string XmlCreator::convertString(UserInfo* info) {

	xml_document xmlDoc;
	
	// add a custom declaration node

	xml_node xml =xmlDoc.prepend_child(pugi::node_declaration);
	xml.append_attribute("version") = "1.0";
	xml.append_attribute("encoding") = "UTF-8";

	
	xml_node userInfo =xmlDoc.append_child("userInfo");
	
	userInfo.append_attribute("currentStage") = info->getCurrentStage();
	userInfo.append_attribute("facebookId") = info->getFacebookId().c_str();
	userInfo.append_attribute("gold") = info->getGold();
	userInfo.append_attribute("totalGold") = info->getTotalGold();
	char tempData[15];
	sprintf(tempData, "%.f", info->getLastVisitDate());
	userInfo.append_attribute("lastVisitDate") = tempData;
	userInfo.append_attribute("name") = info->getName().c_str();
	userInfo.append_attribute("guestId") = info->getGuestId().c_str();
	sprintf(tempData, "%ld", info->getId());
	userInfo.append_attribute("id") = tempData;
	
	
	xml_node heartInfo =userInfo.append_child("heartInfo");
	
	heartInfo.append_attribute("chargeHeartTime") = info->getHeartInfo()->getChargeHeartTime().c_str();
	heartInfo.append_attribute("heartCount") = info->getHeartInfo()->getHeartCount();



	xml_node stageScoreInfo = userInfo.append_child("stageScoreInfo");
	xml_node endlessScoreInfo = userInfo.append_child("endlessScoreInfo");
	xml_node userUpgradeInfo = userInfo.append_child("userUpgradeInfo");
	//_endlessScoreInfo

	for(int indexI = 0 ; indexI < info->getStageScoreInfoList().size() ;++indexI ){

		StageScoreInfo& scoreInfo = info->getStageScoreInfoList()[indexI];

		xml_node scoreInfoNode = stageScoreInfo.append_child("scoreInfo");
		scoreInfoNode.append_attribute("stage") = scoreInfo.getStage();
		scoreInfoNode.append_attribute("maxCombo") = scoreInfo.getMaxCombo();
		scoreInfoNode.append_attribute("maxScore") = scoreInfo.getMaxScore();
	}

	StageScoreInfo& endlessInfo = info->getEndlessScoreInfo();
	endlessScoreInfo.append_attribute("stage") = endlessInfo.getStage();
	endlessScoreInfo.append_attribute("maxCombo") = endlessInfo.getMaxCombo();
	endlessScoreInfo.append_attribute("maxScore") = endlessInfo.getMaxScore();
	endlessScoreInfo.append_attribute("miter") = endlessInfo.getMiter();
	endlessScoreInfo.append_attribute("useItemCount") = endlessInfo.getItemCount();

	for(map<string, UserUpgradeInfo>::iterator iter = info->getUserUpgradeInfoMap().begin();
		iter != info->getUserUpgradeInfoMap().end() ;++iter) {
		UserUpgradeInfo& upgradeInfoModel = iter->second;

		xml_node upgradeInfo = userUpgradeInfo.append_child("upgradeInfo");

		upgradeInfo.append_attribute("name") = upgradeInfoModel.getItemInfo()->getName().c_str();
		upgradeInfo.append_attribute("iconName") = upgradeInfoModel.getItemInfo()->getIconName().c_str();
		upgradeInfo.append_attribute("description") = upgradeInfoModel.getItemInfo()->getDescription().c_str();
		upgradeInfo.append_attribute("price") = upgradeInfoModel.getItemInfo()->getPrice();
		upgradeInfo.append_attribute("id") = upgradeInfoModel.getItemInfo()->getId();

		upgradeInfo.append_attribute("upgradeCount") = upgradeInfoModel.getUpgradeCount();
	}
	stringstream ss(stringstream::in | stringstream::out);
	xmlDoc.save(ss);

	string returnStr = ss.str();

	ss.clear();


	return returnStr;
}
