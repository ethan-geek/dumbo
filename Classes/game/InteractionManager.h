#if !defined(MS_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
#define MS_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "../model/interactionObject.h"
#include "../model/CoinObject.h"
#include "../model/FootBarObject.h"
#include "../model/FakeFootBarObject.h"
#include "../model/FullCoinItemObject.h"
#include "../model/SuperItemObject.h"
#include "../Common/XmlLoader.h"
#include "../pattern/StagePattern.h"

class InteractionManager 
{
public:
	InteractionManager(void);
	~InteractionManager(void);

	void addInteractionObject();
	void removeInteractionObject();

	void process(float frameVelocity, b2Body* body);

	void removeGarbage();


	StagePattern* _stagePattern;

	void addFullCoinObject();

	void changeHeight();
private :

	void checkRemoveList(b2Body* body);
	void processPosition(float frameVelocity, b2Body* body);
	void processContact(b2Body* body);

	b2BodyType getType();

	void createRigidBody(vector<interactionObject*>& pattern, float height = 0);

	void addObject();
	void addUnLimitedObject();

	UserInfo* _userInfo;

	vector<b2Body*> _removeList;
	float _currentHeight;
	float _currentHeightbyCheck;
	float _currentPatternHeight;

	float _groupHeight;
	float _resourceHeight;

	int _groupIndex;
	int _resourceIndex;

	float _nextHeight;
	bool _firstFullCoin;

	int _unlimitedStage;

	ResourcePattern* _pattern;

	AGApplication* _application;

	float _VIEW_HEIGHT;
};

#endif // !defined(MS_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
