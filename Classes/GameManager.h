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

	//게임이 온라인인지 오프라인인지 설정
	void SetOnlineMode(bool flag)	{ m_IsOnlineGame = flag; }

	//플레이어 이름 받아 오기
	const std::string& GetPlayerName(int playerIdx);

	//result scene 관련
	int GetWinnerIdx();
	int GetElementCount (int playerIdx, MO_ITEM item);
	int GetTotalScore(int playerIdx);
	const std::string& GetCharacterResultFaceFileName(int playerIdx);

private:

	static CGameManager*	m_pInstance; //singleton instance

	bool m_IsOnlineGame;

	//캐릭터 이름이나 맵 상태 정보들은 매니저가 캐싱해서 가지고 있는 것이 좋을 듯
	//대신 그 데이터를 기반으로 무언가를 판단하는 로직은 없도록 주의(일단 인풋이 있으면 전송하고 결과값만 받는 방식 유지)

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameManager);
};

