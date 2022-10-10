///////////////////////////////////////////////////////////
//  Background.h
//  Implementation of the Class Background
//  Created on:      19-3-2014 ���� 11:55:01
//  Original author: asinayo
///////////////////////////////////////////////////////////

#if !defined(EA_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
#define EA_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_

#include "../common/HiHighCommon.h"

class Background
{

public:
	Background();
	virtual ~Background();

	virtual void addBackground(CCParallaxNode* node) = 0;
	virtual void removeBackground(CCParallaxNode* node);

protected:
	virtual void readyBackgroundIndex() = 0;

	
	CCPoint _position;

	CCSize _winSize;
	vector<string> _images;
	//string _plistName;
	AGApplication* _application;
	float _backgroundHeight;
	float _backgroundIndex;
};

#endif // !defined(EA_648FD14B_6020_4715_83E7_4E7232FF035E__INCLUDED_)
