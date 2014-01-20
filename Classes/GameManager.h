#pragma once
#include "cocos2d.h"
#include "config.h"

class CGameManager
{
public:
	CGameManager(void);
	~CGameManager(void);

	static CGameManager* CGameManager::GetInstance();
	static void				ReleaseInstance();
	
	bool init();

	int GetPlayerNumber();
	void SetPlayerNumber(int PlayerNumber);

	//������ �¶������� ������������ ����
	void SetOnlineMode(bool flag)	{ m_IsOnlineGame = flag; }

	/* ���� ���� ���� */
	// �̸�
	void SetPlayerName(int playerId, const std::string& playerName);
	const std::string& GetPlayerName(int playerIdx);

	// ĳ����
	void SelectCharacter(int characterId);
	bool isCharacterSelected(int characterId);
	int	  GetCharacterId(int playerId);

	// ��
	void		SetMapSize(MapSelect mapSize);

	// ��
	// ���� �Ͽ� �ش��ϴ� �÷��̾� 'ID'�� ��ȯ�Ѵ�.
	int  GetPlayerIdByTurn(int currentTurn);

	void StartGame();
	
	/* ���� ���� ���� : �ǽð� ���� ����� ���� �ʿ��� �ϵ��� �Ѵ�.*/
	void UpdateGameMap();
	bool isEnd();
	bool isPossible(IndexedPosition indexedPosition);
	bool isClosed(IndexedPosition indexedPosition);
	

	//result scene ����
	int GetWinnerIdx();
	int GetElementCount (int playerIdx, MO_ITEM item);
	int GetTotalScore(int playerIdx);
	const std::string& GetCharacterResultFaceFileName(int playerIdx);

private:

	static CGameManager*	m_pInstance; //singleton instance

	bool m_IsOnlineGame;

	//ĳ���� �̸��̳� �� ���� �������� �Ŵ����� ĳ���ؼ� ������ �ִ� ���� ���� ��
	//��� �� �����͸� ������� ���𰡸� �Ǵ��ϴ� ������ ������ ����(�ϴ� ��ǲ�� ������ �����ϰ� ������� �޴� ��� ����)

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

