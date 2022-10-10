//
//  LogWriterThread.h
//  TestCrash
//
//  Created by Jackdaw on 2014. 8. 26..
//
//

#ifndef __TestCrash__LogWriterThread__
#define __TestCrash__LogWriterThread__

#include "cocos2d.h"
USING_NS_CC;

#include <iostream>
#include <fstream>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <pthread.h>
#endif


using namespace std;

#define LOG_START   LogWriterThread::addLog(MAKE_LOG_VALUE_STRING);
#define LOG_END     LogWriterThread::addLog("ok");
#define LOG_CLEAN   LogWriterThread::cleanThread();

class LogWriterThread {
protected:
public:
    static void init() ;
    static void addLog(string l) ;
    static void cleanThread() ;
    static void* threadFunc(void * arg);
};


#endif /* defined(__TestCrash__LogWriterThread__) */
