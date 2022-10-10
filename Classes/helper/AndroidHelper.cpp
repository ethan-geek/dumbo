

#include "./AndroidHelper.h"

AGDeviceInfo getDeviceInfoAndroid() {
	AGDeviceInfo f;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
			"net/atgame/dumbo/Dumbo",
			"getDeviceInfo",
			"()[Ljava/lang/String;"))
	{
		// get int array
		jobjectArray arry = (jobjectArray)t.env->CallObjectMethod(t.classID, t.methodID);
		// delete reference


		jstring jstr = (jstring)t.env->GetObjectArrayElement(arry, 0);
		f.deviceType = t.env->GetStringUTFChars(jstr, false);
		/* explicitly releasing to assist garbage collection, though not required */
		t.env->DeleteLocalRef(jstr);

		jstr = (jstring)t.env->GetObjectArrayElement(arry, 1);
		f.version = t.env->GetStringUTFChars(jstr, false);
		/* explicitly releasing to assist garbage collection, though not required */
		t.env->DeleteLocalRef(jstr);

		CCLog("%s = %s", f.deviceType.c_str(), f.version.c_str());

		return f;
	}
#endif

	return f;
}



void android_viberate(long time) {

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
			"net/atgame/dumbo/Dumbo",
			"androidVibrate",
			"(J)V"))
	{
		// get int array
		t.env->CallObjectMethod(t.classID, t.methodID, time);
		// delete reference
	}

#endif

}


void android_getFileList(char* filePath, vector<string>& fileList, char* pattern) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,
				"net/atgame/dumbo/Dumbo",
				"getFileList",
				"(Ljava/lang/String;Ljava/lang/String;)[Ljava/lang/String;"))
		{
			// get int array

			jstring StringArg1 = t.env->NewStringUTF(filePath);
			jstring StringArg2 = t.env->NewStringUTF(pattern);

			jobjectArray arry = (jobjectArray)t.env->CallObjectMethod(t.classID, t.methodID, StringArg1, StringArg2);

			CCLog("1");
			 jsize len = t.env->GetArrayLength(arry);

			 CCLog("len %d", len);

			 CCLog("2");
			   for(int indexI =0; indexI < len; indexI++)
			   {
			      jstring jstr = (jstring)t.env->GetObjectArrayElement(arry, indexI);
			      fileList.push_back(t.env->GetStringUTFChars(jstr, false));
			      /* explicitly releasing to assist garbage collection, though not required */
			      t.env->DeleteLocalRef(jstr);
			   }
			   CCLog("3");

			// delete reference
		}
#endif
}

void android_showAd() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
JniMethodInfo t;
if (JniHelper::getStaticMethodInfo(t, "net/atgame/dumbo/Dumbo", "androidShowAd", "()V"))
{
	// get int array
	t.env->CallObjectMethod(t.classID, t.methodID);
	// delete reference
}
#endif

}

void android_showBanner() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "net/atgame/dumbo/Dumbo", "androidShowBanner", "()V"))
    {
        // get int array
        t.env->CallObjectMethod(t.classID, t.methodID);
        // delete reference
    }
#endif
    
}

void android_removeBanner() {
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t, "net/atgame/dumbo/Dumbo", "androidRemoveBanner", "()V"))
    {
        // get int array
        t.env->CallObjectMethod(t.classID, t.methodID);
        // delete reference
    }
#endif
    
}


string android_connectServer(const char* addr ,const char* jsonParameter,int timeoutConnection) {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,
					"net/atgame/dumbo/Dumbo",
					"callServer",
					"(Ljava/lang/String;Ljava/lang/String;I)Ljava/lang/String;"))
			{


		CCLog("android_connectServer in ");
					jstring StringArg1 = t.env->NewStringUTF(addr);
					jstring StringArg2 = t.env->NewStringUTF(jsonParameter);

					jstring retString = (jstring)t.env->CallObjectMethod(t.classID, t.methodID, StringArg1, StringArg2,timeoutConnection);


					string ret = t.env->GetStringUTFChars(retString, false);



					t.env->DeleteLocalRef(StringArg1);
					t.env->DeleteLocalRef(StringArg2);
					t.env->DeleteLocalRef(retString);

					CCLog("android_connectServer out");
					return ret;
			}

	return "";

#endif

	return "";
}

void android_initBanner() {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	 JniMethodInfo t;
	    if (JniHelper::getStaticMethodInfo(t, "net/atgame/dumbo/Dumbo", "androidInitBanner", "()V"))
	    {
	        // get int array
	        t.env->CallObjectMethod(t.classID, t.methodID);
	        // delete reference
	    }

#endif

}

