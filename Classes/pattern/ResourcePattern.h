#if !defined(MS_ResourcePattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
#define MS_ResourcePattern_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"
#include "Pattern.h"
#include "../model/interactionObject.h"

class ResourcePattern : public Pattern
{
public:
	ResourcePattern(void);
	~ResourcePattern(void);

	vector<interactionObject*> _interactionList;
};


#endif
