#pragma once
#include "cocos2d.h"

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static CGameManager* CGameManager::GetInstance();
	static void				ReleaseInstance();
	
	bool init();


private:

	static CGameManager*	m_pInstance; //singleton instance

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

