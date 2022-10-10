///////////////////////////////////////////////////////////
//  GamePlayScene.cpp
//  Implementation of the Class GamePlayScene
//  Created on:      19-3-2014 ���� 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#include "GamePlayScene.h"
#include "../view/PausePopup.h"
#include "../view/SettingPopup.h"
#include "../dao/HiHighDaoSharedUserDefault.h"
#include "../common/XmlCreator.h"
#include "../view/ClearPopup.h"
#include "../view/GameOverPopup.h"
#include "../network/HHNetwork.h"


GamePlayScene::GamePlayScene() : _accelerationValue(NULL), _isGoal(false), _saveMeCount(0), _isSaveMe(false), _groundBody(NULL)
,isColorChange(false)	{
    changeColors.push_back(ccc3(1,112,180));
    changeColors.push_back(ccc3(31,52,159));
    changeColors.push_back(ccc3(156,45,100));
    changeColors.push_back(ccc3(229,120,40));
    changeColors.push_back(ccc3(234,206,21));
    changeColors.push_back(ccc3(48,133,46));
    currentColorCursor = 0;
    mock = 0;
}



GamePlayScene::~GamePlayScene(){
	removeAll();
}


void GamePlayScene::removeAll() { 
    

	this->unschedule(schedule_selector(GamePlayScene::tick));



	vector<interactionObject*> removeList;

	for(b2Body *b = _application->_world->GetBodyList(); b; b=b->GetNext()) {

		if(b == _application->_hero->_heroBody) {
		}
		else if(b == _groundBody) {

		}
		else {
			removeList.push_back((interactionObject*)b->GetUserData());
		}
	}


	for(int indexI =0 ; indexI < removeList.size(); ++indexI) {
		removeList[indexI]->removeGameObject();
		delete removeList[indexI];
	}


	delete _iteractionManager;
	delete _contactLister;

	_application->destoryGame();
	
    
}



CCScene* GamePlayScene::scene()
{
	CCScene *scene = CCScene::create();
    CCLayerColor* bg = CCLayerColor::create(ccc4(1,112,180,255));

	GamePlayScene *layer = GamePlayScene::create();
    layer->bg = bg;
	scene->addChild(bg);
    bg->addChild(layer);

	return scene;
}


bool GamePlayScene::init()  {
    
	if ( !CCLayer::init() )
	{
		return false;

	}
    
    AGApplication::GetInstance()->_currentGameState = GAMESCENE;

    currentColorCursor = 0;
    mock = 0;
    
    HiHighAudio::sharedAudio()->playMusic("game_bgm");

	setTouchEnabled(true);
	setAccelerometerEnabled(true);
	srand((unsigned int)time(NULL));

	_application = AGApplication::GetInstance();
	_application->initGame();
	_winSize  = CCDirector::sharedDirector()->getWinSize();
	_application->_node = this;


	_gamePlayParts = GamePlaySceneParts::create();
	_gamePlayParts->setTag(LAYER_TYPE_GAMEPLAYSCENE_PARTS);
	this->addChild(_gamePlayParts, ZINDEX_PARTS);


	_gamePlayCore = GamePlaySceneCore::create();
	_gamePlayCore->setTag(LAYER_TYPE_GAMEPLAYSCENE_CORE);
	this->addChild(_gamePlayCore, ZINDEX_HERO);

	/*_hero = new Hero();
	_application->_hero = _hero;
	this->addChild(_hero->_heroWrapperSprite,ZINDEX_HERO);
	this->addChild(_application->_parallaxNode, ZINDEX_PARALLAX);*/
	

	_contactLister = new ContactListener();
	_application->_world->SetContactListener(_contactLister);
	_application->_world->SetContinuousPhysics(true);

	
	_backgroundManager.init(AGApplication::GetInstance()->_parallaxNode);
	_backgroundManager.addBackground();

	_iteractionManager = new InteractionManager();
	_iteractionManager->addInteractionObject();
	_application->setInteractionManager(_iteractionManager);

	// down wall~
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,0);

	_groundBody = _application->_world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

    groundEdge.Set(b2Vec2(0, 185/PTM_RATIO), b2Vec2(_winSize.width/PTM_RATIO, 185/PTM_RATIO));
	_groundBody->CreateFixture(&boxShapeDef);
	
	
	this->schedule(schedule_selector(GamePlayScene::tick));

	if(HH_DEBUG) {
		_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_application->_world->SetDebugDraw(_debugDraw);

		uint32 flags= 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_centerOfMassBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		_debugDraw->SetFlags(flags);
	}
	
	return true;
}

