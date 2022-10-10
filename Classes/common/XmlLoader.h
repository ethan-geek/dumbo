//
//  XmlLoader.h
//  HighHi
//
//  Created by Jackdaw on 2014. 1. 24..
//
//

#ifndef __HighHi__XmlLoader__
#define __HighHi__XmlLoader__

#include <iostream>
#include <map>
#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "./HiHighCommon.h"
#include "../lib/pugixml.hpp"
#include "../model/interactionObject.h"
#include "../pattern/Pattern.h"
#include "../pattern/StagePattern.h"
#include "../pattern/GroupPattern.h"
#include "../pattern/ResourcePattern.h"


USING_NS_CC;
USING_NS_CC_EXT;


using namespace std;
using namespace pugi;


struct Pattern_Data {

	string _patternName;
	float _patternHeight;
	int _patternCount;

};

struct ParallaxObject {
	ParallaxObject() {};
	ParallaxObject(int type, int x, int y) {
		_type = type;
		_x = x;
		_y = y;
	}

	int _type;
	int _x;
	int _y;
};

struct ObjectLayer {
	float _speed;
	vector<ParallaxObject> _pallaxObjectList;
};

struct ParallaxLayer {
	int _zIndex;
	float _size;
	vector<ObjectLayer> _objectLayerList;
};


class XmlLoader {
    
public:
    void loadingXMLFile(string file);

    XmlLoader(); 
    static XmlLoader* getInstance();
	StagePattern* _stagePattern;

	ResourcePattern* getFullCoinPattern();
	ResourcePattern* getUnlimitedPattern();

	void initEndlessCount();

	Pattern_Data& getPatternData();

	vector<ParallaxLayer>* getParallaxLayerList();
private :
	void setInteractionObject(interactionObject* object, xml_node& nodeItem, GroupPattern* gp, ResourcePattern* rp);
	void parseGroup(xml_node& patternsNode);
	void parseResource(GroupPattern* groupPattern, xml_node& groupPatternsNode);
	void parseInteraction(xml_document& resourceDoc, GroupPattern* groupPattern, ResourcePattern* resourcePattern);

	void parseCoin(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern);
	void parseItem(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern);
	void parseTrap(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern);
	void parseFootbar(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern);
	void parseStarfish(xml_node& coins, GroupPattern* groupPattern, ResourcePattern* resourcePattern);

	void initPatternInfo();

	bool _isFirstResource;

	vector<string> _patternFileList;
	vector<int> _patternInfo;
	int _endlessCount;

	Pattern_Data _patternData;
	vector<ParallaxLayer> _parallaxLayerList;
};
#endif /* defined(__HighHi__XmlLoader__) */
