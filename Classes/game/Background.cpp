///////////////////////////////////////////////////////////
//  Background.cpp
//  Implementation of the Class Background
//  Created on:      19-3-2014 ø¿¿¸ 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "Background.h"


Background::Background() : _backgroundHeight(0), _backgroundIndex(0){

	_application = AGApplication::GetInstance();
	_winSize = CCDirector::sharedDirector()->getWinSize(); 

}


Background::~Background(){
	
}

void Background::removeBackground(CCParallaxNode* node)
{
	
	CCArray* arr = node->getChildren();

	if (arr == NULL || arr->count() == 0)
	{
		return;
	}
	CCSprite* bgSprite;
	int size = arr->count();
	
	for(int i = 0 ; i < arr->count(); ++i) {
		bgSprite = (CCSprite*)arr->objectAtIndex(i);
		
		if(bgSprite->getTag() != SPRITE_TYPE_FLOW_BACKGROUND 
			&& bgSprite->getTag() != SPRITE_TYPE_SUB_BACKGROUND
			&& bgSprite->getTag() != SPRITE_TYPE_FULL_BACKGROUND) {

			continue;
		}
		
		
		if(-node->getPositionY() > bgSprite->getPositionY() + _application->_winSize.height) {

			bgSprite->removeFromParentAndCleanup(true);

		}
	}

}






