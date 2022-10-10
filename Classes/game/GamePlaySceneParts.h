

#if !defined(HH_GAMEPLAYSCENEPARTS)
#define HH_GAMEPLAYSCENEPARTS

#include "../common/HiHighCommon.h"
#include "../view/PausePopup.h"
#include "../lib/GLES-Render.h"

#define HH_DEBUG		false

class GamePlaySceneParts : public CCLayerColor
{
public:
	GamePlaySceneParts(void);
	~GamePlaySceneParts(void);

	virtual bool init();  
	CREATE_FUNC(GamePlaySceneParts);

	void draw();

	//void init(CCNode* node);
	void tick(float dt);
	void closeManual();


	void pauseMenuListener(CCObject*);
	void readyCallback();
    void showTutorial();
    void showTutorialCallback(CCObject *obj);
    void initFriendsScores();

    void checkFriendRankVisibility();
    void removeFriendRank();

	virtual void keyBackClicked();
private :

	void RenewalRescord();

	CCNode* _parentNode;
	AGApplication* _application;

	CCLabelBMFont* _goldLabel;
	CCLabelBMFont* _meterLabel;
    CCLabelBMFont* _friendMeterLabel;

	CCSprite *_readyText;
	CCSprite *_tiltManual;

	GLESDebugDraw* _debugDraw;
	//CCProgressTimer* _progressTimeBar;

	CCMenuItemLabel* __labelName;
	CCMenuItemLabel* __labelHeight;
	CCMenuItemLabel* __labelCount;
	CCSprite* _friendHeighBG;

    vector<CCSprite *> _friendRankLabels;
    vector<CCSprite *> _removeRankLabels;

};

#endif
