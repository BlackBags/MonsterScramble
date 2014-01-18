#pragma once
#include "cocos2d.h"
#include "config.h"
#include <array>

//�÷��̾� ������
struct PlayerData
{
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