void GamePlayScene::tick(float dt)
{
    
    static bool test = true;
    
	if(_application->IsStop()) {
		return;
	}

    _application->_world->Step(dt, 8, 3);

	if(dt > MAX_FRAME_VALUE) {
		dt = DEFAULT_FRAME_VALUE;
	}
	_frameVelocity = _application->getHeroVelocity() ;
	
	_application->getGameData()->addGameTime(dt);
	_application->getGameData()->setMiter(-_application->_parallaxNode->getPositionY());

	//_application->setSpeed(HERO_STATUS_TYPE_JUMP);
	
	if(_application->getHeroVelocity() != 0 ) {
		_application->_hero->process(_frameVelocity, dt);
	}

	_gamePlayParts->tick(dt);
	
	CCSprite* pSprite;
	for(b2Body *b = _application->_world->GetBodyList(); b; b=b->GetNext()) {

		if(b == _application->_hero->_heroBody) {
			pSprite = (CCSprite*)b->GetUserData();
			_application->_hero->processTilt(_accelerationValue);
		}
		else if (b == _groundBody) {
			continue;
		}
		else {
			pSprite = ((interactionObject*)b->GetUserData())->getSprite();

			if(pSprite->getTag() != TEST_TYPE_TRAP_COIN) {
				_iteractionManager->process(_frameVelocity, b);
			}

		}

		pSprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
		//pSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle())); 
	}
    changeBackgroundColor();

	_iteractionManager->removeInteractionObject();
	_backgroundManager.removeBackground();
	
	if(_application->getIsScroll()) {
		CCPoint backgroundScrollVert = ccp(0, -_frameVelocity);
		_application->_parallaxNode->setPosition(ccpAdd(_application->_parallaxNode->getPosition(), backgroundScrollVert));
		_backgroundManager.addBackground();
        
		_iteractionManager->addInteractionObject();
	}

	if(_application->_hero->isStatus(HERO_STATUS_TYPE_DIE)) {

		if(_isSaveMe == false) {

			//unlimited
            HiHighAudio::sharedAudio()->stopMusic();
             HiHighAudio::sharedAudio()->playEffect("scream");
			_isSaveMe = true;
			clearGame();
		}

	}
 
}





ccColor3B GamePlayScene::getCurrentColor() {
    return changeColors[currentColorCursor];
}
ccColor3B GamePlayScene::getNextColorFromCurrentColor() {
    
    if(currentColorCursor == changeColors.size() - 1) {
        return changeColors[0];
    }
    
    return changeColors[currentColorCursor + 1];
}
ccColor3B GamePlayScene::setNextColor() {

    if(currentColorCursor == changeColors.size() - 1) {
        currentColorCursor = 0;
    } else {
        currentColorCursor++;
    }
    
    return changeColors[currentColorCursor];
}


void GamePlayScene::changeColor(ccColor3B color) {
    bg->setColor(color);
    _gamePlayCore->setColor(color);
}

