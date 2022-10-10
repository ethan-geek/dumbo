#include "BackgroundSub.h"

#define	PARALLAX_IMAGE_NAME		"parallax_%02d_white.png"
#include "./GamePlayScene.h"

BackgroundSub::BackgroundSub(void) : index(0), _lowIndex(0), _lowHeight(0), _changeHeight(0)
{
	//_images.push_back("episode_image_01.png");

}


BackgroundSub::~BackgroundSub(void)
{
}

ccColor3B getColorByScale (float scale) {

    ccColor3B cc;

	if(AGApplication::GetInstance()->_node == NULL) {
		cc = ccc3(1,112,180);
	}
	else {
		cc = ((GamePlayScene*)AGApplication::GetInstance()->_node)->getCurrentColor();
	}
	//

    ccColor3B ac;
    ccColor3B rc;
    
    ac.r = cc.r / 10;
    ac.g = cc.g / 10;
    ac.b = cc.b / 10;

    
    if(scale == FAR) {
        rc.r = cc.r - ac.r * 1;
        rc.g = cc.g - ac.g * 1;
        rc.b = cc.b - ac.b * 1;
    } else if (scale == NORMAL) {
        rc.r = cc.r - ac.r * 2;
        rc.g = cc.g - ac.g * 2;
        rc.b = cc.b - ac.b * 2;
    } else {
        rc.r = cc.r - ac.r * 4;
        rc.g = cc.g - ac.g * 4;
        rc.b = cc.b - ac.b * 4;
    }
    return rc;
}

void BackgroundSub::init(ParallaxLayer& pLayer, CCParallaxNode* node, vector<CCSprite*>& paraList) {

	_parallaxData = pLayer;

	CCLayer* layer = NULL;
	char parallaxImgName[30];
	CCSprite* parallaxSprite = NULL;

	for(int indexJ = pLayer._objectLayerList.size()-1 ; indexJ >= 0; --indexJ) {

		layer = CCLayer::create();
		layer->setContentSize(CCDirector::sharedDirector()->getWinSize());

		ObjectLayer& oLayer = pLayer._objectLayerList[indexJ];

		for(int indexK = 0; indexK < oLayer._pallaxObjectList.size() ; ++indexK) {
			ParallaxObject& pObject = oLayer._pallaxObjectList[indexK];
			sprintf(parallaxImgName, PARALLAX_IMAGE_NAME, pObject._type);

			parallaxSprite = CCSprite::createWithSpriteFrameName(parallaxImgName);
			CCSize temp = parallaxSprite->getContentSize();
			parallaxSprite->setScale(pLayer._size);
			temp = parallaxSprite->getContentSize();
			parallaxSprite->setPositionX(pObject._x);
			parallaxSprite->setPositionY(pObject._y);
			parallaxSprite->setColor(getColorByScale(pLayer._size));

			layer->addChild(parallaxSprite);
			
			parallaxSprite->setAnchorPoint(CCPointZero);
			parallaxSprite->retain();
			
			paraList.push_back(parallaxSprite);
		}
		layer->setAnchorPoint(CCPointZero);
		layer->retain();
		_layerList.push_back(layer);

		node->addChild(layer, ZINDEX_FLOW_BACKGROUND + pLayer._zIndex, ccp(0.0, oLayer._speed), ccp(0,CCDirector::sharedDirector()->getWinSize().height*index));
		++index;
		
	}

}





void BackgroundSub::addBackground(CCParallaxNode* node) {

	/*if(_application == NULL || node == NULL) {
		return;
	}

	if((int)(_backgroundHeight - _winSize.height) > (-node->getPositionY() * BACKGROUND_SPEED_SUB)) {
		return;
	}

	if(_backgroundHeight > 0 ) {
		return;
	}

	readyBackgroundIndex();

	CCSprite* pBackground = pBackground = CCSprite::createWithSpriteFrameName(_images[_backgroundIndex].c_str());
	pBackground->setTag(SPRITE_TYPE_SUB_BACKGROUND);

	pBackground->setPosition(ccp(0,0));
	pBackground->setAnchorPoint(ccp(0,0));
	node->addChild(pBackground,ZINDEX_SUB_BACKGROUND, ccp(0.0, BACKGROUND_SPEED_SUB), ccp(0, _backgroundHeight));


	_backgroundHeight += (_winSize.height -1);*/
}

void BackgroundSub::removeBackground(CCParallaxNode* node) {

	CCLayer* layer = NULL;
	float lastHeight = 0;
	float speed= _parallaxData._objectLayerList[0]._speed;
	

	for(int indexI = 0; indexI < _layerList.size(); ++indexI) {
		layer = _layerList[indexI];

		if(-node->getPositionY() > layer->getPositionY() + (CCDirector::sharedDirector()->getWinSize().height)) {

			
			for(int indexJ = 0; indexJ < _layerList.size(); ++indexJ) {
				float temp = _layerList[indexJ]->getPositionY();
				if(lastHeight <= _layerList[indexJ]->getPositionY()) {
					lastHeight = _layerList[indexJ]->getPositionY();
				}
			}

			_changeHeight += (_layerList[_lowIndex]->getPositionY() - _lowHeight);
			float currentHeight = (CCDirector::sharedDirector()->getWinSize().height) + lastHeight-_changeHeight;
			
			layer->removeFromParent();
			node->addChild(layer, ZINDEX_FLOW_BACKGROUND + _parallaxData._zIndex, ccp(0.0, speed), ccp(0,currentHeight));
			++index;

			++_lowIndex;
			if(_lowIndex > _layerList.size()-1) _lowIndex = 0;
			_lowHeight = _layerList[_lowIndex]->getPositionY();
		}


	}
	

}

void BackgroundSub::readyBackgroundIndex() {
	_backgroundIndex = 0;
}


