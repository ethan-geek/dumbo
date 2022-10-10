#include "BackgroundFull.h"


BackgroundFull::BackgroundFull(void)
{
	/*_images.push_back("background_02_bottom.png");
	_images.push_back("background_02_top.png");*/

	
}


BackgroundFull::~BackgroundFull(void)
{
}



void BackgroundFull::addBackground(CCParallaxNode* node) {

	
	
	CCSprite* pBackground = CCSprite::createWithSpriteFrameName(AGUtil::reSizeImage("background.png").c_str());
	pBackground->setTag(SPRITE_TYPE_FULL_BACKGROUND);
	pBackground->setScaleX(_winSize.width/pBackground->getContentSize().width);
	pBackground->setScaleY(_winSize.height/pBackground->getContentSize().height);
	pBackground->setPosition(ccp(0,0));
	pBackground->setAnchorPoint(ccp(0,0));

	_application->_node->addChild(pBackground, 56);

	//_application->_parallaxNode->addChild(pBackground,ZINDEX_FULL_BACKGROUND, ccp(0.0, BACKGROUND_SPEED_FULL), ccp(0, _backgroundHeight));

}


void BackgroundFull::readyBackgroundIndex() {
	++_backgroundIndex;

	if(_backgroundIndex >= _images.size()) {
		_backgroundIndex = 0;
	}
}
