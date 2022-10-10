//
//  AGEarthQuakeEffect.cpp
//  HiHigh
//
//  Created by Insanity on 2014. 10. 1..
//
//

#include "AGEarthQuakeEffect.h"


// not really useful, but I like clean default constructors
AGEarthQuakeEffect::AGEarthQuakeEffect() : _strength_x(0), _strength_y(0), _initial_x(0), _initial_y(0)
{
}

AGEarthQuakeEffect* AGEarthQuakeEffect::actionWithDuration( float d, float strength )
{
    // call other construction method with twice the same strength
    return actionWithDuration( d, strength, strength );
}

AGEarthQuakeEffect* AGEarthQuakeEffect::actionWithDuration(float duration, float strength_x, float strength_y)
{
    AGEarthQuakeEffect *p_action = new AGEarthQuakeEffect();
    p_action->initWithDuration(duration, strength_x, strength_y);
    p_action->autorelease();
    
    return p_action;
}

bool AGEarthQuakeEffect::initWithDuration(float duration, float strength_x, float strength_y)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _strength_x = strength_x;
        _strength_y = strength_y;
        return true;
    }
    
    return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand( float min, float max )
{
	float rnd = ((float)AGApplication::GetInstance()->getRand()/(float)RAND_MAX);
    return rnd*(max-min)+min;
}

void AGEarthQuakeEffect::update(float time)
{
    float randx = fgRangeRand( -_strength_x, _strength_x );
    float randy = fgRangeRand( -_strength_y, _strength_y );
    
    // move the target to a shaked position
    m_pTarget->setPosition( ccp( randx, randy) );
}

void AGEarthQuakeEffect::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget( pTarget );
    
    // save the initial position
    _initial_x = pTarget->getPosition().x;
    _initial_y = pTarget->getPosition().y;
}

void AGEarthQuakeEffect::stop(void)
{
    // Action is done, reset clip position
    m_pTarget->setPosition( ccp( _initial_x, _initial_y ) );
    
    CCActionInterval::stop();
}