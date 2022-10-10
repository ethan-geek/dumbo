///////////////////////////////////////////////////////////
//  HeartReqResPopup.h
//  Implementation of the Class HeartReqResPopup
//  Created on:      19-3-2014 ¿ÀÀü 11:55:03
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_61A72ADC_E2CE_48a6_A7C9_7127E3E79ED4__INCLUDED_)
#define EA_61A72ADC_E2CE_48a6_A7C9_7127E3E79ED4__INCLUDED_

#include "../common/HiHighCommon.h"

#include "BasicPopup.h"

class HeartReqResPopup : public BasicPopup
{

public:
	HeartReqResPopup();
	virtual ~HeartReqResPopup();
    static HeartReqResPopup* createWithSize(CCSize size);
    void initHeartPopup();
    void askHeart(CCObject*);
    void sendHeart(CCObject*);

};
#endif // !defined(EA_61A72ADC_E2CE_48a6_A7C9_7127E3E79ED4__INCLUDED_)
