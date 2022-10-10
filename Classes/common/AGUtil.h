
#if !defined(HH_AGUTIL)
#define HH_AGUTIL

#include "./DefaultHeader.h"
#include "./HHEnum.h"

class AGUtil : public CCObject
{
public :


	static float getSpeed(HERO_STATUS_TYPE type) ;

	static void gamePause() ;

	static void gameResume();
	static void calc3point(string& strInput);

	static void alert(char* contentsString);

	static void getFileList(char* filePath, vector<string>& fileList, char* pattern = "*.*");

	static CCSprite* createSpriteFromUrl(const char* tempImgName, const char* url);
	
	static CCSprite* createSpriteFromUrl(const char* tempImgName, const char* url, bool isScreenCapture);
	
	void onSpriteFromUrlCompleted(CCHttpClient* client, CCHttpResponse* response);

	void onVoidCompleted(CCHttpClient* client, CCHttpResponse* response);

	static string createFBProfileUrl(const char* fbId);

	static bool isKorean(const string& str);
	static bool isEnglish(const string& str);

	static void settingProfileImg(const char* profileFilePath, CCSprite* bgSprite);

	static void replaceStr(string& currentStr, string original, string convert);

	static string reSizeImage(const char* imageName);

    static CCControlButton * createTextWithIconButton(const char * labelString,
                                                      float labelScale,
                                                      const char * buttonString,
                                                      const char * iconString,
                                                      CCObject * obj, SEL_CCControlHandler action, const char* labelFont = TEXT_FONT_NORMAL,
                                                      bool reverse = false) ;
    static CCControlButton * createIconButton(string iconString, CCObject * obj, SEL_CCControlHandler action,float opaque = 0.8);
    
    
    static CCMenuItemLabel * createLabelButton(string text, string font, string iconImage, string backgroundImage , int margin,
                                               CCObject * target = NULL, SEL_MenuHandler handler = NULL,BUTTON_TEXT_ALIGN ali =
                                               BUTTON_TEXT_ALIGN_CENTER);
    static double gaussianRandom(double average, double stdev);

	static AGUtil* create(CCObject* rec, SEL_CallFuncN selector);
	void initWithTarget(CCObject* rec, SEL_CallFuncN selector);
	void fbProfileLoadingComplete(CCNode* obj);

	void Log(const char * pszFormat, ...);

	CCObject* m_target;
	SEL_CallFuncN m_selector;
	bool m_call;
};


#endif
