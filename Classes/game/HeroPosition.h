
#if !defined(HH_HERO_POSITION)
#define HH_HERO_POSITION

#include "../common/HiHighCommon.h"
#include "./HeroStatus.h"
#include "./HeroAnimation.h"

class HeroPosition
{
public:
	HeroPosition(void);
	~HeroPosition(void);

	void processPosition(float vellocity,float heroVellocity,  b2Body* heroBody, HeroStatus* heroStatus);

	void processTilt(CCAcceleration* acceleration, b2Body* heroBody);

    void changeOpacity(unsigned int opa, CCNode * node) ;
    
private :
	AGApplication* _application;

    float tickCount;
    unsigned int opacity;
    
	int _tiltCount;
	float _beforeTilt;
};

#endif