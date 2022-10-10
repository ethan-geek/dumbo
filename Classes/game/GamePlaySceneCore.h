
#if !defined(HH_GAMEPLAYSCENE_CORE)
#define HH_GAMEPLAYSCENE_CORE

#include "../common/HiHighCommon.h"


class GamePlaySceneCore : public CCLayerColor
{
public:
	GamePlaySceneCore(void);
	~GamePlaySceneCore(void);

	virtual bool init();

	CREATE_FUNC(GamePlaySceneCore)

private :
	Hero* _hero;
	AGApplication* _application;
};


#endif
