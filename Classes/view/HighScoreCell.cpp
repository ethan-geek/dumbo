//
//  HighScoreCell.cpp
//  HiHigh
//
//  Created by insanity on 2014. 5. 14..
//
//

#include "HighScoreCell.h"
#include "../model/StageScoreInfo.h"
#include "../model/UserInfo.h"
#include "../common/HiHighConnector.h"


HighScoreCell::HighScoreCell() : _bg(NULL), _seqLabel(NULL), _profileImage(NULL), _nameLabelBM(NULL), _nameLabelTTF(NULL), _pointLabel(NULL),
	_maxMeter(0), _guestName(""), _line(NULL)
{

}


HighScoreCell::~HighScoreCell()
{

}

bool HighScoreCell::init()   {
	
	if ( !CCTableViewCell::init() )
    {
		return false;
	}
    return true;
}

void HighScoreCell::draw()
{
    
    if (_seqLabel == NULL) {
		_seqLabel = CCLabelBMFont::create("1.", TEXT_FONT_NORMAL, 180, kCCTextAlignmentCenter);
        _seqLabel->setPosition(ccp(100, this->getContentSize().height/2));
        this->addChild(_seqLabel);
    }
	ostringstream os;
	os << _seq;
	os << ".";
	_seqLabel->setString(os.str().c_str());
	os.clear();

    if(_profileImage == NULL) {
        
        
        
		if(_fbId.compare("") != 0) {
			if (!_isScreenCapture) {
				_profileImage = AGUtil::createSpriteFromUrl(_fbId.c_str(), AGUtil::createFBProfileUrl(_fbId.c_str()).c_str());
			}else{
				_profileImage = AGUtil::createSpriteFromUrl(_fbId.c_str(), AGUtil::createFBProfileUrl(_fbId.c_str()).c_str(),_isScreenCapture);
			}
			
            _profileImage->setScale(1.2);
            _profileImage->setAnchorPoint(CCPointZero);
            _profileImage->setPosition(ccp(220, 10));
            
            this->addChild(_profileImage);
		}
		else {
			_profileImage = CCSprite::createWithSpriteFrameName("score_thumbnail_default.png");
			_profileImage->setAnchorPoint(CCPointZero);
			_profileImage->setPosition(ccp(220, 10));
			this->addChild(_profileImage);
		}
    }


    if(_nameLabelBM == NULL && _nameLabelTTF == NULL) {
    	HiHighConnector* conn = HiHighConnector::sharedConnector();
        string name = conn->getFBName(_fbId);
        
		if(_fbId.compare("") != 0 && AGUtil::isEnglish(conn->getFBName(_fbId)) == false ) {
            
    		//_nameLabelTTF = CCLabelTTF::create(conn->getFBName(_fbId).c_str(), "Arial", 25);
			if(name.compare("") == 0) name = "facebook user";
            _nameLabelTTF = CCLabelTTF::create(name.c_str(), "Arial", 26);
            _nameLabelTTF->setAnchorPoint(CCPointZero);
            _nameLabelTTF->setHorizontalAlignment(kCCTextAlignmentLeft);
    		_nameLabelTTF->setPosition(ccp(310, 39));
			this->addChild(_nameLabelTTF);
    	}
    	else {
//    		isEnglish
    		if(_fbId.compare("") != 0) {
				if(name.compare("") == 0) name = "facebook user";
    			_nameLabelBM = CCLabelBMFont::create(name.c_str(), TEXT_FONT_SMALL, 230, kCCTextAlignmentLeft);
                _nameLabelBM->setAnchorPoint(CCPointZero);
    		}
    		else {
				string name = "Player";
				if(_guestName.compare("") != 0) name = _guestName;
				_nameLabelBM = CCLabelBMFont::create(name.c_str(), TEXT_FONT_SMALL, 230, kCCTextAlignmentLeft);
                _nameLabelBM->setAnchorPoint(CCPointZero);
    		}
    		_nameLabelBM->setPosition(ccp(310, 37));
            
			this->addChild(_nameLabelBM);
    	}
    }

	if (_pointLabel == NULL) {
		_pointLabel = CCLabelBMFont::create("0", TEXT_FONT_SMALL);
		_pointLabel->setScale(0.8);
		_pointLabel->setColor(ccc3(255, 203, 24));
        _pointLabel->setAnchorPoint(CCPointZero);
		_pointLabel->setPosition(ccp(313, 10));
		this->addChild(_pointLabel);
	}

	char tempPoint[30];
	sprintf(tempPoint, "%d", _maxMeter);
    string commaString = tempPoint;
    AGUtil::calc3point(commaString);
    
    ostringstream oss;
    oss << commaString;
    oss << " m";

	_pointLabel->setString(oss.str().c_str());
    
    if(_line == NULL) {
//        _line = CCSprite::createWithSpriteFrameName("score_line.png");
//        if(_isScreenCapture) {
//            _line->setAnchorPoint(ccp(0.5, 0));
//            _line->setPosition(ccp(572/2 + 10, 0));
//        }else {
//            _line->setAnchorPoint(ccp(0.5, 0));
//            _line->setPosition(ccp(this->getContentSize().width/2, 0));
//        }
//
//        this->addChild(_line);
    }

}

void HighScoreCell::isMyScore(bool isMyScore)
{
    if(isMyScore) {
        CCSprite* myScoreBG = CCSprite::createWithSpriteFrameName("score_bg_myscore.png");
        myScoreBG->setAnchorPoint(ccp(0.5, 0));
        myScoreBG->setPosition(ccp(this->getContentSize().width/2, 0));
        this->addChild(myScoreBG);
    }

}


void HighScoreCell::setData(UserInfo *userInfo, int seq,bool isScreenCapture)
{
	_fbId = (userInfo->getFacebookId().compare("") != 0) ? userInfo->getFacebookId() : "" ;
	_maxMeter = userInfo->getEndlessScoreInfo().getMiter();
	_maxCombo = userInfo->getEndlessScoreInfo().getMaxCombo();
	_seq = userInfo->getEndlessScoreInfo().getRank();
	_isScreenCapture = isScreenCapture;
	
	if(userInfo->getFacebookId().compare("") == 0) {
		char temp[15];
		sprintf(temp, "guest_%.ld", userInfo->getId());
		_guestName = temp;
    }
	
	/*if(userInfo->getId() > 0 ) {
		char temp[15];
		sprintf(temp, "guest_%ld", userInfo->getId());
		_guestName = temp;
	}*/
	
}
