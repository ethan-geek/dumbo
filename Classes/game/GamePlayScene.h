	///////////////////////////////////////////////////////////
//  GamePlayScene.h
//  Implementation of the Class GamePlayScene
//  Created on:      19-3-2014 ���� 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_F95691C4_399F_4d42_81C0_C31012E59DEA__INCLUDED_)
#define EA_F95691C4_399F_4d42_81C0_C31012E59DEA__INCLUDED_

#include "../common/HiHighCommon.h"
#include "Hero.h"
#include "Background.h"
#include "InteractionManager.h"
#include "../lib/GLES-Render.h"
#include "./ContactListener.h"
#include "../view/PausePopup.h"
#include "./HeroStatus.h"
#include "../common/HiHighConnector.h"
#include "./GamePlaySceneParts.h"
#include "./BackgroundManager.h"
#include "./GamePlaySceneCore.h"
#include "./ChangeColorUtil.h"

#define MAX_FRAME_VALUE 		0.019
#define DEFAULT_FRAME_VALUE		0.017




class GamePlayScene : public cocos2d::CCLayer
{

public:
	GamePlayScene();
	virtual ~GamePlayScene();

	virtual bool init();  
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GamePlayScene);

	void tick(float);
	void draw();

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	void defaultMenuListener(CCObject*);
	

	void pauseMenuListener(CCObject*, CCControlEvent event);
	void resumeMenuListener(CCObject*);

	void removeBodys();

	void saveMeCallbackFunction(int saveMeGold);

	void removeAll();
	void onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) ;
    
	void removeComboText(CCObject* obj);

    
    CCLayerColor * bg;
    
private :
	
	AGApplication* _application;
	/*Hero* _hero;*/

	BackgroundManager _backgroundManager;
	InteractionManager* _iteractionManager;

	//float _heroVellocity;
	float _frameVelocity;
	//float _grabvity;
	CCSize _winSize;

	GLESDebugDraw* _debugDraw;
	ContactListener* _contactLister;

	CCAcceleration* _accelerationValue;
	
	float _heroMoveRatio;
	CCSprite* _processHero;
	bool _isGoal;

	int _saveMeCount;
	bool _isSaveMe;

	void clearGame();
	
	b2Body* _groundBody;

	GamePlaySceneParts* _gamePlayParts;
	GamePlaySceneCore* _gamePlayCore;
    
    
    
    bool isColorChange;
    vector<ccColor3B> changeColors;
    int currentColorCursor;

    int addValue;

public:

    ColorAverage average;
    
    int tickCount;
    int mock;
    int preTickMeter;

    int compareMock;
    bool isMaxValue;

    
    void changeBackgroundColor();
    void changeColor(ccColor3B nextColor);
    void updateColorRGB(ColorVector color,RGB rgb);
    ccColor3B getCurrentColor();
    ccColor3B getNextColorFromCurrentColor();
    ccColor3B setNextColor();
    
};
#endif // !defined(EA_F95691C4_399F_4d42_81C0_C31012E59DEA__INCLUDED_)
