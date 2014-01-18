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

	std::string m_CharacterSettingImage;
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

	int GetPlayerId(int playerIdx) {return m_PlayerData[playerIdx].m_PlayerId; }

	//ĳ���͸� �÷��̾�� ¦���� �ش�.
	void SetPlayerCharacterId(int playerId, int characterId) { m_PlayerData[playerId].m_CharacterId = characterId;}

	const std::string& GetPlayerName(int playerId)			{ return m_PlayerData[playerId].m_PlayerName; }
	
	const std::string& GetPlayerSettingImage(int playerId)		{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterSettingImage; }
	const std::string& GetPlayerPlayImage(int playerId)			{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterPlayImage; } 
	const std::string& GetPlayerResultImage(int playerId) { return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterResultImage; }
	const cocos2d::ccColor4B& GetPlayerColor(int playerId) { return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterColor; }

	void SetPlayerTurn(int playerId, int turn)				{ m_PlayerData[playerId].m_PlayerTurn = turn; }
	int GetPlayerTurn(int palyerId)							{ return m_PlayerData[palyerId].m_PlayerTurn; }

	void		SetMapSize(int x, int y);
	MapSize		GetMapSize() {return m_MapSize;}

	void		SetPlayerNumber(int playerNumber)			{m_PlayerNumber = playerNumber;}
	int			GetplayerNumber()							{return m_PlayerNumber; }

	void		UpdatePlayerResult(int playerId, MO_ITEM item);
	int			GetPlayerResult(int playerId, MO_ITEM item);

	void		UpdatePlayerScore(int playerId, int score) { m_PlayerData[playerId].m_MyTotalScore += score; }
	int			GetPlayerTotalScore(int playerId) {return m_PlayerData[playerId].m_MyTotalScore; }

private:
	static CGameLogic*	m_pInstance; //singleton instance

	MapSize				m_MapSize;
	int						m_PlayerNumber;

	std::array<PlayerData, MAX_PLAYER_NUM> m_PlayerData;
	std::array<Character, CHARACTER_NUM> m_Character;


	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

