#include "GroupPattern.h"


GroupPattern::GroupPattern(void) 
{
}


GroupPattern::~GroupPattern(void)
{

	for(int indexI = 0 ; indexI < _resourceList.size(); ++indexI) {
		delete _resourceList[indexI];
	}

}