void GamePlayScene::updateColorRGB(ColorVector colorVector,RGB rgb) {

    isMaxValue = false;
    
    if(colorVector.overLimit) {
        if(rgb == colorR)      changeColor(ccc3(bg->getColor().r + colorVector.getIncreaseValue(), bg->getColor().g, bg->getColor().b));
        else if(rgb == colorG) changeColor(ccc3(bg->getColor().r , bg->getColor().g + colorVector.getIncreaseValue(), bg->getColor().b));
        else                   changeColor(ccc3(bg->getColor().r , bg->getColor().g, bg->getColor().b + colorVector.getIncreaseValue()));
    }
  
    if(average.checkGreater(rgb, colorVector.velocity, bg->getColor())) {
        isMaxValue = true;
        changeColor(average.nextColor);
    }
  
    if(isMaxValue == false) {
        if(tickCount % colorVector.tickOffset == 0) {
            if(rgb == colorR)       changeColor(ccc3(bg->getColor().r + colorVector.getIncreaseValue(), bg->getColor().g, bg->getColor().b));
            else if(rgb == colorG)  changeColor(ccc3(bg->getColor().r , bg->getColor().g + colorVector.getIncreaseValue(), bg->getColor().b));
            else                    changeColor(ccc3(bg->getColor().r , bg->getColor().g, bg->getColor().b + colorVector.getIncreaseValue()));
        }
    }
}


// smooth changeing
//void GamePlayScene::changeBackgroundColor() {
//    
//    
//    int currentMeter = (int)AGApplication::GetInstance()->getGameData()->getMiter();
//    
//    if(currentMeter <= preTickMeter) {
//        return;
//    }
//    
//    if(isColorChange == false) {
//        isColorChange = true;
//        average.setColorAndAverage(getCurrentColor(),getNextColorFromCurrentColor());
//        _backgroundManager.setColorAndAverage(getCurrentColor(), getNextColorFromCurrentColor());
//    }
//    
//    if(isColorChange == true) {
//        
//        updateColorRGB(average.r,colorR);
//        updateColorRGB(average.g,colorG);
//        updateColorRGB(average.b,colorB);
//        _backgroundManager.setBackgroundObjectColor();
//        
//        preTickMeter = currentMeter;
//        
//        if(currentMeter % LIMIT_METER == 0) {
//            isColorChange = false;
//            changeColor(average.nextColor);
//            _backgroundManager.changeColor();
//            setNextColor();
//            preTickMeter = currentMeter;
//            
//            CCLog("change color");
//        }
//    }
//}



// momentarily changeing
void GamePlayScene::changeBackgroundColor() {

    compareMock = (int)AGApplication::GetInstance()->getGameData()->getMiter() / LIMIT_METER;
    
    if(isColorChange == false && compareMock != mock && ((int)AGApplication::GetInstance()->getGameData()->getMiter()) != 0 ) {
        tickCount = 1;
        isColorChange = true;
        average.setColorAndAverage(getCurrentColor(),getNextColorFromCurrentColor());
        _backgroundManager.setColorAndAverage(getCurrentColor(), getNextColorFromCurrentColor());
        mock = compareMock;
    }
    
    if(isColorChange == true) {
        
        updateColorRGB(average.r,colorR);
        updateColorRGB(average.g,colorG);
        updateColorRGB(average.b,colorB);
        
        _backgroundManager.setBackgroundObjectColor();

        tickCount++;

        if(tickCount > TICK_LIMIT_CHANGECOLOR) {
            tickCount = 0;
            isColorChange = false;
            changeColor(average.nextColor);
            _backgroundManager.changeColor();
            setNextColor();
        }
    }
}


void GamePlayScene::didAccelerate(CCAcceleration* pAccelerationValue)
{
	_accelerationValue = pAccelerationValue;
}
void GamePlayScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	_gamePlayParts->closeManual();
	if(_groundBody != NULL) {
		_application->_world->DestroyBody(_groundBody);
		_application->setIsScroll(true);
		_groundBody = NULL;
	}
    if(_application->IsStop()) _gamePlayParts->getChildByTag(1983)->removeFromParentAndCleanup(true);

	_application->setStop(false);
	
	_application->_hero->useItem();
}


void GamePlayScene::defaultMenuListener(CCObject*) {

	_application->setSpeed(HERO_STATUS_TYPE_JUMP);

}



