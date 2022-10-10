#if !defined(MS_GroupPattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
#define MS_GroupPattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "Pattern.h"
#include "ResourcePattern.h"

class GroupPattern : public Pattern
{
public:
	GroupPattern(void);
	~GroupPattern(void);

	vector<ResourcePattern*> _resourceList;

};

#endif //MS_Pattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_