

#ifndef HH_SCENE_MANAGER
#define HH_SCENE_MANAGER

#include "../common/HiHighCommon.h"

class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	static void replaceScene(const char* sceneName);
};

#endif	