
#ifndef HIHIGH_DYNAMIC_COIN
#define HIHIGH_DYNAMIC_COIN

#include "../common/HiHighCommon.h"
#include "coinobject.h"


class DynamicCoin :	public CoinObject
{
public:
	DynamicCoin(void);
	~DynamicCoin(void);

	virtual void processPosition(float frameVelocity, b2Body* body);
	virtual void processPosition();


	virtual void setSprite(CCSprite* sprite);
	//virtual void processContact();
	void setCoinType(COIN_TYPE type);

	void setVelocity(float velocity);
private :
	float _moveLength;

	bool _isMove;
};



#endif