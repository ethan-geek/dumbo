

#if !defined(HH_HIHIGH_GAMEDATA)
#define HH_HIHIGH_GAMEDATA

#define COMBO_TIME				1.3

#include <vector>

using namespace std;

class UserInfo;

class HiHighGameData {

public :

	HiHighGameData();
	~HiHighGameData();

	void initData();
	void initMeter();
	void increaseGold(float amount);
	void decreaseGold(float amount);
	void increaseCombo();
	void increaseItemCount();

	void setCurrentStage(int currentStage);
	void addGameTime(float goldAMount);
	void setMiter(float miter);
	void setDirectMeter(float meter);

	float getGoldAmount();
	int getCombo();
	int getMaxCombo();
	int getCurrentStage();
	float getGameTime();
	float getMiter();
	int getItemCount();
	int getRenewalIndex();

	void setFbFriendRecordList(vector<UserInfo>* fbFriendRecordList);
    vector<UserInfo> & getFbFriendRecordList();
	UserInfo* getCurrentRecordFriend();
	UserInfo* getNextRecordFriend();

	bool isRenewal();

	void initCombo();

private :

	void viewComboCount();

	float _goldAmount;
	int _maxCombo;
	float _miter;
	float _gameTime;

	int _combo;
	float _comboDt;

	int _currentStage;
	int _useItemCount;

	vector<UserInfo> _fbFriendRecordList;
	int _myRecordIndex;
	int _renewalndex;
};



#endif
