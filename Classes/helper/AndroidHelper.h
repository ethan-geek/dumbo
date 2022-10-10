


#include "../common/HiHighCommon.h"
#include "../model/AGDeviceInfo.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "../platform/android/jni/JniHelper.h"
#endif

USING_NS_CC;

AGDeviceInfo getDeviceInfoAndroid();
void android_viberate(long time);
void android_getFileList(char* filePath, vector<string>& fileList, char* pattern);
void android_showAd(); //
void android_initBanner();
void android_showBanner();
void android_removeBanner();

string android_connectServer(const char* addr , const char* jsonParameter, int timeoutConnection);
