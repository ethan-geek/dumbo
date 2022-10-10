#include "HeroAnimation.h"
#include "Hero.h"

#define COUNT_AIR_IDLE1_DUMBO           11
#define COUNT_AIR_IDLE2_DUMBO           11
#define COUNT_AIR_IDLE3_DUMBO           11
#define COUNT_AIR_LEFTRIGHT_DUMBO		11
#define COUNT_FALL_DUMBO				37
#define COUNT_GAMEOVER_DUMBO			35
#define COUNT_JUMP_DUMBO				10
#define COUNT_STAR_DUMBO				17
#define COUNT_SUPER_LEFTRIGHT_DUMBO		14
#define COUNT_SUPER1_DUMBO				8
#define COUNT_SUPER2_DUMBO				7
#define COUNT_TRAP_DUMBO				15
#define COUNT_WALK1_DUMBO				10
#define COUNT_WALK2_DUMBO				9

#define COUNT_AIR_BLINK_DEFAULT			10
#define COUNT_AIR_IDLE_DEFAULT			13
#define COUNT_AIR_LEFTRIGHT_DEFAULT		10
#define COUNT_FALL_DEFAULT				33
#define COUNT_GAMEOVER_DEFAULT			7
#define COUNT_JEWEL_DEFAULT				10
#define COUNT_JUMP_DEFAULT				10
#define COUNT_STAR_DEFAULT				18
#define COUNT_SUPER_LEFTRIGHT_DEFAULT	10
#define COUNT_SUPER1_DEFAULT			10
#define COUNT_SUPER2_DEFAULT			7
#define COUNT_TRAP_DEFAULT				15
#define COUNT_WALK1_DEFAULT				8
#define COUNT_WALK2_DEFAULT				10


HeroAnimation::HeroAnimation(void)
{
	//initActionsDefault();
	initActionsDumbo();
	_beforAnimStr = "";
}


HeroAnimation::~HeroAnimation(void)
{
}

