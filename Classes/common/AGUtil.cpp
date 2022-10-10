

#include "./HiHighCommon.h"
#include "./HHAlert.h"
#include "./AGUtil.h"
#include "../network/HHNetwork.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <io.h>
#include  "direct.h"

#define mkdir(n)			mkdir(n)
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "../helper/AndroidHelper.h"
#include <sys/stat.h>
#include <sys/types.h>
#define mkdir(n)			mkdir(n, 0777)
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <sys/types.h>
#include <sys/stat.h>
#define mkdir(n)			mkdir(n, 0777)
#endif

#define FB_PROFILE_IMG_DIC			"/fb_profile/"

#define IMAGE_SMALL					".png"
#define IMAGE_NORMAL				"@2x.png"
#define IMAGE_BIG					"@3x.png"

#define IMAGE_SIZE					IMAGE_SMALL

enum  HERO_SPEED_TYPE {
	COIN_INCREASE_SPEED =				500		/	65,
	COIN_DOUBLE_INCREASE_SPEED =		600		/	65,
	SUPERITEM_INCREASE_SPEED =			1000	/	65,
	FOOTBAR_INCREASE_SPEED =			550		/	65,
	TRAP_DECREASE_SPEED =				-250	/	65,
	ITEM_INCREASE_SPEED =				100		/	65,
	START_INCREASE_SPEED =				1000	/	65,
	STARFISH_INCREASE_SPEED =			1200	/	65
};


struct SPRITE_URL_DATA {
	string imgName;
	CCSprite* sprite;
};


float AGUtil::getSpeed(HERO_STATUS_TYPE type) {
	float speedType = 0;
	switch (type)
	{
	case HERO_STATUS_TYPE_JUMP:
	{
		float currVelocity = AGApplication::GetInstance()->getHeroVelocity();
		if(currVelocity < 0) currVelocity = 0;
		if(currVelocity > COIN_INCREASE_SPEED/2) {
			speedType = COIN_DOUBLE_INCREASE_SPEED;
		}else {
			speedType = COIN_INCREASE_SPEED;
		}


	}


	break;
	case HERO_STATUS_TYPE_SUPERITEM:
		speedType = SUPERITEM_INCREASE_SPEED;
		break;
	case HERO_STATUS_TYPE_STARTJUMP:
		speedType = START_INCREASE_SPEED;
		break;
	case HERO_STATUS_TYPE_TRAP :
		speedType = TRAP_DECREASE_SPEED;
		break;

	case HERO_STATUS_TYPE_FOOTBAR :
		speedType = FOOTBAR_INCREASE_SPEED;
		if(AGApplication::GetInstance()->getHeroVelocity() > -5) {
			speedType += 1;
		}


		break;
	case HERO_STATUS_TYPE_STARFISH :
		speedType = STARFISH_INCREASE_SPEED;
		break;
	default:
		speedType = AGApplication::GetInstance()->getHeroVelocity();
		break;
	}



	return speedType;
}

void AGUtil::gamePause() {
	CCDirector::sharedDirector()->pause();
    if(AGApplication::GetInstance()->_node != NULL) {
        AGApplication::GetInstance()->_node->pauseSchedulerAndActions();
    }
    
}

void AGUtil::gameResume() {
	CCDirector::sharedDirector()->resume();
    if(AGApplication::GetInstance()->_node != NULL) {
        AGApplication::GetInstance()->_node->resumeSchedulerAndActions();
    }
}

void AGUtil::calc3point(string& strInput)
{

	int nLength=strInput.length();
	int j=0;
	for(j=nLength;j>3;j-=3)
		strInput.insert(j-3, ",");
}


