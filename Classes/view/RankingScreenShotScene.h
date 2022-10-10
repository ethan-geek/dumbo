/*
 * RankingScreenShotScene.h
 *
 *  Created on: 2014. 10. 16.
 *      Author: geek
 */

#ifndef RANKINGSCREENSHOTSCENE_H_
#define RANKINGSCREENSHOTSCENE_H_

/* Disabled class
 * Disabled class
 * Disabled class
 * Disabled class
 * Disabled class
 */
#include "../common/HiHighCommon.h"

class RankingView;

class RankingScreenShotScene: public cocos2d::CCLayerColor {
public:
	RankingScreenShotScene();

	virtual ~RankingScreenShotScene();

	virtual bool init();
	static cocos2d::CCScene* scene(vector<UserInfo> scoreDatas, RankingView *ranking);
//	static cocos2d::CCScene* scene();
	CREATE_FUNC(RankingScreenShotScene);

//	void virtual draw();

	void drawRanking();

	CCSize _winSize;

	int _seq;
	string _fbId;
	int _maxPoint;
	int _maxCombo;

private:
	vector<CCSprite *> _profileDatas;
	vector<UserInfo> _scoreDatas;
	RankingView* rankingView;

	void checkProfileLoding();
};

#endif /* RANKINGSCREENSHOTSCENE_H_ */
