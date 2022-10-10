
#if !defined(HH_HERO_ANIMATION)
#define HH_HERO_ANIMATION

#include "../common/HiHighCommon.h"
#include "./HeroStatus.h"


class HeroAnimation
{
public:
	HeroAnimation(void);
	~HeroAnimation(void);

	void processAnimation(HERO_STATUS_TYPE beforeStatus,HeroStatus* heroStatus, CCSprite* heroSprite);
    
    void callBackWalkAnimation();
	void callBackStartAnimation();
	void callBackSuperAnimation();

	CCAction* checkMiddleJump(HeroStatus* heroStatus);

	bool checkDuplicateAnimation(const char* before, const char* current, CCSprite* heroSprite);

private :
	void initActionsDefault();
	void initActionsDumbo();
	bool isSkyStatus(HeroStatus* heroStatus);

	string _beforAnimStr;
};

#endif