CCMenuItemLabel * AGUtil::createLabelButton(string text, string font, string iconImage, string backgroundImage , int margin,
		CCObject * target, SEL_MenuHandler handler,BUTTON_TEXT_ALIGN ali ) {

	CCSprite * s = CCSprite::createWithSpriteFrameName(backgroundImage.c_str());
	s->setAnchorPoint(CCPointZero);

	CCSprite * icon = NULL;
	if(iconImage != "") {
		const char * iconText = iconImage.c_str();
		icon = CCSprite::createWithSpriteFrameName(iconText);
		icon->setPosition(ccp(margin, s->getContentSize().height / 2));

	}

	CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), font.c_str(),s->getContentSize().width / 1.0, kCCTextAlignmentRight);
	label->setZOrder(10);

	if(ali == BUTTON_TEXT_ALIGN_CENTER) {
		if(icon != NULL) {
			label->setPosition(ccp(icon->getContentSize().width / 2 + s->getContentSize().width/2 - label->getContentSize().width / 2,s->getContentSize().height/2 - label->getContentSize().height / 2));
		} else {
			label->setPosition(ccp(s->getContentSize().width/2 - label->getContentSize().width / 2,s->getContentSize().height/2 - label->getContentSize().height / 2));
		}

	} else if (ali == BUTTON_TEXT_ALIGN_RIGHT) {
		label->setPosition(ccp( s->getContentSize().width - margin - label->getContentSize().width ,s->getContentSize().height/2 - label->getContentSize().height / 2));
	}

	CCMenuItemLabel * labelButton = CCMenuItemLabel::create(label, target, handler);
	labelButton->setContentSize(s->getContentSize());
	labelButton->addChild(s);

	if(icon != NULL) {
		labelButton->addChild(icon);
	}

	return labelButton;
}




CCControlButton * AGUtil::createTextWithIconButton(const char * labelString,
		float labelScale,
		const char * buttonString,
		const char * iconString,
		CCObject * obj, SEL_CCControlHandler action, const char* labelFont,
		bool reverse) {

	string backgroundName;
	string highlightName;

	if(reverse) {
		highlightName = string(buttonString) + "_default.png";
		backgroundName = string(buttonString) + "_highlight.png";
	}else {
		backgroundName = string(buttonString) + "_default.png";
		highlightName = string(buttonString) + "_highlight.png";
	}

	string iconName;
	if(iconString != NULL) iconName = string(iconString) + ".png";

	CCScale9Sprite * defaultImage = CCScale9Sprite::create();
	CCSprite * back = CCSprite::createWithSpriteFrameName(backgroundName.c_str());
	back->setAnchorPoint(ccp(0,0));
	defaultImage->addChild(back);
	if(iconString != NULL) {
		CCSprite * icon = CCSprite::createWithSpriteFrameName(iconName.c_str());
		icon->setTag(80);
		defaultImage->addChild(icon);
		icon->setPosition(ccp(20, back->getContentSize().height / 2 - icon->getContentSize().height / 2));
		icon->setAnchorPoint(ccp(0,0));

		CCSprite * xIcon = CCSprite::createWithSpriteFrameName("icon_setting_off.png");
		xIcon->setTag(SETTING_BTN_IGNORE_TAG);
		xIcon->setAnchorPoint(ccp(0,0));
		xIcon->setVisible(false);
		CCPoint pt = icon->getPosition();

		xIcon->setPosition(ccp(pt.x + icon->getContentSize().width - xIcon->getContentSize().width,pt.y));
		defaultImage->addChild(xIcon);
	}




	CCScale9Sprite * highlighted = CCScale9Sprite::create();
	CCSprite * image = CCSprite::createWithSpriteFrameName(highlightName.c_str());
	image->setAnchorPoint(ccp(0,0));
	highlighted->addChild(image);

	if(iconString) {
		CCSprite * icon2 = CCSprite::createWithSpriteFrameName(iconName.c_str());
		icon2->setPosition(ccp(40, back->getContentSize().height/2));
		icon2->setAnchorPoint(ccp(0.5,0.5));
		highlighted->addChild(icon2);
	}


	CCLabelBMFont *label = CCLabelBMFont::create(labelString, labelFont);
	label->setTag(10001);
	label->setScale(labelScale);


	CCControlButton * btn = CCControlButton::create(label, defaultImage);


	btn->setBackgroundSpriteForState(highlighted, CCControlStateHighlighted);
	btn->setPreferredSize(ccp(back->getContentSize().width, back->getContentSize().height));
	btn->addTargetWithActionForControlEvents(obj,action, CCControlEventTouchUpInside);

	return btn;
}
CCControlButton * AGUtil::createIconButton(string iconString, CCObject * obj, SEL_CCControlHandler action,float opaque) {
	string iconName = iconString + ".png";

	CCScale9Sprite * defaultImage = CCScale9Sprite::create();

	CCSprite * icon = CCSprite::createWithSpriteFrameName(iconName.c_str());
	icon->setOpacity(255 * opaque);
	icon->setAnchorPoint(ccp(0,0));

	defaultImage->addChild(icon);


	CCScale9Sprite * highlighted = CCScale9Sprite::create();
	CCSprite * icon2 = CCSprite::createWithSpriteFrameName(iconName.c_str());
	icon2->setAnchorPoint(ccp(0,0));

	highlighted->addChild(icon2);


	CCLabelTTF *label = CCLabelTTF::create("", TEXT_FONT_NORMAL, 32);
	label->setColor(ccWHITE);

	CCControlButton * btn = CCControlButton::create(label, defaultImage);

	btn->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
	btn->setBackgroundSpriteForState(highlighted, CCControlStateHighlighted);
	btn->setPreferredSize(ccp(icon->getContentSize().width, icon->getContentSize().height));
	btn->addTargetWithActionForControlEvents(obj,action, CCControlEventTouchUpInside);

	return btn;
}


