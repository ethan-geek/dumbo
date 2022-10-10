#include "MainPallaxManager.h"


MainPallaxManager::MainPallaxManager(void) : _JewelBackgroundHeight(0)
{
	_pallaxNode = CCParallaxNode::create();

}


MainPallaxManager::~MainPallaxManager(void)
{
}

void MainPallaxManager::init(CCNode* _parent){ 
	_parent->addChild(_pallaxNode);
	_backgroundManager.init(_pallaxNode);
	_backgroundManager.addBackground();
	//background manager 를 추가하자
}

void MainPallaxManager::tick(float dt) {

	CCPoint backgroundScrollVert = ccp(0, -dt * 500);
	_pallaxNode->setPosition(ccpAdd(_pallaxNode->getPosition(), backgroundScrollVert));

	/*addPallax();
	removePallax();*/

	_backgroundManager.removeBackground();
	_backgroundManager.addBackground();
}

void MainPallaxManager::addPallax() {

	_flow.addMainBackground(_pallaxNode);
	//addJewel();

}
void MainPallaxManager::removePallax() {
	_flow.removeBackground(_pallaxNode);
	//removeJewel();
}


void MainPallaxManager::addJewel() {

	if((int)(_JewelBackgroundHeight - CCDirector::sharedDirector()->getWinSize().height) > (-_pallaxNode->getPositionY() * BACKGROUND_SPEED_FLOW)) {
		return;
	}


	const char* jewelName = NULL;
	const char* shinyName = NULL;
	int index;
	int width;
	int height;
	float speed;

	CCSprite* bg = NULL;
	CCSprite* jewel= NULL;
	CCSprite* shiny = NULL;

	CCScaleTo *scaleUp = NULL;
	CCScaleTo *scaleDown = NULL;
	CCSequence *seq = NULL;
	CCRepeatForever *r = NULL;
	int colorIndex = 0;


	for(int indexI = 0 ; indexI < 4; ++indexI) {

		index = rand() % 3 + 1;
		colorIndex = rand() % 2;

		width = rand() % (int)CCDirector::sharedDirector()->getWinSize().width;
		height = rand() % (int)CCDirector::sharedDirector()->getWinSize().height;
		speed = (index + 1) * 0.1;

		switch (index)
		{

		case 1 :
			if(colorIndex == 0) {
				jewelName = "CoinSmall.png";
				shinyName = "CoinSmall_light.png";
			}
			else {
				jewelName = "DynamicCoinSmall.png";
				shinyName = "DynamicCoinSmall_light.png";
			}
			

			
			break;

		case 2 :
			if(colorIndex == 0) {
				jewelName = "CoinNormal.png";
				shinyName = "CoinNormal_light.png";
			}
			else {
				jewelName = "DynamicCoinNormal.png";
				shinyName = "DynamicCoinNormal_light.png";
			}
			
			break;

		case 3 :

			if(colorIndex == 0) {
				jewelName = "CoinBig.png";
				shinyName = "CoinBig_light.png";
			}
			else {
				jewelName = "DynamicCoinBig.png";
				shinyName = "DynamicCoinBig_light.png";
			}
			
			break;
		default:
			break;
		}


		bg = CCSprite::create();
		bg->setTag(4545);

		jewel = CCSprite::createWithSpriteFrameName(jewelName);
		shiny = CCSprite::createWithSpriteFrameName(shinyName);


		bg->addChild(shiny);
		bg->addChild(jewel);

		_pallaxNode->addChild(bg, ZINDEX_FLOW_BACKGROUND+3+index,ccp(0.0, speed),ccp(width,height+ _JewelBackgroundHeight));

		scaleUp = CCScaleTo::create(0.7, 1.10);
		scaleDown = CCScaleTo::create(0.7, 0.8);
		seq = CCSequence::create(scaleUp, scaleDown, NULL);
		r = CCRepeatForever::create(seq);

		shiny->runAction(r);
	}
	_JewelBackgroundHeight += CCDirector::sharedDirector()->getWinSize().height;
}
void MainPallaxManager::removeJewel() {

	CCArray* arr = _pallaxNode->getChildren();

	if (arr == NULL || arr->count() == 0)
	{
		return;
	}
	CCSprite* bgSprite;
	int size = arr->count();
	
	for(int i = 0 ; i < arr->count(); ++i) {
		bgSprite = (CCSprite*)arr->objectAtIndex(i);
		
		if(bgSprite->getTag() != 4545) {
			continue;
		}
		
		
		if(-_pallaxNode->getPositionY() > bgSprite->getPositionY() + CCDirector::sharedDirector()->getWinSize().height) {
			bgSprite->removeAllChildren();
			bgSprite->removeFromParentAndCleanup(true);

		}
	}


}