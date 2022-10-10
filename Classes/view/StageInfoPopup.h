///////////////////////////////////////////////////////////
//  StageInfoPopup.h
//  Implementation of the Class StageInfoPopup
//  Created on:      19-3-2014 ¿ÀÀü 11:55:06
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_C39D424A_477C_45f0_81CA_6213C15A75DD__INCLUDED_)
#define EA_C39D424A_477C_45f0_81CA_6213C15A75DD__INCLUDED_


#include "../common/HiHighCommon.h"
#include "BasicPopup.h"


typedef struct _ScoreData
{
	string name;
    int point;
    int maxCombo;
	
}ScoreData;

class StageInfoPopup : public BasicPopup, public CCTableViewDataSource, public CCTableViewDelegate
{

public:
	StageInfoPopup();
	virtual ~StageInfoPopup();
    static StageInfoPopup* create();
    void initStageInfoPopup();
    void initData();
    
    //datasource method
	void scrollViewDidScroll(CCScrollView* view);
    void scrollViewDidZoom(CCScrollView* view);
	
	CCSize cellSizeForTable(CCTableView *table);
    
	CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    
    unsigned int numberOfCellsInTableView(CCTableView *table);

	void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    
    void play(CCObject* obj);
    virtual void show();
    
    CCLayer *topLayer;
    CCLayer *bottomLayer;
    CCSize _winSize;
    
private:
	vector<ScoreData> _scoreDatas;
    
};
#endif // !defined(EA_C39D424A_477C_45f0_81CA_6213C15A75DD__INCLUDED_)