void HeroAnimation::initActionsDefault() {
    
	CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
	{
		CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_WALK1_DEFAULT + 1; ++indexI ) {
            sprintf(temp, "wait_idle_mask00%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimWalk");
	}
    
    {
        CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_WALK2_DEFAULT + 1; ++indexI ) {
            sprintf(temp, "wait_idle2_mask00%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimWalk2");
    }

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_AIR_LEFTRIGHT_DEFAULT + 1; ++indexI ) {
			sprintf(temp, "air_leftright_mask00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}		


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimSideJump");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_JUMP_DEFAULT + 1; ++indexI ) {
			sprintf(temp, "jump00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}		

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.02);
		animationCache->addAnimation(animation, "AnimJump");
	}


	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_FALL_DEFAULT+1; ++indexI ) {
			sprintf(temp, "fall00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}



		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimFall");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_GAMEOVER_DEFAULT+1; ++indexI ) {
			sprintf(temp, "gameover00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2);
		animationCache->addAnimation(animation, "AnimDrop");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_SUPER_LEFTRIGHT_DEFAULT +1; ++indexI ) {
			sprintf(temp, "super_leftright00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimSuperLeftRight");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_SUPER1_DEFAULT +1; ++indexI ) {
			sprintf(temp, "super100%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.08);
		animationCache->addAnimation(animation, "AnimSuper");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_SUPER2_DEFAULT+1; ++indexI ) {
			sprintf(temp, "super200%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimSuper2");
	}

    {
        CCArray *frames = CCArray::create();

        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_SUPER2_DEFAULT+1; ++indexI ) {
            sprintf(temp, "super_leftright00%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimSideSuperLeftRight");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_TRAP_DEFAULT+1; ++indexI ) {
			sprintf(temp, "trap00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimTrap");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_STAR_DEFAULT+1; ++indexI ) {
			sprintf(temp, "star00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimStar");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_AIR_BLINK_DEFAULT+1; ++indexI ) {
			sprintf(temp, "blink00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimBlink");
	}

	{
		CCArray *frames = CCArray::create();
		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_AIR_IDLE_DEFAULT+1; ++indexI ) {
			sprintf(temp, "air_idle00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimIdle1");
	}


}

void HeroAnimation::initActionsDumbo() {
    
	CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
	{
		CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_WALK1_DUMBO + 1; ++indexI ) {
            sprintf(temp, "walk_step100%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimWalk");
	}
    
    {
        CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_WALK2_DUMBO + 1; ++indexI ) {
            sprintf(temp, "walk_step200%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimWalk2");
    }

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_AIR_LEFTRIGHT_DUMBO + 1; ++indexI ) {
			sprintf(temp, "air_leftright00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}		


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimSideJump");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_JUMP_DUMBO + 1; ++indexI ) {
			sprintf(temp, "jump00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}		

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.02);
		animationCache->addAnimation(animation, "AnimJump");
	}


	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_FALL_DUMBO+1; ++indexI ) {
			sprintf(temp, "fall00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}



		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimFall");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_GAMEOVER_DUMBO+1; ++indexI ) {
			sprintf(temp, "gameover00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2);
		animationCache->addAnimation(animation, "AnimDrop");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_SUPER1_DUMBO +1; ++indexI ) {
			sprintf(temp, "super_step100%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.08);
		animationCache->addAnimation(animation, "AnimSuper");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_SUPER2_DUMBO+1; ++indexI ) {
			sprintf(temp, "super_step200%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimSuper2");
	}

    {
        CCArray *frames = CCArray::create();

        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_SUPER2_DUMBO+1; ++indexI ) {
            sprintf(temp, "super_leftright00%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimSuperLeftRight");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_TRAP_DUMBO+1; ++indexI ) {
			sprintf(temp, "trap00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimTrap");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_STAR_DUMBO+1; ++indexI ) {
			sprintf(temp, "star00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}


		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimStar");
	}

	{
		CCArray *frames = CCArray::create();

		char temp[30];
		for(int indexI = 1 ; indexI < COUNT_AIR_IDLE1_DUMBO+1; ++indexI ) {
			sprintf(temp, "air_idle00%02d.png", indexI);
			frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
		}

		CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
		animationCache->addAnimation(animation, "AnimIdle1");
	}

    {
        CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_AIR_IDLE2_DUMBO+1; ++indexI ) {
            sprintf(temp, "air_idle200%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimIdle2");
    }

    {
        CCArray *frames = CCArray::create();
        
        char temp[30];
        for(int indexI = 1 ; indexI < COUNT_AIR_IDLE3_DUMBO+1; ++indexI ) {
            sprintf(temp, "air_idle300%02d.png", indexI);
            frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
        }
        
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.05);
        animationCache->addAnimation(animation, "AnimIdle3");
    }
}

void HeroAnimation::processAnimation(HERO_STATUS_TYPE beforeStatus, HeroStatus* heroStatus, CCSprite* heroSprite) {

    heroSprite->setFlipX(false);
    
    CCAction* action = NULL;
	char* currentAnim = NULL;
    
    CCAnimationCache *animationCache = CCAnimationCache::sharedAnimationCache();
    
    
	if(AGApplication::GetInstance()->getIsScroll() == false) {
        
        //CENTER walk
        if(heroStatus->isTilt(HERO_TILT_TYPE_CENTER)) {

			currentAnim = "AnimIdle1";
            CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
            action = CCRepeatForever::create(animate);

        }
        
        //left walk
        else if(heroStatus->isTilt(HERO_TILT_TYPE_LEFT)) {
            
			currentAnim = "AnimWalk";
			CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
            CCCallFunc * func = CCCallFunc::create(heroSprite, callfunc_selector(HeroAnimation::callBackWalkAnimation));
            action = CCSequence::create(animate, func, NULL);
            heroSprite->setFlipX(true);

        }
        
        //right walk
        else if(heroStatus->isTilt(HERO_TILT_TYPE_RIGHT)) {
            
			currentAnim = "AnimWalk";
			CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
            CCCallFunc * func = CCCallFunc::create(heroSprite, callfunc_selector(HeroAnimation::callBackWalkAnimation));
            action = CCSequence::create(animate, func, NULL);
            
        }

		if(checkDuplicateAnimation(_beforAnimStr.c_str(), currentAnim, heroSprite)) {
			return;
		}

        heroSprite->stopAllActions();
        if(action != NULL) {
			if(strcmp(currentAnim, "AnimWalk") == 0 && heroStatus->getBeforeStatus() == heroStatus->getDefaultStatus()._statusType
				&& heroSprite->numberOfRunningActions() >0){
					return;
			}

			_beforAnimStr = currentAnim;

            heroSprite->runAction(action);
        }
        
        
        
		return;
	}


	// start item
	if(heroStatus->isStatus(HERO_STATUS_TYPE_STARTJUMP)) {
		currentAnim = "AnimJump";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));

		CCCallFunc * func = CCCallFunc::create(heroSprite, callfunc_selector(HeroAnimation::callBackStartAnimation));
		action = CCSequence::create(animate,CCDelayTime::create(0.5f), func, NULL);
	}

	


	// super item left
	//else if(heroStatus->isStatus(HERO_STATUS_TYPE_SUPERITEM)  && heroStatus->isTilt(HERO_TILT_TYPE_LEFT)) {
	//	  currentAnim = "AnimSuper2";

	//	CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
	//	action = CCRepeat::create(animate, 1);
 //       heroSprite->setFlipX(true);
	//}

	//// super item right
	//else if(heroStatus->isStatus(HERO_STATUS_TYPE_SUPERITEM) && heroStatus->isTilt(HERO_TILT_TYPE_RIGHT)) {
	//	  currentAnim = "AnimSuper2";
	//	
	//	CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
	//	action = CCRepeat::create(animate, 1);
	//	
	//}

	// super item
	else if(heroStatus->isStatus(HERO_STATUS_TYPE_SUPERITEM) ) {
        CCLog("HERO_STATUS_TYPE_SUPERITEM");
        currentAnim = "AnimSuper";
        
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));

		CCCallFunc * func = CCCallFunc::create(heroSprite, callfunc_selector(HeroAnimation::callBackSuperAnimation));
		action = CCSequence::create(animate,CCDelayTime::create(0.5f), func, NULL);
//heroSprite->numberOfRunningActions()
	}

	else if(heroStatus->isStatus(HERO_STATUS_TYPE_STARFISH)) {
        CCLog("HERO_STATUS_TYPE_STARFISH");
       currentAnim = "AnimStar";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeatForever::create(animate);
	}

	// contact
	else if(heroStatus->isStatus(HERO_STATUS_TYPE_TRAP)) {

		  currentAnim = "AnimTrap";
		

		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeat::create(animate, 1);
	}

	// fall
	else if(heroStatus->isStatus(HERO_STATUS_TYPE_FALL)) {
		  currentAnim = "AnimFall";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeat::create(animate, 1);
	}

	// drop
	else if(heroStatus->isStatus(HERO_STATUS_TYPE_DROP)) {
		currentAnim = "AnimDrop";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeat::create(animate, 1);
	}


	// center sky
	else if(isSkyStatus(heroStatus) && heroStatus->isTilt(HERO_TILT_TYPE_CENTER)) {
		action = checkMiddleJump(heroStatus);
		if(action == NULL) {
			currentAnim = "AnimJump";
		
			CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
			action = CCRepeat::create(animate, 1);
		}
		else {
			currentAnim = "AnimIdle1";
		}

	}


	//left sky
	else if(isSkyStatus(heroStatus) && heroStatus->isTilt(HERO_TILT_TYPE_LEFT)) {
		currentAnim = "AnimSideJump";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeat::create(animate, 1);
		
		heroSprite->setFlipX(true);
	}

	//right sky
	else if(isSkyStatus(heroStatus) && heroStatus->isTilt(HERO_TILT_TYPE_RIGHT)) {
		currentAnim = "AnimSideJump";
		
		CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
		action = CCRepeat::create(animate, 1);
	}

	// test center sky
	else if(isSkyStatus(heroStatus) ) {
		action = checkMiddleJump(heroStatus);
		if(action == NULL) {
			currentAnim = "AnimJump";
		
			CCAnimate* animate = CCAnimate::create(animationCache->animationByName(currentAnim));
			action = CCRepeat::create(animate, 1);
            

		}

	}
    
    CCLayer* coreLayer = (CCLayerColor*)AGApplication::GetInstance()->_node->getChildByTag(LAYER_TYPE_GAMEPLAYSCENE_CORE);
    CCScaleTo *scale = NULL;
    if(heroStatus->isStatus(HERO_STATUS_TYPE_FALL)) {
        scale = CCScaleTo::create(0.6, 1.1);
    }else {
        scale = CCScaleTo::create(0.6, 1.0);
    }
    coreLayer->runAction(scale);
    
    if(checkDuplicateAnimation(_beforAnimStr.c_str(), currentAnim, heroSprite)) {
        return;
    }

	if(action != NULL) {
		heroSprite->stopAllActions();
		_beforAnimStr = currentAnim;
		heroSprite->runAction(action);
	}
	
}


