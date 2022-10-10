///////////////////////////////////////////////////////////
//  CoinObject.h
//  Implementation of the Class CoinObject
//  Created on:      19-3-2014 ¿ÀÀü 11:55:02
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_3FE51832_889D_454e_A03F_4668B95C3ECA__INCLUDED_)
#define EA_3FE51832_889D_454e_A03F_4668B95C3ECA__INCLUDED_

#include "../common/HiHighCommon.h"
#include "interactionObject.h"
#include "../game/Hero.h"
#include "../common/HiHighAudio.h"

#define SPIN_SPEED_SMALL	0.15	
#define SPIN_SPEED_NORMAL	0.2
#define SPIN_SPEED_BIG		0.25

class CoinObject : public interactionObject
{

public:
	CoinObject();
	virtual ~CoinObject();

	virtual void initRigid();

	void processGold();

	void setCoinSizeType(string coinSizeType);
	COIN_SIZE_TYPE getCoinSizeType();
	int getGoldAmount();

	virtual void setSprite(CCSprite* sprite);
	virtual void processContact();
	virtual void processPosition(float frameVelocity, b2Body* body);
	virtual void processPosition();

	void shinyTick(CCObject* object);

	CCAnimation* getAnimation(const string& imageName);

protected:

	CCAnimation* processSpeed(CCAnimation* animation, const string& imageName);

	int _goldAmount;
	COIN_SIZE_TYPE _sizeType;
	
	COIN_TYPE _coinType;

	CCSprite* _coin;
    void removeDoubleMark(CCObject *obj);
};
#endif // !defined(EA_3FE51832_889D_454e_A03F_4668B95C3ECA__INCLUDED_)
