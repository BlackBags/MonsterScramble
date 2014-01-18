#pragma once
#include "cocos2d.h"
#include "ccTypes.h"
#include "config.h"
#include <array>

//�÷��̾� ������
struct PlayerData
{
	PlayerData() : m_PlayerId(-1),m_PlayerName(""),m_CharacterId(-1),m_PlayerTurn(-1),
						m_MyTile(0), m_MyGold(0), m_MyTrash(0), m_MyTotalScore(0) {}

	//�÷��̾��� ���� ���̵� ( �¶��� ����� �� clientID�� �ǹ� )
	int m_PlayerId;

	//�÷��̾� �̸��� ����� ���� �ִٸ� �˾Ƽ� �ҷ������� �Ѵ�.
	std::string m_PlayerName;
	
	int m_CharacterId;
	
	int m_PlayerTurn;

	int m_MyTile;
	int m_MyGold;
	int m_MyTrash;

	int m_MyTotalScore;
};

//���� ĳ���Ϳ� ���� �ڷ� ( �߰� �ʿ� )
struct Character
{
	Character() : m_CharacterName("") {}

	std::string m_CharacterName;

	cocos2d::ccColor4B m_CharacterColor;

	std::string m_CharacterSelectImage;
	std::string m_CharacterPlayImage;
	std::string m_CharacterResultImage;
	std::string m_CharacterVoice;

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
	std::array<Character, CHARACTER_NUM> m_Character;


	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

