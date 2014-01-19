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

	//������ �¶������� ������������ ����
	void SetOnlineMode(bool flag)	{ m_IsOnlineGame = flag; }

	//�÷��̾� �̸� �޾� ����
	const std::string& GetPlayerName(int playerIdx);

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

