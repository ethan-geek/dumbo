

#if !defined(HH_XmlCreator)
#define HH_XmlCreator

#include "./HiHighCommon.h"
#include "../model/UserInfo.h"
#include "../lib/pugixml.hpp"

#include <sstream>


using namespace pugi;


class XmlCreator
{
public:
	XmlCreator(void);
	~XmlCreator(void);

	static XmlCreator* getInstance();

	string convertString(UserInfo* info);

};

#endif

