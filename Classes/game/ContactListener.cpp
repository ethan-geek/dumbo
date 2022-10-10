#include "ContactListener.h"


ContactListener::ContactListener(void)
{
	_application = AGApplication::GetInstance();
}


ContactListener::~ContactListener(void)
{
}


void ContactListener::BeginContact(b2Contact* contact)
{
	
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();

	if(fixtureB->GetType() == b2Shape::e_edge || fixtureA->GetType() == b2Shape::e_edge)  {
		return;
	}

    if(AGApplication::GetInstance()->_hero->invisible) {
        return;
    }
    

	b2Body *bodyA = fixtureA->GetBody();
	b2Body *bodyB = fixtureB->GetBody();

	b2Body* hero;
	b2Body* object;

	

	if(bodyA == _application->_hero->_heroBody) {
		hero = bodyA;
		object = bodyB;
	}
	else {
		hero = bodyB;
		object = bodyA;
	}

	interactionObject* interactObject = (interactionObject*)object->GetUserData();

	if((interactObject->getInteractionObjectType() == INTERACTION_OBJECT_TYPE_FOOTBAR 
		|| interactObject->getInteractionObjectType() == INTERACTION_OBJECT_TYPE_FAKE_FOOTBAR)
		&& AGApplication::GetInstance()->getHeroVelocity() > 0 ) {
		interactObject->setCheckContact(false);
	}
	else if(interactObject->getSprite()->isVisible()) {
		interactObject->setCheckContact(true);
	}

	
	

}
void ContactListener::EndContact(b2Contact* contact)
{
	
}
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	
}
void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	
}
