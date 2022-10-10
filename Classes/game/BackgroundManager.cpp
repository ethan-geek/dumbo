#include "BackgroundManager.h"
#include "../common/XmlLoader.h"
#include "./GamePlayScene.h"

BackgroundManager::BackgroundManager(void)
{

	

	
	farColor = NULL;
	normalColor = NULL;
	nearColor = NULL;
	_parallaxNode= NULL;

	//add object
	// save

}


BackgroundManager::~BackgroundManager(void)
{
}

void BackgroundManager::init(CCParallaxNode* node) {
	_parallaxNode = node;
  //  _flow.initBackgroundObjects(AGApplication::GetInstance()->_parallaxNode);
	if(AGApplication::GetInstance()->_parallaxNode != NULL) {
		_full.addBackground(_parallaxNode);
	}
	vector<ParallaxLayer>* pLayerList = XmlLoader::getInstance()->getParallaxLayerList();
	
	int index = 0;
	for(int indexI = 0 ; indexI < pLayerList->size(); ++indexI) {

		index = 0;
		ParallaxLayer& pLayer = pLayerList->at(indexI);
		
		BackgroundSub sub;
		sub.init(pLayer, _parallaxNode, _parallaxSpriteList);
		_subList.push_back(sub);
	}

	

}



void BackgroundManager::addBackground() {
    //_flow.addGameBackground(AGApplication::GetInstance()->_parallaxNode);
    _flow.addBackgroundParticle(_parallaxNode);
}

void BackgroundManager::removeBackground() {
	_flow.removeGameBackground(_parallaxNode);

	for(int indexI = 0; indexI < _subList.size(); ++indexI) {
		_subList[indexI].removeBackground(_parallaxNode);
	}

}

ccColor3B BackgroundManager::getColorDivide(ccColor3B c, int count) {
    return ccc3(c.r - c.r / 10 * count, c.g -  c.g / 10 * count,  c.b - c.b / 10 * count);
}

void BackgroundManager::setColorAndAverage(ccColor3B currentColor, ccColor3B nextColor) {
    averageNear.setColorAndAverage(getColorDivide(currentColor,4), getColorDivide(nextColor,4));
    averageNormal.setColorAndAverage(getColorDivide(currentColor,2), getColorDivide(nextColor,2));
    averageFar.setColorAndAverage(getColorDivide(currentColor,1), getColorDivide(nextColor,1));
    

	 for(int i  =0 ; i < _parallaxSpriteList.size();++i) {
        if(_parallaxSpriteList[i]->getScale() == FAR) {
            farColor = _parallaxSpriteList[i];
        } else if (_parallaxSpriteList[i]->getScale() == NORMAL) {
            normalColor = _parallaxSpriteList[i];
        } else {
            nearColor = _parallaxSpriteList[i];
        }
    }

   /* for(int i  =0 ; i < _flow.backgoundObjects.size();++i) {
        if(_flow.backgoundObjects[i]->getScale() == FAR) {
            farColor = _flow.backgoundObjects[i];
        } else if (_flow.backgoundObjects[i]->getScale() == NORMAL) {
            normalColor = _flow.backgoundObjects[i];
        } else {
            nearColor = _flow.backgoundObjects[i];
        }
    }*/
}


void BackgroundManager::setBackgroundObjectColor() {

	if(nearColor != NULL) {
		this->updateColor(averageNear, averageNear.r, colorR, nearColor);
		this->updateColor(averageNear, averageNear.g, colorG, nearColor);
		this->updateColor(averageNear, averageNear.b, colorB, nearColor);
	}

	if(normalColor != NULL) {
		this->updateColor(averageNormal, averageNormal.r, colorR, normalColor);
		this->updateColor(averageNormal, averageNormal.g, colorG, normalColor);
		this->updateColor(averageNormal, averageNormal.b, colorB, normalColor);
	}

	if(farColor != NULL) {
		this->updateColor(averageFar, averageFar.r, colorR, farColor);
		this->updateColor(averageFar, averageFar.g, colorG, farColor);
		this->updateColor(averageFar, averageFar.b, colorB, farColor);
	}

	
}


void BackgroundManager::changeColor() {
	if(nearColor != NULL) {
		this->changeColor(nearColor, averageNear.nextColor);
	}
	if(normalColor != NULL) {
		this->changeColor(normalColor, averageNormal.nextColor);
	}
	if(farColor != NULL) {
		this->changeColor(farColor, averageFar.nextColor);
	}

	farColor = NULL;
	normalColor = NULL;
	nearColor = NULL;
}

void BackgroundManager::changeColor(CCSprite * target,ccColor3B color){
    
    float scale = target->getScale();
	for(int  i =0 ; i < _parallaxSpriteList.size() ;++i) {
        if(scale == _parallaxSpriteList[i]->getScale()) {
            _parallaxSpriteList[i]->setColor(color);
        }
    }
}


void BackgroundManager::updateColor(ColorAverage average,ColorVector colorVector,RGB rgb, CCSprite * target) {
    bool isMaxValue = false;
	if(target == NULL) return;
//    int tickMeter = AGApplication::GetInstance()->getGameData()->getMiter();
    int tickMeter = ((GamePlayScene* )AGApplication::GetInstance()->_node)->tickCount;
    if(colorVector.overLimit) {
        if(rgb == colorR)      changeColor(target,ccc3(target->getColor().r + colorVector.getIncreaseValue(), target->getColor().g, target->getColor().b));
        else if(rgb == colorG) changeColor(target,ccc3(target->getColor().r , target->getColor().g + colorVector.getIncreaseValue(), target->getColor().b));
        else                changeColor(target,ccc3(target->getColor().r , target->getColor().g, target->getColor().b + colorVector.getIncreaseValue()));
    }
    
    if(average.checkGreater(rgb, colorVector.velocity, target->getColor())) {
        isMaxValue = true;
        changeColor(target,average.nextColor);
    }
    
    if(isMaxValue == false) {
        if(tickMeter % colorVector.tickOffset == 0) {
            if(rgb == colorR)        changeColor(target,ccc3(target->getColor().r + colorVector.getIncreaseValue(), target->getColor().g, target->getColor().b));
            else if(rgb == colorG)  changeColor(target,ccc3(target->getColor().r , target->getColor().g + colorVector.getIncreaseValue(), target->getColor().b));
            else                    changeColor(target,ccc3(target->getColor().r , target->getColor().g, target->getColor().b + colorVector.getIncreaseValue()));
        }
    }
}