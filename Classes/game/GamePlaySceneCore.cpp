#include "GamePlaySceneCore.h"
#include "./Hero.h"


GamePlaySceneCore::GamePlaySceneCore(void)
{
	_application = AGApplication::GetInstance();
}


GamePlaySceneCore::~GamePlaySceneCore(void)
{
	delete _hero;
}


bool GamePlaySceneCore::init() {

	if ( !CCLayerColor::initWithColor(ccc4(1,112,180,255)) ) {
		return false;
	}


	_hero = new Hero();
	_application->_hero = _hero;
	this->addChild(_hero->_heroWrapperSprite,ZINDEX_HERO);
	this->addChild(_application->_parallaxNode, ZINDEX_PARALLAX);



	return true;
}