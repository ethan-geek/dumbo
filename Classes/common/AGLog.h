//
//  ATLog.h
//  TestCrash
//
//  Created by Jackdaw on 2014. 8. 19..
//
//

#ifndef __TestCrash__ATLog__
#define __TestCrash__ATLog__

#include <iostream>
#include <fstream>
#include "./HiHighCommon.h"

using namespace std;


#define MAKE_LOG_VALUE_STRING string(string(__FILE__) + string("-") +string(__FUNCTION__) + string("-") + string(__DATE__) + string("-")  + string(__TIME__))




class AGLog {
public:

    static void readLog(CCObject* object, SEL_HttpResponse pSelector);
    static void sendLog(string str,CCObject* object, SEL_HttpResponse pSelector);

};

#endif /* defined(__TestCrash__ATLog__) */
