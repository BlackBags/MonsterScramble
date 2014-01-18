#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

//플레이어 데이터
struct PlayerData
{
	//플레이어의 고유 아이디 ( 온라인 모드일 시 clientID를 의미 )
	int m_PlayerId;

	//플레이어 이름은 저장된 것이 있다면 알아서 불러오도록 한다.
	std::string m_PlayerName;
	
	int m_CharacterId;
	
	int m_PlayerTurn;

	int m_MyTile;
	int m_MyGold;
	int m_MyTrash;

	int m_MyTotalScore;
};

//몬스터 캐릭터에 관한 자료 ( 추가 필요 )
struct Character
{
	std::string m_CharacterName;

	GLfloat m_CharacterColor;

	std::string m_CharacterSelectImage;
	std::string m_CharacterPlayImage;
	std::string m_CharacterResultImage;
	std::string m_CharacterVoicePath;

};

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	static CGameLogic* CGameLogic::GetInstance();
	static void				ReleaseInstance();
	bool init();
	

private:
	static CGameLogic*	m_pInstance; //singleton instance


	MapSize				m_MapSize;

	std::array<PlayerData, MAX_PLAYER_NUM> m_PlayerData;
	std::array<Character, MAX_PLAYER_NUM> m_Character;


	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

