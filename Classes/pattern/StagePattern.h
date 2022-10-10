#if !defined(MS_StagePattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
#define MS_StagePattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "Pattern.h"
#include "GroupPattern.h"

class StagePattern : public Pattern
{
public:
	StagePattern(void);
	~StagePattern(void);

	vector<GroupPattern*> _groupList;

};

#endif