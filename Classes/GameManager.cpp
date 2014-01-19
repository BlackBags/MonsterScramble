#include "GameManager.h"
#include "GameLogic.h"

CGameManager* CGameManager::m_pInstance = nullptr;

CGameManager::CGameManager(void)
{
	m_IsOnlineGame = false;
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


void CGameManager::SetPlayerName(int playerId,  const std::string& playerName )
{
	if (m_IsOnlineGame)
	{

	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerName(playerId,playerName);
	}
}


const std::string& CGameManager::GetPlayerName(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerName(playerIdx);
	}
}

int CGameManager::GetPlayerNumber()
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetplayerNumber();
	}
}

void CGameManager::SetPlayerNumber(int PlayerNumber)
{
	if (m_IsOnlineGame)
	{
		//server로 패킷을 보낸다.
	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerNumber(PlayerNumber);
	}
}

int CGameManager::GetWinnerIdx()
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetWinnerIdx();
	}
}

int CGameManager::GetElementCount(int playerIdx, MO_ITEM item)
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerResult(playerIdx, item);
	}
}

int CGameManager::GetTotalScore(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerTotalScore(playerIdx);
	}
}


const std::string& CGameManager::GetCharacterResultFaceFileName(int playerIdx)
{
	if (m_IsOnlineGame)
	{
		//server에서 필요한 정보를 받아 온다.
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerResultImage(playerIdx);
	}
}

void CGameManager::SelectCharacter( int playerId, int characterId )
{
	if (m_IsOnlineGame)
	{

	}
	else
	{
		CGameLogic::GetInstance()->SetPlayerCharacterId(playerId,characterId);
	}
}

bool CGameManager::isCharacterSelected( int characterId )
{
	if (m_IsOnlineGame)
	{

	}
	else
	{
		return CGameLogic::GetInstance()->isCharacterSelected(characterId);
	}
}

int CGameManager::GetCharacterId( int playerId )
{
	if (m_IsOnlineGame)
	{

	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerCharacterId( playerId );
	}
}

void CGameManager::SetRandomPlayerTurn()
{

}

int CGameManager::GetPlayerIdByTurn( int currentTurn )
{
	// 조심해!!
	return 0;
}
