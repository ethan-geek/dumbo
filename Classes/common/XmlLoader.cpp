//
//  XmlLoader.cpp
//  HighHi
//
//  Created by Jackdaw on 2014. 1. 24..
//
//

#include "XmlLoader.h"
#include "../model/CoinObject.h"
#include "../model/SuperItemObject.h"
#include "../model/FullCoinItemObject.h"
#include "../model/TrapObject.h"
#include "../model/FootBarObject.h"
#include "../model/FakeFootBarObject.h"
#include "../model/DynamicCoin.h"
#include "../model/WeighItemObject.h"
#include "../model/ShieldItemObject.h"
#include "../model/StarFishObject.h"
#include "../model/MagnetItemObject.h"
#include "../model/DoubleItemObject.h"
#include "../game/Hero.h"

#include <string>





#define GROUP_PATTERN_PATH		"patterns/grouppattern/"
#define STAGE_PATTERN_PATH		"patterns/stagepattern/"
#define RESOURCE_PATTERN_PATH	"patterns/pattern/"
#define PATTERN_STR				"pattern"
#define PATTERN_INFO_STR		"pattern_info.xml"

#define PATTERN_DIFFICULT		10

XmlLoader * g_inst = NULL;

XmlLoader::XmlLoader() : _stagePattern(NULL), _isFirstResource(false), _endlessCount(0) {
}



XmlLoader* XmlLoader::getInstance() {
	if (g_inst == NULL) {
		g_inst = new XmlLoader();
	}
	return g_inst;
}


void XmlLoader::loadingXMLFile(string file) {

	if(_stagePattern != NULL) {
		delete _stagePattern;
	}

	_stagePattern = new StagePattern();

	AGApplication::GetInstance()->setStagePattern(_stagePattern);

	xml_document stageDoc;



	unsigned char* stageBuffer = NULL;


	unsigned long bufferSize = 0;

	string tempPath = STAGE_PATTERN_PATH;

	stageBuffer = CCFileUtils::sharedFileUtils()->getFileData((tempPath+file).c_str(), "rb", &bufferSize);

	stageDoc.load_buffer(stageBuffer, bufferSize);
	xml_node rootNode = stageDoc.child("stagePattern");
	xml_node patternsNode = rootNode.child("patterns");

	_stagePattern->_height = rootNode.attribute("height").as_float();

	CC_SAFE_DELETE(stageBuffer);

	parseGroup(patternsNode);



}

void XmlLoader::parseGroup(xml_node& patternsNode) {

	xml_document groupDoc;
	GroupPattern* groupPattern;
	unsigned char* groupBuffer = NULL;
	unsigned long bufferSize = 0;

	for(xml_node stageNodeItem = patternsNode.child("groupPattern"); stageNodeItem; stageNodeItem = stageNodeItem.next_sibling("groupPattern")) {
		groupPattern = new GroupPattern();
		groupPattern->_xmlName = stageNodeItem.attribute("name").as_string();
		groupPattern->_offset = stageNodeItem.attribute("offset").as_float();
		groupPattern->_width = stageNodeItem.attribute("width").as_float();

		_isFirstResource = true;


		string tempGroupPath = GROUP_PATTERN_PATH;

		groupBuffer = CCFileUtils::sharedFileUtils()->getFileData((tempGroupPath+groupPattern->_xmlName).c_str(), "rb", &bufferSize);

		groupDoc.load_buffer(groupBuffer, bufferSize);
		xml_node groupRootNode = groupDoc.child("groupPattern");
		xml_node groupPatternsNode = groupRootNode.child("patterns");

		CC_SAFE_DELETE(groupBuffer);

		parseResource(groupPattern, groupPatternsNode);

		_stagePattern->_groupList.push_back(groupPattern);
	}
}
void XmlLoader::parseResource(GroupPattern* groupPattern, xml_node& groupPatternsNode) {

	xml_document resourceDoc;
	unsigned char* resourceBuffer = NULL;
	ResourcePattern* resourcePattern;

	unsigned long bufferSize = 0;

	for(xml_node groupNodeItem = groupPatternsNode.child("pattern"); groupNodeItem; groupNodeItem = groupNodeItem.next_sibling("pattern")) {
		resourcePattern = new ResourcePattern();
		resourcePattern->_xmlName = groupNodeItem.attribute("name").as_string();
		resourcePattern->_offset = groupNodeItem.attribute("offset").as_float();
		resourcePattern->_width = groupNodeItem.attribute("width").as_float();
		resourcePattern->_height = groupNodeItem.attribute("height").as_float();

		string tempResourcePath = RESOURCE_PATTERN_PATH;

		resourceBuffer = CCFileUtils::sharedFileUtils()->getFileData((tempResourcePath+resourcePattern->_xmlName).c_str(), "rb", &bufferSize);

		resourceDoc.load_buffer(resourceBuffer, bufferSize);
		CC_SAFE_DELETE(resourceBuffer);
		parseInteraction(resourceDoc, groupPattern, resourcePattern);
	}
}

