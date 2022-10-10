

#if !defined(HH_ITEM_TIMER_MANAGER)
#define HH_ITEM_TIMER_MANAGER

#include "./ItemTimer.h"

#define PROGRASSBAR_ARRAY_SIZE		10

struct HEROITEMSTATUS {
	HEROITEMSTATUS() : _statusKeepTime(0), _saveDt(0) {

	}

	HERO_STATUS_TYPE _statusType;
	float _statusKeepTime;
	float _saveDt;
	string _imageName;
};

class ItemTimerManager
{
public:
	ItemTimerManager(void);
	~ItemTimerManager(void);

	void useItem(HEROITEMSTATUS& status);

	void flowTime(HERO_STATUS_TYPE& type, float flowTime);

	void removeItem(HERO_STATUS_TYPE& type);


private :
	int _index;
	map<HERO_STATUS_TYPE,ItemTimer> _itemTimerMap;
	ItemTimer _itemTimerList[PROGRASSBAR_ARRAY_SIZE];
	//vector<ItemTimer> _itemTimerList;
};


#endif
