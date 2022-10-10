
#if !defined(HH_AGAPPLICATION)
#define HH_AGAPPLICATION

#include "./DefaultHeader.h"
#include "./HHEnum.h"
#include "./HiHighGameData.h"


class Hero;
class StagePattern;
class UserInfo;
class HiHighDao;
class InteractionManager;



class AGApplication
{
public:
	AGApplication();
	~AGApplication();
	static AGApplication* g_Application;
	
	static AGApplication* GetInstance();

	b2World* _world;
	CCParallaxNode* _parallaxNode;
	CCSize _winSize;
	Hero* _hero;
	CCNode* _node;

	void setHeroVelocity(float velocity);
	void setGravity(float g);
	void setIsScroll(bool type);
	bool setSpeed(HERO_STATUS_TYPE type);
	void setStagePattern(StagePattern* pattern);
	void setUserInfo(UserInfo* userInfo);

	void setWeightMultiple(float weightMultiple);

	void setObjectMap(string key, CCObject* obj);

	float getHeroVelocity();
	float getGravity();
	float getWeightMultiple();
	CCObject* getObjectMap(string key);
	
	bool getIsScroll();

	bool IsStop();
	void setStop(bool stop);

	
	StagePattern* getStagePattern();
	UserInfo* getUserInfo();
	HiHighDao* getHiHighDao();
	
	void changedFacebookUser();

	void removeBodys(float height = 0);


	void destoryGame();
	void initGame();
	void initData();

	bool checkFacebook();
	void setDt(float dt);
	HiHighGameData* getGameData();

	void setInteractionManager(InteractionManager* mgr);
	InteractionManager* getInteractionManager();

	int getRand();
	void initRand();
private:

	

	StagePattern* _stagePattern;
	UserInfo* _userInfo;
	HiHighDao* _hihighDao;
	
	float _heroVellocity;
	
	float _gravity;
	
	bool _isScroll;
	HiHighGameData _gameData;
	
	vector<int> _randList;
	int _randIndex;

//	float _goldAmount;
//	int _combo;
//	int _maxCombo;
//	int _currentStage;
//	float _gameTime;
	float _weightMultiple;

	float _comboDt;

	bool _isStop;
	InteractionManager* _interactionManager;
	map<string, CCObject*> _objectMap;
    
    
public:
    GameState _currentGameState;
};

#endif