void XmlLoader::parseInteraction(xml_document& resourceDoc, GroupPattern* groupPattern, ResourcePattern* resourcePattern) {
	xml_node resourceRootNode = resourceDoc.child("pattern");

	xml_node coins = resourceRootNode.child("coins");
	xml_node items = resourceRootNode.child("items");
	xml_node traps = resourceRootNode.child("traps");
	xml_node footbarss = resourceRootNode.child("footBars");
	xml_node starfishes = resourceRootNode.child("starfishes");
	resourcePattern->_height = resourceRootNode.attribute("height").as_float();

	interactionObject* object;

	parseCoin(coins, groupPattern, resourcePattern);

	parseItem(items, groupPattern, resourcePattern);

	parseTrap(traps, groupPattern, resourcePattern);

	parseFootbar(footbarss, groupPattern, resourcePattern);

	parseStarfish(starfishes, groupPattern, resourcePattern);

	resourcePattern->_height += resourcePattern->_offset;

	if(_isFirstResource) {
		if(groupPattern != NULL) {
			resourcePattern->_height += groupPattern->_offset;
		}
	}

	if(groupPattern != NULL) {
		groupPattern->_height += resourcePattern->_height;
		groupPattern->_resourceList.push_back(resourcePattern);
	}

	_isFirstResource = false;
}

