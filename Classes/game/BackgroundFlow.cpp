#include "BackgroundFlow.h"
#include "GamePlayScene.h"



BackgroundFlow::BackgroundFlow(void)
{
	_images.push_back(AGUtil::reSizeImage("parallax_01_white.png"));
	_images.push_back(AGUtil::reSizeImage("parallax_02_white.png"));
	_images.push_back(AGUtil::reSizeImage("parallax_03_white.png"));
	_images.push_back(AGUtil::reSizeImage("parallax_04_white.png"));
	_images.push_back(AGUtil::reSizeImage("parallax_05_white.png"));
    addCount = 0;
    particleBackgroundHeight = 0;
}


BackgroundFlow::~BackgroundFlow(void)
{
   /* for(int i =0 ; i < backgoundObjects.size() ;++i)
        backgoundObjects[i]->release();
    
    backgoundObjects.erase(backgoundObjects.begin(), backgoundObjects.end());*/
}

#define BACKGROUND_PARTICLE 9713

void BackgroundFlow::removeGameBackground(CCParallaxNode* node)
{
    
    CCArray* arr = node->getChildren();
    
    if (arr == NULL || arr->count() == 0) {
        return;
    }
    
    CCSprite* bgSprite;
    
    for(int i = 0 ; i < arr->count(); ++i) {
        bgSprite = (CCSprite*)arr->objectAtIndex(i);
        
        if(bgSprite->getTag() == BACKGROUND_PARTICLE && (-node->getPositionY() > bgSprite->getPositionY() + _application->_winSize.height / 4) ) {
            bgSprite->removeFromParentAndCleanup(true);
            continue;
        }
        
        if(bgSprite->getTag() != SPRITE_TYPE_FLOW_BACKGROUND
           && bgSprite->getTag() != SPRITE_TYPE_SUB_BACKGROUND
           && bgSprite->getTag() != SPRITE_TYPE_FULL_BACKGROUND) {
            continue;
        }
        
        
        
       /* if(-node->getPositionY() > bgSprite->getPositionY() + _application->_winSize.height / 4) {
            
            bgSprite->setVisible(false);
            bgSprite->removeFromParent();
            addCount--;
            CCLog("pa count %d",addCount);
        }*/
    }
}


bool BackgroundFlow::checkOverlapHeight(int height, int width, int index,CCParallaxNode* node) {
    float scale;
   	CCArray* arr = node->getChildren();
    
    switch (index) {
        case 1:
            scale = FAR;
            break;
        case 2:

            scale = NORMAL;
            break;
        case 3:
            scale = NEAR;
            break;
    }
    int y,x,h,w;
    

    if (arr == NULL || arr->count() == 0)  return false;
    CCSprite* bgSprite;
    for(int i = 0 ; i < arr->count(); ++i) {
        
        bgSprite = (CCSprite*)arr->objectAtIndex(i);
        
        if(bgSprite->getTag() != SPRITE_TYPE_FLOW_BACKGROUND)  continue;
       if(bgSprite->getScale() != scale) continue;
        
        y = bgSprite->getPosition().y;
        x = bgSprite->getPosition().x;
        h = (bgSprite->getContentSize().height * bgSprite->getScale());
        w = (bgSprite->getContentSize().width * bgSprite->getScale());
        
        if(height > y - h && y + h < height) return true;
        if(width > x - w && x + w < width) return true;
        
    }
    return false;
}

