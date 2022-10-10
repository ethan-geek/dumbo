#include "SceneManager.h"
#include "../view/MainMenuScene.h"
#include "../view/AbilitiesScene.h"
#include "../view/ClearPopup.h"
#include "../view/LogoScene.h"
#include "../view/GameLoadingScene.h"
#include "../game/GamePlayScene.h"

SceneManager::SceneManager(void)
{
}


SceneManager::~SceneManager(void)
{
}


void SceneManager::replaceScene(const char* sceneName) {

	CCScene* scene = NULL;

	if(strcmp(sceneName, "LogoScene") == 0) {
		scene = LogoScene::scene();
	}
	else if(strcmp(sceneName, "MainMenuScene") == 0) {
		scene = MainMenuScene::scene();
	}
	else if(strcmp(sceneName, "AbilitiesScene") == 0) {
		scene = AbilitiesScene::scene();
	}
	else if(strcmp(sceneName, "GameLoadingScene") == 0) {
		scene = GameLoadingScene::scene();
	}
	
	else if(strcmp(sceneName, "GamePlayScene") == 0) {
		scene = GamePlayScene::scene();
	}
	else if(strcmp(sceneName, "ClearPopup") == 0) {
		scene = ClearPopup::scene();
	}
	else {
		CCLog("%s not found Scene", sceneName);
		return;
	}
		
		
		
    CCTransitionScene* transition = CCTransitionFade::create(0.1f, scene);
    CCDirector::sharedDirector()->replaceScene(transition);

}