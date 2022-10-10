///////////////////////////////////////////////////////////
//  Hero.h
//  Implementation of the Class Hero
//  Created on:      19-3-2014 ���� 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_423EAFC5_0E26_4301_A522_EE3AA738B7AD__INCLUDED_)
#define EA_423EAFC5_0E26_4301_A522_EE3AA738B7AD__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../model/interactionObject.h"
#include "../model/UserUpgradeInfo.h"
#include "../model/SuperItemObject.h"
#include "../model/FullCoinItemObject.h"
#include "../model/StartItemObject.h"
#include "./HeroStatus.h"
#include "./HeroAnimation.h"
#include "./HeroPosition.h"


//class b2BodyHero : public b2Body {
//public :
//	virtual void SetTransform(const b2Vec2& position, float32 angle) {
//
//		if(position.y > AGApplication::GetInstance()->_winSize.height * 0.6 / PTM_RATIO) {
//			return;
//		}
//		
//		b2Body::SetTransform(position, angle);
//		
//
//		
//	}
//};

#define MAX_TILT		0.45
#define ALPHA_VALUE 25
#define LIMIT_TILT 0.35
#define LIMIT_TILT_TICK 120

class Hero
{

public:
	Hero();
	virtual ~Hero();

	void contactReAction();
	

	void process(float frameVelocity, float dt);

	
	void setItem(interactionObject* object);
	void useItem();

	void setStatusType(HERO_STATUS_TYPE status);
	void processTilt(CCAcceleration* accelerationValue);
    interactionObject* getFirstItem();
	
	
	void initItemRelation();
	bool checkItemRelation(const INTERACTION_OBJECT_TYPE& type);

	bool isStatus(HERO_STATUS_TYPE type);
	bool isStatusRelativeVelocity();
	bool isStatusUNDecreaseRelativeVelocity();
	bool checkItemType(HERO_STATUS_TYPE& type);
   

	CCSprite* _heroWrapperSprite;
	CCSprite* _heroSprite;
	b2Body* _heroBody;
	
    bool invisible;
    
private:
	void processTransformation();
	void processPosition(float vellocity, float heroVellocity, float dt);
	void processGravity();
	void createRigidBody();

	vector<interactionObject*> _haveItemList;
	float _speed;
	
	
	UserUpgradeInfo* userUpgradeInfo;

	CCSize _winSize;
	
	AGApplication* _application;
	
	HeroStatus* _heroStatus;
	HeroAnimation* _heroAnimation;
	HeroPosition* _heroPosition;
    bool _isFirstTimeGettingItem;
	
	map<INTERACTION_OBJECT_TYPE, vector<HERO_STATUS_TYPE> > _itemRelationMap;
};
#endif // !defined(EA_423EAFC5_0E26_4301_A522_EE3AA738B7AD__INCLUDED_)
