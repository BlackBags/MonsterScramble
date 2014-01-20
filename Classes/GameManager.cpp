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
		//온라인인 경우
		return;
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
		//온라인
		return;
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
		//온라인
		return false;
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
		//온라인
		return -1;
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
	if (m_IsOnlineGame)
	{
		//온라인
		return -1;
	}
	else
	{
		return CGameLogic::GetInstance()->GetPlayerTurn(currentTurn);
	}
}

void CGameManager::UpdateGameMap()
{
	if (m_IsOnlineGame)
	{
		//온라인
		return;
	}
	else
	{
		return;
	}
}

bool CGameManager::isEnd()
{
	if (m_IsOnlineGame)
	{
		//온라인
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsEnd();
	}
}

bool CGameManager::isPossible(IndexedPosition indexedPosition)
{
	if (m_IsOnlineGame)
	{
		//온라인
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsPossible(indexedPosition);
	}
}

bool CGameManager::isClosed(IndexedPosition indexedPosition)
{
	if (m_IsOnlineGame)
	{
		//온라인
		return false;
	}
	else
	{
		return CGameLogic::GetInstance()->IsClosed(indexedPosition);
	}
}