bool HeroAnimation::isSkyStatus(HeroStatus* heroStatus) { 

	if(heroStatus->isStatus(HERO_STATUS_TYPE_JUMP)
		|| heroStatus->isStatus(HERO_STATUS_TYPE_SHIELD)
		|| heroStatus->isStatus(HERO_STATUS_TYPE_STARFISH)
		|| heroStatus->isStatus(HERO_STATUS_TYPE_WEIGHT)) {
			return true;
	}

	return false;
}


void HeroAnimation::callBackWalkAnimation() {
	
    CCAction *action = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("AnimWalk2")));
    AGApplication::GetInstance()->_hero->_heroSprite->runAction(action);
    
}

void HeroAnimation::callBackStartAnimation() {
	CCAction *action = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("AnimStar")));
	AGApplication::GetInstance()->_hero->_heroSprite->runAction(action);

}

void HeroAnimation::callBackSuperAnimation() {
	CCAction *action = CCRepeatForever::create(CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName("AnimSuper2")));
	AGApplication::GetInstance()->_hero->_heroSprite->runAction(action);
}

CCAction* HeroAnimation::checkMiddleJump(HeroStatus* heroStatus) {
	if(heroStatus->isStatus(heroStatus->getBeforeStatus()) || heroStatus->getBeforeStatusItem() == HERO_STATUS_TYPE_STARTJUMP) {

		//_beforAnimStr = "AnimIdleBlink";
		
		int randIndex = AGApplication::GetInstance()->getRand() % 7;
		char* temp;
        if(randIndex == 0) {
            temp = "AnimIdle2";
        }else if(randIndex == 1) {
            temp = "AnimIdle3";
        }else {
            temp = "AnimIdle1";
        }

		CCAnimate* animate = CCAnimate::create(CCAnimationCache::sharedAnimationCache()->animationByName(temp));
		return CCRepeat::create(animate, 1);

	}

	return NULL;
}


bool HeroAnimation::checkDuplicateAnimation(const char* before, const char* current, CCSprite* heroSprite) {
	if(current == NULL) return true;

	if(strcmp(before, current) == 0) {
		if(heroSprite->numberOfRunningActions() > 0 ) {
			return true;
		}
	}


	return false;
}