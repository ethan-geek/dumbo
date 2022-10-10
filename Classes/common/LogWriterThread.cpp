//
//  LogWriterThread.cpp
//  TestCrash
//
//  Created by Jackdaw on 2014. 8. 26..
//
//

#include "LogWriterThread.h"
#include <queue>

bool isRunning;
bool isclean = true;

queue<string> q;
//fstream output;
ofstream output;

pthread_t thread;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  thread_cond  = PTHREAD_COND_INITIALIZER;

void LogWriterThread::init() {
    isRunning = true;
    isclean = true;

    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "/crash.txt";
    
    output.open(path.c_str());

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&thread_cond, NULL);
    pthread_create(&thread, NULL, LogWriterThread::threadFunc,NULL);
    
}

void LogWriterThread::cleanThread() {
    
    if(isclean == false) return;
    
    isclean = false;
    isRunning = false;
    
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&thread_cond);
    pthread_mutex_unlock(&mutex);
    
    int status;
    pthread_join(thread, (void **)&status);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&thread_cond);

    thread = NULL;
    
    output<<"ok"<<endl;
    output.close();
}


void LogWriterThread::addLog(string l) {
    if(!isclean) return;
    pthread_mutex_lock(&mutex);
    q.push(l);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&thread_cond);
}

void* LogWriterThread::threadFunc(void * arg) {

    while(1) {
        
        if(isRunning == false) {
            break;
        }
        
        pthread_mutex_lock(&mutex);
        while (q.empty()) pthread_cond_wait(&thread_cond, &mutex);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        if (output.good()) {
            string s = q.front();
            CCLog("write log %s ,  queue count: %lu", s.c_str(),q.size());
            output.clear();
            output.seekp(ios_base::beg);

            output<<s<<endl<<endl;

            q.pop();
        }
        pthread_mutex_unlock(&mutex);
        
    }
    return NULL;
}
