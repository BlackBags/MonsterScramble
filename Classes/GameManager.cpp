#include "GameManager.h"

USING_NS_CC;

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{

}

CGameManager::~CGameManager(void)
{
}

CGameManager* CGameManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameManager();
	}

	return m_pInstance;
}

void CGameManager::ReleaseInstance()
{
}

bool CGameManager::init()
{

	return true;
}