void XmlLoader::parseCoin(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern) {
	if(coins.select_nodes("coin").size() > 0 ) {

		interactionObject* object;

		for(xml_node nodeItem = coins.child("coin"); nodeItem; nodeItem = nodeItem.next_sibling("coin")) {

			if(strcmp(nodeItem.attribute("type").as_string(), "coin") == 0) {
				object = new CoinObject();
				object->setObjectType(INTERACTION_OBJECT_TYPE_COIN);
				((CoinObject*)object)->setCoinSizeType(nodeItem.attribute("imagePath").as_string());

			}
			else if(strcmp(nodeItem.attribute("type").as_string(), "dynamicCoin") == 0) {

				object = new DynamicCoin();

				object->setObjectType(INTERACTION_OBJECT_TYPE_COIN);
				((DynamicCoin*)object)->setCoinSizeType(nodeItem.attribute("imagePath").as_string());
				((DynamicCoin*)object)->setVelocity(nodeItem.attribute("velocity").as_float());
				if(strcmp(nodeItem.attribute("moveType").as_string(), "circle") == 0) {
					((DynamicCoin*)object)->setCoinType(COIN_TYPE_CIRCLE);
				}
				else if(strcmp(nodeItem.attribute("moveType").as_string(), "patrol") == 0) {
					((DynamicCoin*)object)->setCoinType(COIN_TYPE_PATROL);
				}

			}
			setInteractionObject(object, nodeItem, groupPattern, resourcePattern);
			resourcePattern->_interactionList.push_back(object);
		}

	}
}
void XmlLoader::parseItem(xml_node& items, GroupPattern* groupPattern, ResourcePattern* resourcePattern) {
	if(items.select_nodes("item").size() > 0 ) {
		
		if(AGApplication::GetInstance()->_hero->isStatus(HERO_STATUS_TYPE_STARTJUMP)
			|| AGApplication::GetInstance()->_hero->isStatus(HERO_STATUS_TYPE_DEFAULT)) {
			return;
		}

		interactionObject* object = NULL;

		for(xml_node nodeItem = items.child("item"); nodeItem; nodeItem = nodeItem.next_sibling("item")) {

			if(strcmp(nodeItem.attribute("type").as_string() , "superItem") == 0) {
				object = new SuperItemObject();
			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "fullCoin") == 0) {
				object = new FullCoinItemObject();
			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "shield") == 0) {
				object = new ShieldItemObject();
			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "umbrella") == 0) {
				object = new WeighItemObject();
			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "doubleItem") == 0) {
				object = new DoubleItemObject();
			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "magnet") == 0) {
				object = new MagnetItemObject();
			}

			else {
				if(object == NULL) {
					continue;
				}
			}

			setInteractionObject(object, nodeItem, groupPattern, resourcePattern);
			resourcePattern->_interactionList.push_back(object);

		}

	}
}
void XmlLoader::parseTrap(xml_node& traps, GroupPattern* groupPattern, ResourcePattern* resourcePattern) {
	if(traps.select_nodes("trap").size() > 0 ) {
		interactionObject* object;
		for(xml_node nodeItem = traps.child("trap"); nodeItem; nodeItem = nodeItem.next_sibling("trap")) {

			if(strcmp(nodeItem.attribute("type").as_string() , "trap") == 0) {
				object = new TrapObject();
				object->setObjectType(INTERACTION_OBJECT_TYPE_TRAP);
			}
			setInteractionObject(object, nodeItem, groupPattern, resourcePattern);
			resourcePattern->_interactionList.push_back(object);

		}
	}
}
void XmlLoader::parseFootbar(xml_node& footbars, GroupPattern* groupPattern, ResourcePattern* resourcePattern) {
	if(footbars.select_nodes("footBar").size() >0 ) {

		interactionObject* object;

		for(xml_node nodeItem = footbars.child("footBar"); nodeItem; nodeItem = nodeItem.next_sibling("footBar")) {


			if(strcmp(nodeItem.attribute("type").as_string() , "footBar") == 0) {
				object = new FootBarObject();
				object->setObjectType(INTERACTION_OBJECT_TYPE_FOOTBAR);

				((FootBarObject*)object)->setAngle(nodeItem.attribute("angle").as_float());

			}
			else if(strcmp(nodeItem.attribute("type").as_string() , "fakeFootBar") == 0) {
				object = new FakeFootBarObject();
				object->setObjectType(INTERACTION_OBJECT_TYPE_FAKE_FOOTBAR);

				((FakeFootBarObject*)object)->setAngle(nodeItem.attribute("angle").as_float());

			}


			setInteractionObject(object, nodeItem, groupPattern, resourcePattern);
			resourcePattern->_interactionList.push_back(object);
		}
	}
}

void XmlLoader::parseStarfish(xml_node& starfishes, GroupPattern* groupPattern, ResourcePattern* resourcePattern) { 
	if(starfishes.select_nodes("starfish").size() >0 ) {

		interactionObject* object;

		for(xml_node nodeItem = starfishes.child("starfish"); nodeItem; nodeItem = nodeItem.next_sibling("starfish")) {

			if(strcmp(nodeItem.attribute("type").as_string() , "starfish") == 0) {
				object = new StarFishObject();
				object->setObjectType(INTERACTION_OBJECT_TYPE_STARFISH);

			}
		
			setInteractionObject(object, nodeItem, groupPattern, resourcePattern);
			resourcePattern->_interactionList.push_back(object);
		}
	}
}


