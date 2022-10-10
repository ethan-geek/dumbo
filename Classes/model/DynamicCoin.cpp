#include "DynamicCoin.h"


DynamicCoin::DynamicCoin(void) : _moveLength(10), _isMove(false)
{
}


DynamicCoin::~DynamicCoin(void)
{
}



void DynamicCoin::processPosition(float frameVelocity, b2Body* body) {

	interactionObject::processPosition(frameVelocity, body);
	
}


void DynamicCoin::processPosition() {

	
	if(_coinType == COIN_TYPE_PATROL) {



		CCPoint vec = ccpAdd(ccp(_body->GetPosition().x, _body->GetPosition().y), ccp(_moveLength/PTM_RATIO , 0));
		_body->SetTransform(b2Vec2(vec.x, vec.y), _body->GetAngle());

		if(_moveLength > 0 && _body->GetPosition().x > _application->_winSize.width / PTM_RATIO) {
			_moveLength = _moveLength*-1;

		}
		else if(_moveLength < 0 && _body->GetPosition().x < 0) {
			_moveLength = _moveLength*-1;

		}
	}
	else if(_coinType == COIN_TYPE_CIRCLE) {

		
		CCPoint vec = ccpAdd(ccp(_body->GetPosition().x, _body->GetPosition().y), ccp(_moveLength/PTM_RATIO , 0));
		_body->SetTransform(b2Vec2(vec.x, vec.y), _body->GetAngle());
		

		if(_body->GetPosition().x > _application->_winSize.width / PTM_RATIO) {
		
			_body->SetTransform(b2Vec2(0, _body->GetPosition().y), _body->GetAngle());
		}
	}
	
}


void DynamicCoin::setCoinType(COIN_TYPE type) {
	_coinType = type;
}

void DynamicCoin::setVelocity(float velocity) {
	_moveLength = velocity;
}

void DynamicCoin::setSprite(CCSprite* sprite) {
	interactionObject::setSprite(sprite);
	
	/*CCAnimation* animation = getAnimation(_imageName);
	CCAnimate* animate = CCAnimate::create(animation);
	CCAction *action = CCRepeatForever::create(animate);
	_sprite->runAction(action);*/

}


