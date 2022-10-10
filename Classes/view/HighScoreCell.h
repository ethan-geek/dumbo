//
//  HighScoreCell.h
//  HiHigh
//
//  Created by insanity on 2014. 5. 14..
//
//

#ifndef __HiHigh__HighScoreCell__
#define __HiHigh__HighScoreCell__

#include "../common/HiHighCommon.h"

class HighScoreCell : public CCTableViewCell
{
    
public:

	HighScoreCell();
	virtual ~HighScoreCell();
    bool init();
    
    CCSprite* _bg;
    CCLabelBMFont * _seqLabel;
    CCSprite * _profileImage;
	CCLabelBMFont * _nameLabelBM;
	CCLabelTTF * _nameLabelTTF;
	CCLabelBMFont * _pointLabel;
    CCSprite* _line;
    
    
    void virtual draw();
    
    void setData(UserInfo *userInfo, int seq, bool isScreenCapture=false);
    void isMyScore(bool isMyScore);
    
	int _seq;
	string _fbId;
	int _maxMeter;
	int _maxCombo;
	string _guestName;
	bool _isScreenCapture;
};



#endif /* defined(__HiHigh__HighScoreCell__) */
