///////////////////////////////////////////////////////////
//  interactionObject.h
//  Implementation of the Class interactionObject
//  Created on:      19-3-2014 ���� 11:55:04
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_1938A200_D02F_4c1c_9378_08F9193DF206__INCLUDED_)
#define EA_1938A200_D02F_4c1c_9378_08F9193DF206__INCLUDED_

#include "../common/HiHighCommon.h"
#define MAGNET_RATIO		4.0

class interactionObject
{

public:
	interactionObject();
	virtual ~interactionObject();

	virtual void initRigid() {};

	void addInteractionObject();
	
	void processAnimation();
	virtual void processContact();
	virtual void processPosition(float frameVelocity, b2Body* body);
	virtual void processPosition();
	void removeGameObject();

	virtual void useItem();

	bool processMagnet();


	void setImageName(string imageName);
	void setObjectType(INTERACTION_OBJECT_TYPE type);
	void setItemHaveType(ITEM_HAVE_TYPE type);
	void setPosition(CCPoint& point);
	void setSpeed(float speed);
	virtual void setSprite(CCSprite* sprite);
	void setCheckContact(bool isContact);
	void setBody(b2Body* body);
	void setCheckHave(bool isHave);
	void setCheckRemove(bool isRemove);
    void useItemEffect();
    void useItemEffectCallback(CCObject* obj);

	string getImageName();
	INTERACTION_OBJECT_TYPE getInteractionObjectType();
	ITEM_HAVE_TYPE getItemHaveType();
	CCPoint getPosition();
	float getSpeed();
	CCSprite* getSprite();
	bool getCheckContact();
	bool getCheckRemove();
	bool getCheckHave();
	
protected:

	bool isAbleMagnet();

	string _imageName;
	INTERACTION_OBJECT_TYPE _objectType;
	ITEM_HAVE_TYPE _itemHaveType;
	CCPoint _position;
	float _speed;
	CCSprite* _sprite;
	bool _checkContact;
	bool _checkRemove;
	bool _checkHave;
	AGApplication* _application;

	b2Body* _body;
};
#endif // !defined(EA_1938A200_D02F_4c1c_9378_08F9193DF206__INCLUDED_)
