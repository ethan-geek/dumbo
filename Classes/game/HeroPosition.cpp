#include "HeroPosition.h"
#include "./hero.h"

HeroPosition::HeroPosition(void) :  _tiltCount(0), _beforeTilt(0)
{
	_application = AGApplication::GetInstance();
    tickCount = 0;
    opacity = 255;
}

HeroPosition::~HeroPosition(void)
{
}

#define HERO_MAX_HEIGHT		0.45

void HeroPosition::processPosition(float vellocity,float heroVellocity,  b2Body* heroBody, HeroStatus* heroStatus) {

	float heroHeight = heroBody->GetPosition().y;
	
	if(heroHeight > _application->_winSize.height * HERO_MAX_HEIGHT  / PTM_RATIO )
	{
		heroBody->SetTransform(b2Vec2(heroBody->GetPosition().x, _application->_winSize.height * HERO_MAX_HEIGHT  / PTM_RATIO), heroBody->GetAngle());
	}
	else if(heroHeight >= _application->_winSize.height * (HERO_MAX_HEIGHT-0.09)  / PTM_RATIO &&heroHeight <= _application->_winSize.height * HERO_MAX_HEIGHT  / PTM_RATIO) {

	}
	else if( heroHeight > _application->_winSize.height * (HERO_MAX_HEIGHT-0.1)  / PTM_RATIO && 
			(
				heroStatus->isStatusRelativeVelocity() == false || heroStatus->isStatus(HERO_STATUS_TYPE_STARFISH) == false
			)
		) {
		heroBody->SetTransform(b2Vec2(heroBody->GetPosition().x, _application->_winSize.height * (HERO_MAX_HEIGHT-0.1)  / PTM_RATIO), heroBody->GetAngle());
	}


	if(heroBody->GetLinearVelocity().y < 0  && heroBody->GetLinearVelocity().y > -15 ) {
		if(heroStatus->isStatus(HERO_STATUS_TYPE_FALL) == false && heroStatus->isStatus(HERO_STATUS_TYPE_TRAP) == false) {
			_application->_hero->setStatusType(HERO_STATUS_TYPE_FALL);
		}
	}
	else if(heroBody->GetLinearVelocity().y < -15 ) {
		_application->_hero->setStatusType(HERO_STATUS_TYPE_DROP);
	}

	if(heroStatus->isStatus(HERO_STATUS_TYPE_DROP) && heroBody->GetPosition().y < 0 - ((CCSprite*)heroBody->GetUserData())->getContentSize().height/2 /PTM_RATIO ) {
		_application->_hero->setStatusType(HERO_STATUS_TYPE_DIE);
	}


	return;

	/*bool isCheck = false;

	if(heroVellocity > 1000 ) {
		if(heroBody->GetPosition().y <= _application->_winSize.height * 0.6  / PTM_RATIO ) {
			isCheck = true;		
		}
	}

	else if(heroVellocity > 600 ) {

		if(heroBody->GetPosition().y <= _application->_winSize.height / 2 / PTM_RATIO) {
			isCheck = true;		
		}

	}

	else if(heroVellocity > 0 && heroVellocity <= 600 ) {

		if(heroStatus->isStatus(HERO_STATUS_TYPE_JUMP)) {
			if(heroBody->GetPosition().y > (_application->_winSize.height / 3) / PTM_RATIO + 2 ) {
				vellocity *= -0.5;
				_application->setHeroVelocity(_application->getHeroVelocity() - vellocity);
				isCheck = true;
			}
			else {
				isCheck = false;
			}
		}

		if ( heroBody->GetPosition().y <= (_application->_winSize.height/3)  / PTM_RATIO) {
			isCheck = true;
		}


	}*/
	bool isCheck = false;
	if(heroVellocity <= 0  && heroVellocity > -1000) {

		

		if(heroStatus->isStatus(HERO_STATUS_TYPE_FALL) == false) {
			_application->_hero->setStatusType(HERO_STATUS_TYPE_FALL);
		}
		
	}
	else {
		//isCheck = true;
		_application->_hero->setStatusType(HERO_STATUS_TYPE_DROP);
	}

	if(heroStatus->isStatus(HERO_STATUS_TYPE_DROP) && heroBody->GetPosition().y < 0 - ((CCSprite*)heroBody->GetUserData())->getContentSize().height/2 /PTM_RATIO ) {
		_application->_hero->setStatusType(HERO_STATUS_TYPE_DIE);
	}

	if(isCheck) {
		
		
		CCPoint vec = ccpAdd(ccp(heroBody->GetPosition().x, heroBody->GetPosition().y), ccp(0, vellocity/PTM_RATIO));
		heroBody->SetTransform(b2Vec2(vec.x, vec.y),heroBody->GetAngle());
		
		
			
		
		
	}
}



void HeroPosition::changeOpacity(unsigned int opa, CCNode * node) {
    CCArray* arr = node->getChildren();
    
    if (arr == NULL || arr->count() == 0)   return;

    CCSprite * bgSprite = NULL;
    CCSprite * n = NULL;
    
    for(int i = 0 ; i < arr->count(); ++i) {
		n = NULL;
        bgSprite = (CCSprite*)arr->objectAtIndex(i);
        // ?ÑÏù¥???ôÏ†Ñ
        if(bgSprite == NULL || bgSprite->getTag() != SPRITE_TYPE_OBJECT) continue;
        

		// coin child check
        if(bgSprite->getChildren() != NULL && bgSprite->getChildren()->count() != 0) {
            CCArray * arr = bgSprite->getChildren();
            for(int i =0 ; i < arr->count() ; ++i) {
                n = (CCSprite*)arr->objectAtIndex(i);
                n->setOpacity(opa);
            }
        }
		
		if(n == NULL || n->getTag() != 6969) {
			bgSprite->setOpacity(opa);
		}
		
        
    }
}



void HeroPosition::processTilt(CCAcceleration* acceleration, b2Body* heroBody) {

	float currentTilt = 0;
    double curVel = abs(acceleration->x);
 

    
    if(curVel >= LIMIT_TILT) {
        if(tickCount >= LIMIT_TILT_TICK) {
            // alpha--
            // alpha <= 25  alpht = 0  hero contract set
            changeOpacity(opacity--,AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE));
            if(opacity <= 25) {
                // flag change
                AGApplication::GetInstance()->_hero->invisible = true;
            }
        }
        tickCount++;
    } else {
        // alpha++
        // alpha >= 25 hero contract set
        changeOpacity(opacity++,AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE));
        if(opacity >= 25) {
            // flag change
            AGApplication::GetInstance()->_hero->invisible = false;
        }
        tickCount = 0;
    }

    if (opacity >= 255) opacity = 255;
    if (opacity <= 1)   opacity = 1;
    
    if(_tiltCount > 0 ) {

		if(_tiltCount == 10) {
			currentTilt = -acceleration->x;
		}
		else {
			currentTilt = acceleration->x / _tiltCount;
		}
		--_tiltCount;
	}
	else {
		currentTilt = acceleration->x ;
	}

	if(_beforeTilt *  acceleration->x < 0) {
		_tiltCount = 10;

	}

	_beforeTilt = acceleration->x;

	b2Vec2 position = b2Vec2((heroBody->GetPosition().x + currentTilt) ,(heroBody->GetPosition().y) );

	if (position.x < 0  ) {
		position = b2Vec2(_application->_winSize.width / PTM_RATIO, position.y);
	}
	if (position.x > _application->_winSize.width / PTM_RATIO) {
		position = b2Vec2(0, position.y);
	}


	heroBody->SetTransform(position, heroBody->GetAngle());


}
