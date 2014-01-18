#pragma once
#include "cocos2d.h"

class CGameManager
{
public:
	//create 사용 안 하고 수동으로 관리할까?
	//그럼 생성자 소멸자 필요
	
	bool init();

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

