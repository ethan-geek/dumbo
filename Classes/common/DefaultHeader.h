



#ifndef HH_DEFAULT_HEADER

#define HH_DEFAULT_HEADER

#include "cocos2d.h"
#include "cocos-ext.h"





#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define NO_IOS
#endif

#ifdef NO_IOS
#include "../external/Box2D/Box2D.h"
#include "../external/Box2D/Collision/Shapes/b2Shape.h"
#else
#include "Box2D.h"
#include <Box2D/Collision/Shapes/b2Shape.h>
#endif



USING_NS_CC;
USING_NS_CC_EXT;


#include "./AGLog.h"
#include "./LogWriterThread.h"



#endif