void BackgroundFlow::addMainBackground(CCParallaxNode* node) {

	if(_application == NULL || node == NULL) {
		return;
	}

	if((int)(_backgroundHeight - _winSize.height) > (-node->getPositionY() * BACKGROUND_SPEED_FLOW)) return;

    int imgIndex = 0;
    int oppaIndex = 0;
    int width = 0 ;
    int height  = 0;
    CCSprite* pBackground = NULL;
    float speed = 0;
    float scale = 1.0;

    for( int indexI = 0 ; indexI < 5 ; ++indexI ) {

        imgIndex = rand() % _images.size();
        oppaIndex = rand() % 3 + 1;
        
        speed = (oppaIndex + 1) * 0.1;

        width = rand() % ((int)CCDirector::sharedDirector()->getWinSize().width - 200) + 200;
        height = rand() % (int)CCDirector::sharedDirector()->getWinSize().height;
        
        if(checkOverlapHeight(height,width,oppaIndex,node)) {
            indexI--;
            continue;
        }
        
        pBackground = CCSprite::createWithSpriteFrameName(_images[imgIndex].c_str());
 
        switch (oppaIndex) {
            case 1:
                pBackground->setColor(ccc3(26, 122, 207));
                scale = FAR;
                break;
            case 2:
                pBackground->setColor(ccc3(22, 101, 171));
                scale = NORMAL;
                break;
            case 3:
                pBackground->setColor(ccc3(18, 73, 120));
                scale = NEAR;
                break;
                
            default:
                break;
        }
        
        pBackground->setTag(SPRITE_TYPE_FLOW_BACKGROUND);
        pBackground->setPosition(CCPointZero);
        pBackground->setScale(scale);
		
        node->addChild(pBackground, ZINDEX_FLOW_BACKGROUND + oppaIndex, ccp(0.0, speed), ccp(width,height+ _backgroundHeight));
		
    }
    _backgroundHeight += (_winSize.height -1);
}




void BackgroundFlow::addBackgroundParticle(CCParallaxNode* node) {
    
    if(_application == NULL || node == NULL) {
        return;
    }
    
    if((int)(particleBackgroundHeight - _winSize.height) > (-node->getPositionY() * 0.5)) return;
    
    int imgIndex = 0;
    int oppaIndex = 0;
    int width = 0 ;
    int height  = 0;
    CCSprite* pBackground = NULL;
    float speed = 0;

    int offsetX = CCDirector::sharedDirector()->getWinSize().width / 2;
    int offsetY = CCDirector::sharedDirector()->getWinSize().height / 3;
    unsigned int alpha;
    
    for( int indexX = 0 ; indexX < 2 ; ++indexX ) {
        for( int indexY = 0 ; indexY < 3; ++indexY ) {
            for(int i = 0 ; i < 3 ; ++i) {

                imgIndex = AGApplication::GetInstance()->getRand() % _images.size();
                oppaIndex = AGApplication::GetInstance()->getRand() % 3 + 1;
                speed = (oppaIndex + 3) * 0.1;
                
                width = (indexX * offsetX) + (AGApplication::GetInstance()->getRand() % offsetX) + 100;
                width = (indexY * offsetY) + (AGApplication::GetInstance()->getRand() % offsetY) + 100;
                
                height = AGApplication::GetInstance()->getRand() % (int)CCDirector::sharedDirector()->getWinSize().height;
                
                pBackground = CCSprite::createWithSpriteFrameName("parallax_06_light.png");
                
                switch (oppaIndex) {
                    case 1:
                        alpha = 255 / 3;
                        break;
                    case 2:
                        alpha = 255 / 2;
                        break;
                    case 3:
                        alpha = 255;
                        break;
                    default:
                        break;
                }
                
                pBackground->setTag(BACKGROUND_PARTICLE);
                pBackground->setPosition(CCPointZero);
                pBackground->setOpacity(alpha);
                
                node->addChild(pBackground, ZINDEX_FLOW_BACKGROUND + oppaIndex, ccp(0.0, speed), ccp(width,height+ particleBackgroundHeight));
            }
        }
    }
    particleBackgroundHeight += (_winSize.height );
    

}




//
//ccColor3B getColorByScale (float scale) {
//
//    ccColor3B cc = ((GamePlayScene*)AGApplication::GetInstance()->_node)->getCurrentColor();
//    ccColor3B ac;
//    ccColor3B rc;
//    
//    ac.r = cc.r / 10;
//    ac.g = cc.g / 10;
//    ac.b = cc.b / 10;
//
//    
//    if(scale == FAR) {
//        rc.r = cc.r - ac.r * 1;
//        rc.g = cc.g - ac.g * 1;
//        rc.b = cc.b - ac.b * 1;
//    } else if (scale == NORMAL) {
//        rc.r = cc.r - ac.r * 2;
//        rc.g = cc.g - ac.g * 2;
//        rc.b = cc.b - ac.b * 2;
//    } else {
//        rc.r = cc.r - ac.r * 4;
//        rc.g = cc.g - ac.g * 4;
//        rc.b = cc.b - ac.b * 4;
//    }
//    return rc;
//}