void AGUtil::alert(char* contentsString) {

	HHAlert* alert = HHAlert::create(NULL, contentsString, NULL, "OK");
	alert->show();

}

void AGUtil::getFileList(char* filePath, vector<string>& fileList, char* pattern) {

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32

	long h_file;
	char search_Path[100];

	_finddata_t file_search;

	sprintf(search_Path, "%s/%s", filePath, pattern);
	if((h_file = _findfirst(search_Path, &file_search)) == -1L) {


	} else {

		do {

			fileList.push_back(file_search.name);
		} while (_findnext(h_file, &file_search) == 0);

		_findclose(h_file);
	}

#endif





#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

	android_getFileList(filePath, fileList, pattern);

#endif


	CCLog("directory end");
}

CCSprite* AGUtil::createSpriteFromUrl(const char* tempImgName, const char* pUrl) {

	

	return createSpriteFromUrl(tempImgName, pUrl,false);

}

CCSprite* AGUtil::createSpriteFromUrl(const char* tempImgName, const char* pUrl, bool isScreenCapture)
{
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("fb_profile_space.png");
	
	if(HHNetwork::GetInstance()->getNetworkStatus() == false) {
		return sprite;
	}
	
	if (isScreenCapture) {
		string* fbId = new string(tempImgName);
		sprite->setUserData(fbId);
	}else{
		sprite->setUserData(NULL);
	}
	
	string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	if(CCFileUtils::sharedFileUtils()->isFileExist(filePath + FB_PROFILE_IMG_DIC + tempImgName)) {
		
		settingProfileImg((filePath + FB_PROFILE_IMG_DIC + tempImgName).c_str(), sprite);
		
		
		return sprite;
	}
	
	CCHttpRequest* request = new CCHttpRequest();
	
	request->setUrl(pUrl);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(sprite, httpresponse_selector(AGUtil::onSpriteFromUrlCompleted));
	
	request->setTag("POST Request");
	CCHttpClient::getInstance()->setTimeoutForConnect(5);
	CCHttpClient::getInstance()->send(request);
	request->release();
	
	SPRITE_URL_DATA* data = new SPRITE_URL_DATA();
	data->imgName = tempImgName;
	data->sprite = sprite;
	data->sprite->setTag(0);
	
	request->setUserData(data);
	
	return sprite;
}


void AGUtil::onSpriteFromUrlCompleted(CCHttpClient* client, CCHttpResponse* response) {

	if (!response)
	{
		return;
	}

	SPRITE_URL_DATA* data = (SPRITE_URL_DATA*)response->getHttpRequest()->getUserData();

	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	// Check the HTTP Status Code
	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	CCLog("response code: %d", statusCode);

	// A connection failure
	if (!response->isSucceed())
	{
		CCLog("response failed");
		CCLog("error buffer: %s", response->getErrorBuffer());
		delete data;
		return;
	}


	string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();


	if(CCFileUtils::sharedFileUtils()->isFileExist(filePath + FB_PROFILE_IMG_DIC) == false) {
		mkdir((filePath + FB_PROFILE_IMG_DIC).c_str());
	}
	filePath.append(FB_PROFILE_IMG_DIC + data->imgName);
	vector<char> *buffer = response->getResponseData();


	string rest; 
	for (unsigned int i = 0; i < buffer->size(); i++)  
	{  
		rest+=(*buffer)[i];

	}  

	FILE* file = fopen(filePath.c_str(), "wb");



	fwrite(rest.c_str(), rest.size(), 1, file);
	fclose(file);

	settingProfileImg(filePath.c_str(), data->sprite);

	//	pRet->scheduleOnce(schedule_selector(AGUtil::test), 0.5);

	delete data;
}

