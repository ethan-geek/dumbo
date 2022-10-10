#include "HHSecurity.h"
//#include "../lib/McbDES2.hpp"
#include "../lib/base64.h"



HHSecurity* g_security = NULL;

HHSecurity::HHSecurity(void)
{
	_temp1 = "hiflsnvkdnsldkfdlalsldlfienapqec";
	_temp2 = "uivnalskflaiaqpezdvlvcazaqefofie";
	_temp3 = "soasdfpcivnclzlqwsdvoaoepsovkand";
	_temp4 = "flkejlfkhasdknflkajsndflkjnlkaj";
}


HHSecurity::~HHSecurity(void)
{
}

HHSecurity* HHSecurity::getInstance() {
	if(g_security == NULL) {
		g_security = new HHSecurity();
	}

	return g_security;
}

const std::string xorEncode(std::string text, std::string key) {
    std::string output = text;
    const unsigned int n = text.size();
    const unsigned int keyN = key.size();
    unsigned int keyIndex = 0;
    for (unsigned int i = 0; i < n; i++) {
        output[i] ^= key[keyIndex];
        keyIndex = (keyIndex + 1) % keyN;
    }
    return output;
}

string HHSecurity::Encryption(const char* division, string str) {

	string encodedstr;

	

	
	char temp1[33];
	temp1[0] = _temp1[3];
	temp1[1] = _temp4[6];
	temp1[2] = _temp1[1];
	temp1[3] = _temp3[12];
	temp1[4] = _temp2[0];
	temp1[5] = _temp1[5];
	temp1[6] = _temp2[23];
	temp1[7] = _temp4[2];
	temp1[8] = _temp4[2];
	temp1[9] = _temp1[3];
	temp1[10] = _temp4[16];
	temp1[11] = _temp4[26];
	temp1[12] = _temp1[31];
	temp1[13] = _temp3[2];
	temp1[14] = _temp2[20];
	temp1[15] = _temp1[5];
	temp1[16] = _temp2[23];
	temp1[17] = _temp4[12];
	temp1[18] = _temp1[19];
	temp1[19] = _temp4[28];
	temp1[20] = _temp4[11];
	temp1[21] = _temp4[9];
	temp1[22] = _temp1[32];
	temp1[23] = _temp3[18];
	temp1[24] = _temp2[15];
	temp1[25] = _temp1[25];
	temp1[26] = _temp2[21];
	temp1[27] = _temp4[12];
	temp1[28] = _temp1[30];
	temp1[29] = _temp4[10];
	temp1[30] = _temp4[0];
	temp1[31] = _temp4[16];
	temp1[32] = '\0';

	string encodeBase = encodedstr = base64_encode(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());;
	string encodeXor = xorEncode(encodeBase, temp1);
	encodedstr = base64_encode(reinterpret_cast<const unsigned char*>(encodeXor.c_str()), encodeXor.length());
	
	return encodedstr;
	

}
string HHSecurity::Decryption(const char* division,string str) {

	string encodedstr;

	//encodedstr  = base64_decode(str);


	
	char temp1[33];
	temp1[0] = _temp1[3];
	temp1[1] = _temp4[6];
	temp1[2] = _temp1[1];
	temp1[3] = _temp3[12];
	temp1[4] = _temp2[0];
	temp1[5] = _temp1[5];
	temp1[6] = _temp2[23];
	temp1[7] = _temp4[2];
	temp1[8] = _temp4[2];
	temp1[9] = _temp1[3];
	temp1[10] = _temp4[16];
	temp1[11] = _temp4[26];
	temp1[12] = _temp1[31];
	temp1[13] = _temp3[2];
	temp1[14] = _temp2[20];
	temp1[15] = _temp1[5];
	temp1[16] = _temp2[23];
	temp1[17] = _temp4[12];
	temp1[18] = _temp1[19];
	temp1[19] = _temp4[28];
	temp1[20] = _temp4[11];
	temp1[21] = _temp4[9];
	temp1[22] = _temp1[32];
	temp1[23] = _temp3[18];
	temp1[24] = _temp2[15];
	temp1[25] = _temp1[25];
	temp1[26] = _temp2[21];
	temp1[27] = _temp4[12];
	temp1[28] = _temp1[30];
	temp1[29] = _temp4[10];
	temp1[30] = _temp4[0];
	temp1[31] = _temp4[16];
	temp1[32] = '\0';

	
	string decodeStr = base64_decode(str);

	string decodeXor = xorEncode(decodeStr, temp1);

	string decodeStr2 = base64_decode(decodeXor);
	
	
	return decodeStr2;
}

void HHSecurity::initSave() {

}