void XmlLoader::setInteractionObject(interactionObject* object, xml_node& nodeItem, GroupPattern* gp, ResourcePattern* rp) {

	float offset = rp->_offset;

	if(_isFirstResource) {
		if(gp != NULL) {
			offset += gp->_offset;
		}
	}

	object->setImageName(nodeItem.attribute("imagePath").as_string());
	CCPoint position = CCPoint(nodeItem.attribute("x").as_float(), nodeItem.attribute("y").as_float()+ offset);

	object->setPosition(position);

}


ResourcePattern* XmlLoader::getFullCoinPattern() {

	unsigned char* stageBuffer = NULL;

	unsigned long bufferSize = 0;

	string tempPath = RESOURCE_PATTERN_PATH;

	stageBuffer = CCFileUtils::sharedFileUtils()->getFileData((tempPath+"fullcoin.xml").c_str(), "rb", &bufferSize);

	xml_document fullCoinDoc;
	fullCoinDoc.load_buffer(stageBuffer, bufferSize);

	ResourcePattern* fullCoinPattern = new ResourcePattern();
	CC_SAFE_DELETE(stageBuffer);
	parseInteraction(fullCoinDoc, NULL, fullCoinPattern);

	return fullCoinPattern;
}

#define EASY 42
#define NORMAL_LOW 47
#define NORMAL_HIGH 55
#define HARD 60


int getDifficultPatternLevel(int value) {
    
    int difficultLevel = 3;
    if (value < EASY) {
        difficultLevel = 1;
    } else if (EASY < value && value <= NORMAL_LOW) {
        difficultLevel = 3;
    } else if (NORMAL_LOW < value && value <= NORMAL_HIGH) {
        difficultLevel = 2;
    } else if (NORMAL_HIGH < value && value <= HARD) {
        difficultLevel = 4;
    } else if(HARD < value){
        difficultLevel = 5;
    }
    return difficultLevel;
}


struct DifficultRandomRange {
    
    int offset;
    int range;
    
    void setRange(int o, int r) {
        offset = o;
        range = r;
    }
    
};

DifficultRandomRange getDifficultRange(int currentMeter) {
    
    // 1            ~300
    // 1,2          300 ~ 600
    // 1,2,3        600 ~ 1000
    // 2,3,4        1000 ~ 1500
    // 3,4,5        1500 ~ 2000
    // 4,5          2000 ~ 2500
    // 5            3000 ~
    
    DifficultRandomRange range;
    
    if(currentMeter < 300) {
        range.setRange(1, 1);
    } else if (300 < currentMeter && currentMeter < 600) {
        range.setRange(1, 2);
    } else if (600 < currentMeter && currentMeter < 1000) {
        range.setRange(1, 3);
    } else if (1000 < currentMeter && currentMeter < 1500) {
        range.setRange(2, 3);
    } else if (1500 < currentMeter && currentMeter < 2000) {
        range.setRange(3, 3);
    } else if (2000 < currentMeter && currentMeter < 2500) {
        range.setRange(4, 2);
    } else {
        range.setRange(5, 1);
    }
    
    return range;
}

ResourcePattern* XmlLoader::getUnlimitedPattern() { 
	
	if(_patternInfo.size() <= 0 ) {
		initPatternInfo();
	}


	unsigned char* stageBuffer = NULL;

	unsigned long bufferSize = 0;

	string tempPath = RESOURCE_PATTERN_PATH;
    
    DifficultRandomRange range = getDifficultRange(AGApplication::GetInstance()->getGameData()->getMiter());
    
	char temp[40];
	int difficult = AGApplication::GetInstance()->getRand() % range.range + range.offset;

	/*static int testIndex = 3;
	static int testNumber = 20;
    sprintf(temp, "%s_%02d_%02d.xml", PATTERN_STR, testIndex , testNumber);

	++testNumber;
	if(testNumber > _patternInfo[testIndex-1]) {
		++testIndex;
		if(testIndex > 5) testIndex = 1;
		testNumber = 1;
	}*/

	sprintf(temp, "%s_%02d_%02d.xml", PATTERN_STR, difficult , AGApplication::GetInstance()->getRand() % _patternInfo[difficult-1] + 1);
    stageBuffer = CCFileUtils::sharedFileUtils()->getFileData((tempPath + temp).c_str(), "rb", &bufferSize);

	xml_document patternDoc;
	patternDoc.load_buffer(stageBuffer, bufferSize);

	ResourcePattern* pattern = new ResourcePattern();
	CC_SAFE_DELETE(stageBuffer);
	parseInteraction(patternDoc, NULL, pattern);


	_patternData._patternName = temp;
	_patternData._patternHeight = pattern->_height;
	_patternData._patternCount = pattern->_interactionList.size();

	++_endlessCount;
	return pattern;
}


