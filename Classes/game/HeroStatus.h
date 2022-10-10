#if !defined(HH_HEROSTATUS)
#define HH_HEROSTATUS

#include "../common/HiHighCommon.h"
#include "../model/interactionObject.h"
#include "../model/ItemObject.h"
#include "./ItemTimerManager.h"


class HeroStatus
{
public:
	HeroStatus(void);
	~HeroStatus(void);

	bool isStatusRelativeVelocity();
	bool isStatusUNDecreaseRelativeVelocity();

	bool isStatus(HERO_STATUS_TYPE type);
	bool isTilt(HERO_TILT_TYPE type);
	void setStatusType(HERO_STATUS_TYPE status, interactionObject* haveItem);
	void setTiltType(HERO_TILT_TYPE type);
	bool isDefaultHeroStatus(HERO_STATUS_TYPE type);

	bool checkKeepTime(float dt);

	bool checkItemType(HERO_STATUS_TYPE& type);
	bool checkItemRelativeVelocity(HERO_STATUS_TYPE& type);
	bool checkItemUNRelativeVelocity(HERO_STATUS_TYPE& type);
	bool checkItemUNDecreaseRelativeVelocity(HERO_STATUS_TYPE& type);
	
	HEROITEMSTATUS getDefaultStatus();

	HERO_STATUS_TYPE getBeforeStatus();
	HERO_STATUS_TYPE getBeforeStatusItem();

private :
	void testCurrentStatus(HERO_STATUS_TYPE& status);

	vector<HEROITEMSTATUS> _itemStatusList;

	HERO_STATUS_TYPE _beforeStatusArray[2];

	HERO_TILT_TYPE _tileType;

	ItemTimerManager _timerManager;
};

#endif