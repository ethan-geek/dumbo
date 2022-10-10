///////////////////////////////////////////////////////////
//  StageScoreInfo.h
//  Implementation of the Class StageScoreInfo
//  Created on:      19-3-2014 ¿ÀÀü 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_8F1E397B_F17C_4127_9ACA_05ECBAB454B3__INCLUDED_)
#define EA_8F1E397B_F17C_4127_9ACA_05ECBAB454B3__INCLUDED_

#include "../common/HiHighCommon.h"

class StageScoreInfo
{

public:
	StageScoreInfo();
	virtual ~StageScoreInfo();

	void setStage(int stage);
	void setMaxCombo(int maxCombo);
	void setMaxScore(int maxScore);
	void setMiter(float miter);
	void setItemCount(int itemCount);
	void setRank(long rank);
	
	int getStage();
	int getMaxCombo();
	int getMaxScore();
	float getMiter();
	int getItemCount();
	long getRank();
private:
	int _stage;
	int _maxCombo;
	int _maxScore;


	float _miter;
	int _useItemCount;
	long _rank;
};
#endif // !defined(EA_8F1E397B_F17C_4127_9ACA_05ECBAB454B3__INCLUDED_)