void XmlLoader::initPatternInfo() {


	unsigned char* buffer = NULL;
	unsigned long bufferSize = 0;

	string tempPath = RESOURCE_PATTERN_PATH;
	tempPath += PATTERN_INFO_STR;

	buffer = CCFileUtils::sharedFileUtils()->getFileData(tempPath.c_str(), "rb", &bufferSize);
	xml_document patternDoc;
	patternDoc.load_buffer(buffer, bufferSize);
	CC_SAFE_DELETE(buffer);

	xml_node patternInfos = patternDoc.child("patternInfos");
	for(xml_node patternInfo  = patternInfos.child("patternInfo"); patternInfo; patternInfo = patternInfo.next_sibling("patternInfo")) {
		_patternInfo.push_back(patternInfo.attribute("count").as_int());
	}
	

	return;

}

vector<ParallaxLayer>* XmlLoader::getParallaxLayerList() {

	if(_parallaxLayerList.size() != 0 ) {
		return &_parallaxLayerList;
	}

	unsigned char* buffer = NULL;
	unsigned long bufferSize = 0;

	ParallaxLayer paLayer;
	ObjectLayer ojLayer;
	ParallaxObject object;

	int type, x, y = 0;

	xml_document parallaxDoc;
	xml_node parallaxLayers;
	xml_node parallaxLayer;
	xml_node objectLayers;
	xml_node objectLayer;
	xml_node parallaxObjects;
	xml_node parallaxObject;

	string tempPath = "parallax/parallaxpattern.xml";

	buffer = CCFileUtils::sharedFileUtils()->getFileData(tempPath.c_str(), "rb", &bufferSize);
	
	parallaxDoc.load_buffer(buffer, bufferSize);
	CC_SAFE_DELETE(buffer);


	parallaxLayers = parallaxDoc.child("parallaxLayers");
	
	
	for( parallaxLayer  = parallaxLayers.child("parallaxLayer"); parallaxLayer; parallaxLayer = parallaxLayer.next_sibling("parallaxLayer")) {
		
		paLayer = ParallaxLayer();
		paLayer._zIndex = parallaxLayer.attribute("zIndex").as_int();
		paLayer._size = parallaxLayer.attribute("size").as_float();

		objectLayers =parallaxLayer.child("objectLayers");

		for(objectLayer = objectLayers.child("objectLayer") ; objectLayer; objectLayer = objectLayer.next_sibling("objectLayer") ) {

			ojLayer = ObjectLayer();
			ojLayer._speed = objectLayers.attribute("speed").as_float();
			parallaxObjects = objectLayer.child("parallaxObjects");

			for(parallaxObject = parallaxObjects.child("parallaxObject"); parallaxObject; parallaxObject = parallaxObject.next_sibling("parallaxObject")) {

				type = parallaxObject.attribute("type").as_int();
				x = parallaxObject.attribute("x").as_int();
				y = parallaxObject.attribute("y").as_int();

				object = ParallaxObject(type, x, y);

				ojLayer._pallaxObjectList.push_back(object);

			}

			paLayer._objectLayerList.push_back(ojLayer);

		}

		_parallaxLayerList.push_back(paLayer);
		
		
		
	}

	return &_parallaxLayerList;
}

void XmlLoader::initEndlessCount() {

	_endlessCount = 0;
}


Pattern_Data& XmlLoader::getPatternData()  {
	return _patternData;
}