void GamePlayScene::draw() {
	CCLayer::draw();

	if(HH_DEBUG) {
		ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
		kmGLPushMatrix();
		_application->_world->DrawDebugData();
		kmGLPopMatrix();
	}

}


void GamePlayScene::removeBodys() {
    
	for(b2Body *b = _application->_world->GetBodyList(); b; b=b->GetNext()) {

		if(b == _application->_hero->_heroBody) {

		}

		else {
			((interactionObject*)b->GetUserData())->setCheckRemove(true);
		}


	}
    
}


void GamePlayScene::pauseMenuListener(CCObject*, CCControlEvent event) {
	PausePopup *pausePopup = PausePopup::createWithSize(CCSizeMake(_winSize.width, _winSize.height));
	pausePopup->show();
    
}

void GamePlayScene::resumeMenuListener(CCObject*) {
	
	AGUtil::gameResume();
}



void GamePlayScene::clearGame() {
    
    
	UserInfo* info = _application->getUserInfo();

	info->setGold(info->getGold() + _application->getGameData()->getGoldAmount());
	info->setTotalGold(info->getTotalGold() + _application->getGameData()->getGoldAmount());
    
	_application->getGameData()->setDirectMeter(_application->getGameData()->getMiter() + (_application->getGameData()->getMaxCombo()));
	//if(info->getEndlessScoreInfo().getMaxScore() < _application->getGameData()->getGoldAmount() * _application->getGameData()->getMaxCombo()) {
	if(info->getEndlessScoreInfo().getMiter() < _application->getGameData()->getMiter()) {	
		StageScoreInfo scoreInfo;
		scoreInfo.setStage(_application->getGameData()->getCurrentStage());
		scoreInfo.setMaxCombo(_application->getGameData()->getMaxCombo());
		//scoreInfo.setMaxScore(_application->getGameData()->getMaxCombo() * _application->getGameData()->getGoldAmount());
		scoreInfo.setMiter((int)(_application->getGameData()->getMiter()+0.5));
		scoreInfo.setItemCount(_application->getGameData()->getItemCount());

		info->setEndlessScoreInfo(scoreInfo);
		_application->getHiHighDao()->updateScoreInfo(scoreInfo);
	}


	if(HHNetwork::GetInstance()->getNetworkStatus()) {
		if(_application->checkFacebook()) {
			HiHighConnector::sharedConnector()->sendUserInfo(info, this, httpresponse_selector(GamePlayScene::onHttpRequestCompleted));
		}
		else {
			HiHighConnector::sharedConnector()->registGuestScore(&info->getEndlessScoreInfo(), this, httpresponse_selector(GamePlayScene::onHttpRequestCompleted));
		}
	}
	
	AGApplication::GetInstance()->_currentGameState = OTHERSCENE;

	CCScene* clearPopup = ClearPopup::scene();

	CCTransitionScene* transition = CCTransitionFade::create(0.1f, clearPopup);
	CCDirector::sharedDirector()->replaceScene(transition);

    
}


void GamePlayScene::saveMeCallbackFunction(int saveMeGold) {

	_application->getGameData()->decreaseGold(saveMeGold);

	_application->getHiHighDao()->updateGold(_application->getUserInfo()->getGold());


	_application->_hero->setStatusType(HERO_STATUS_TYPE_JUMP);
	_application->setGravity(0);
	_application->setHeroVelocity(0);

	_application->_hero->setItem(new SuperItemObject());
	_application->_hero->useItem();

	_isSaveMe = false;
    
    

}

void GamePlayScene::onHttpRequestCompleted(CCHttpClient* client, CCHttpResponse* response) {
	HiHighConnector* conn = HiHighConnector::sharedConnector();

	if(conn->checkRespose(response) == false) {
		return;
	}

	string resStr;
	conn->convertString(response, resStr);

	if(resStr == "") {
		return;
	}

}

void GamePlayScene::removeComboText(CCObject *obj)
{
	CCSprite* removeObj = (CCSprite*)obj;
	removeObj->removeFromParent();
	removeObj = NULL;
}
