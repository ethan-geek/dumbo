///////////////////////////////////////////////////////////
//  GameOverPopup.h
//  Implementation of the Class GameOverPopup
//  Created on:      19-3-2014 ¿ÀÀü 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_BD05CEAE_CDF4_4aba_A812_2F2DA62FB90B__INCLUDED_)
#define EA_BD05CEAE_CDF4_4aba_A812_2F2DA62FB90B__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../common/HHAlert.h"
#include "BasicPopup.h"

#define RESUREECTION_PAY	1000

class GamePlayScene;

class GameOverPopup : public BasicPopup
{

public:
	GameOverPopup();
	virtual ~GameOverPopup();

    static GameOverPopup* create();
    void initGameOverPopup();
	void setCallback(GamePlayScene* obj, void (GamePlayScene::*callBack)(int), int count);
    
    void saveMeBtnListener(CCObject* obj,CCControlEvent event);
    void retryBtnListener(CCObject* obj,CCControlEvent event);
    void backBtnListener(CCObject* obj,CCControlEvent event);
    
    virtual void show();
    void pauseCallback();
    void buySaveMeItem(CCObject* obj,CCControlEvent event);

private :
	void (GamePlayScene::*_callBack)(int);
	int _saveMeCount;
	GamePlayScene* _callObject;
    HHAlert *alert;
};
#endif // !defined(EA_BD05CEAE_CDF4_4aba_A812_2F2DA62FB90B__INCLUDED_)