CCSprite * getSpriteByImageName(const char * imageName, float scale) {
    CCSprite* pBackground = NULL;
    
    pBackground = CCSprite::createWithSpriteFrameName(imageName);

    //pBackground->setColor(getColorByScale(scale));
    
    pBackground->setTag(SPRITE_TYPE_FLOW_BACKGROUND);
    pBackground->setPosition(CCPointZero);
    pBackground->setScale(scale);
    pBackground->setVisible(false);
    
    return pBackground;
}

void BackgroundFlow::initBackgroundObjects(CCParallaxNode* node) {
    
   /* CCSprite * b = NULL;
    
    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),FAR);
        backgoundObjects.push_back(b);
        b->retain();
    }
    
    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),NORMAL);
        backgoundObjects.push_back(b);
        b->retain();
    }
    
    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),NEAR);
        backgoundObjects.push_back(b);
        b->retain();
    }

    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),FAR);
        backgoundObjects.push_back(b);
        b->retain();
    }
    
    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),NORMAL);
        backgoundObjects.push_back(b);
        b->retain();
    }
    
    for (int i =0 ; i < 5; ++i) {
        b = getSpriteByImageName(_images[i].c_str(),NEAR);
        backgoundObjects.push_back(b);
        b->retain();
    }*/
    
    /*CCSprite *ground = CCSprite::createWithSpriteFrameName("parallax_bottom.png");
    ground->setScale(1.2);
    ground->setAnchorPoint(CCPointZero);
    node->addChild(ground, ZINDEX_PATICLE, ccp(0.0, 1), ccp(-30, -30));*/
 
}


void BackgroundFlow::addGameBackground(CCParallaxNode* node) {
    
    if(_application == NULL || node == NULL) return;
//    if (addCount >= backgoundObjects.size() / 2)    return;
    if((int)(_backgroundHeight - _winSize.height) > (-node->getPositionY())) return;

    int imgIndex = 0;
    int oppaIndex = 0;
    int width = 0 ;
    int height  = 0;
    float speed = 0;
    CCSprite* pBackground = NULL;
    
    for( int indexI = 0 ; indexI < 5 ; ++indexI ) {
        
        imgIndex = AGApplication::GetInstance()->getRand() % backgoundObjects.size();
        pBackground = backgoundObjects[imgIndex];
        
        if(pBackground->isVisible() == true) {
            continue;
        }
        
        
        if(pBackground->getScale() == NEAR) {
            oppaIndex = 3;
        } else if(pBackground->getScale() == NORMAL) {
            oppaIndex = 2;
        } else {
            oppaIndex = 1;
        }

        speed = (oppaIndex + 5) * 0.1;
        width = AGApplication::GetInstance()->getRand() % ((int)CCDirector::sharedDirector()->getWinSize().width - 100) + 100;
        

        
        if(_backgroundHeight == 0) {
            height = (AGApplication::GetInstance()->getRand() % ((int)CCDirector::sharedDirector()->getWinSize().height * 2)) +
            -node->getPositionY() + (pBackground->getContentSize().height * pBackground->getScale()) / 2;
        } else {
            height = (AGApplication::GetInstance()->getRand() % ((int)CCDirector::sharedDirector()->getWinSize().height * 2)) +
            -node->getPositionY() + (int)CCDirector::sharedDirector()->getWinSize().height +
            (pBackground->getContentSize().height * pBackground->getScale()) / 2;
        }
        
        if(checkOverlapHeight(height,width,oppaIndex,node)) {
            indexI--;
            continue;
        }
        CCLog("%d, %d", width, height);
        pBackground->setVisible(true);
        node->addChild(pBackground, ZINDEX_FLOW_BACKGROUND + oppaIndex, ccp(0.0, speed), ccp(width,height));
        addCount++;
    }
    
    _backgroundHeight += (_winSize.height);
}

void BackgroundFlow::changeColor(CCSprite * target,ccColor3B color){
    
    /*float scale = target->getScale();
    for(int  i =0 ; i < backgoundObjects.size() ;++i) {
        if(scale == backgoundObjects[i]->getScale()) {
            backgoundObjects[i]->setColor(color);
        }
    }*/
}


void BackgroundFlow::updateColor(ColorAverage average,ColorVector colorVector,RGB rgb, CCSprite * target) {
    bool isMaxValue = false;

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




void BackgroundFlow::readyBackgroundIndex() {
	_backgroundIndex = rand()%_images.size();
}
