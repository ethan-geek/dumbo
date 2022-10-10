#include "AppDelegate.h"
#include "./common/HiHighCommon.h"
#include "./common/HiHighAudio.h"
#include "./common/HeartChecker.h"
#include "./common/XmlCreator.h"
#include "./common/HiHighJsonConvecter.h"
#include "./game/GamePlayScene.h"


USING_NS_CC;
void AppDelegate::eraseLog() {
	//LOG_END
}
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	delete AGApplication::GetInstance();
	delete HiHighAudio::sharedAudio();
	delete HeartChecker::sharedHeartChecker();
	delete XmlCreator::getInstance();
	delete HiHighJsonConvecter::sharedJsonConverter();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    
 
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionExactFit);
#else
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 1136, kResolutionShowAll);
#endif

	

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = GamePlayScene::scene();
    CCScene *pScene = LogoScene::scene();
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    if( AGApplication::GetInstance()->_currentGameState == GAMESCENE ) {
        CCArray* layers = CCDirector::sharedDirector()->getRunningScene()->getChildren();
        CCLayer* layer = (CCLayer*)layers->objectAtIndex(0);
        
        CCNode* node = layer->getChildByTag(BASICPOPUP);
        if(node != NULL) {
            
            ((PausePopup*)node)->menuCloseCallback(NULL);
            AGUtil::gameResume();
            return;
        }
        
        PausePopup* pausePopup = PausePopup::createWithSize(CCSizeMake(500, 600));
        pausePopup->show();
    }

    CCDirector::sharedDirector()->stopAnimation();
	HiHighAudio::sharedAudio()->pauseMusic();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
   

}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	HiHighAudio::sharedAudio()->resumeMusic();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

}
