
#if !defined(HH_ITEMOBJECT)
#define HH_ITEMOBJECT

#include "./interactionObject.h"

#define STR_SUPER_ITEM_NAME		"SUPER HIGH"
#define STR_FULL_COIN_ITEM_NAME	"FULL COIN"
#define STR_SHIELD_ITEM_NAME	"SHIELD"
#define STR_PARACHUTE_ITEM_NAME	"PARACHUTE"
#define STR_MAGNET_ITEM_NAME	"MAGNET"
#define STR_DOUBLE_ITEM_NAME	"DOUBLE"
#define STR_START_ITEM_NAME		"START"

class ItemObject : public interactionObject
{
public:
	ItemObject(void);
	virtual ~ItemObject(void);

	virtual void useItem() {};
	virtual void processContact();

	void applyUpgrade(const char* itemStr);

	float getKeepTime();

protected:
	float _keepTime;
};

#endif