void AGUtil::settingProfileImg(const char* profileFilePath, CCSprite* bgSprite) {
//	CCSprite* profileRound = CCSprite::createWithSpriteFrameName("profile_bg_108.png");
//	profileRound->setScale(0.9);
//
//	profileRound->setScaleX((bgSprite->getContentSize().width* 0.9)/profileRound->getContentSize().width);
//	profileRound->setScaleY((bgSprite->getContentSize().height * 0.9)/profileRound->getContentSize().height);
//	profileRound->setPosition(ccp(bgSprite->getContentSize().width/2, bgSprite->getContentSize().height/2));
	
	CCSprite* profile = CCSprite::create();
	profile->initWithFile(profileFilePath);
    profile->setPosition(ccp(profile->getContentSize().width/2, profile->getContentSize().height/2));
	bgSprite->addChild(profile);



	if (NULL != bgSprite->getUserData()) {
		AGUtil* pUtil = (AGUtil*)AGApplication::GetInstance()->getObjectMap("AGUTIL_OBJECT");
		
		if (pUtil != NULL) {
				pUtil->fbProfileLoadingComplete(bgSprite);
		}
	}
}
void AGUtil::fbProfileLoadingComplete(CCNode* obj)
{
	if (m_call) {
		if (m_selector != NULL && m_target != NULL) {
			(m_target->*m_selector)(obj);
		}
	}
}


AGUtil* AGUtil::create(cocos2d::CCObject *rec, SEL_CallFuncN selector)
{

	AGUtil* pRet = new AGUtil();

	AGApplication::GetInstance()->setObjectMap("AGUTIL_OBJECT", pRet);
	pRet->retain();
	pRet->initWithTarget(rec, selector);
	pRet->autorelease();
	return pRet;
}

void AGUtil::initWithTarget(cocos2d::CCObject *rec, SEL_CallFuncN selector)
{
	m_selector = selector;
	m_target = rec;
}
string AGUtil::createFBProfileUrl(const char* fbId) {

	string temp = "https://graph.facebook.com/";
	temp += fbId;
	temp += "/picture?type=square";

	return temp;
}

void AGUtil::onVoidCompleted(CCHttpClient* client, CCHttpResponse* response) {
	// ANDROID ....  NULL....
	if(client != NULL) {
		CCSprite* sprite = (CCSprite*)(response->getHttpRequest()->getUserData());
		if(sprite != NULL) {
			sprite->removeFromParentAndCleanup(true);
		}
		
	}

}

bool AGUtil::isKorean(const string& str)
{

	for( int indexI = 0 ; indexI < str.length(); ++indexI) {
		if((str[indexI] & 0x80) == 0x80) {
			return true;
		}

	}
	return false;
}

bool AGUtil::isEnglish(const string& str)
{

	for( int indexI = 0 ; indexI < str.length(); ++indexI) {
		if((0x61 <= str[indexI] && str[indexI] <= 0x7A) || (0x41 <= str[indexI] && str[indexI] <= 0x5A)) {
			return true;
		}

	}
	return false;

}


double AGUtil::gaussianRandom(double average, double stdev) {
	double v1, v2, s, temp;

	do {
		v1 =  2 * ((double) rand() / RAND_MAX) - 1;
		v2 =  2 * ((double) rand() / RAND_MAX) - 1;
		s = v1 * v1 + v2 * v2;
	} while (s >= 1 || s == 0);

	s = sqrt( (-2 * log(s)) / s );

	temp = v1 * s;
	temp = (stdev * temp) + average;

	return temp;
}



void AGUtil::replaceStr(string& currentStr, string original, string convert) {
	int pos = currentStr.find(original);
	int count = (original.size() > convert.size()) ? original.size() : convert.size();
	currentStr = currentStr.replace(pos, count,convert);
}

string AGUtil::reSizeImage(const char* imageName) {

	//add @2x , @3x
	string temp = imageName;
	AGUtil::replaceStr(temp, ".png", IMAGE_SIZE);

	return temp;
}
void AGUtil::Log(const char * pszFormat, ...) {
	CCLog("NO LOG");
}
