
#ifndef HH_SECURITY
#define HH_SECURITY

#include "./HiHighCommon.h"
//#include "../lib/encypher/endetool.h"


class HHSecurity
{
public:
	HHSecurity(void);
	~HHSecurity(void);

	static HHSecurity* getInstance();

	void initSave();

	string Encryption(const char* division, string str);
	string Decryption(const char* division, string str);

private :
	char* _temp1;
	char* _temp2;
	char* _temp3;
	char* _temp4;
};

#endif
