#pragma once
#include "cocos2d.h"
#include "ccTypes.h"
#include "config.h"
#include <array>

//플레이어 데이터
struct PlayerData
{
	PlayerData() : m_PlayerId(-1),m_PlayerName("꿀호떡"),m_CharacterId(-1),m_PlayerTurn(-1),
						m_MyTile(0), m_MyGold(0), m_MyTrash(0), m_MyTotalScore(0) {}

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

	//이 함수는 필요 없을 것 같음. m_PlayerId = playerIdx 이므로 이미 알고 있는 정보를 다시 요청하는 것 같음
	int GetPlayerId(int playerIdx) {return m_PlayerData[playerIdx].m_PlayerId; }

	//캐릭터를 플레이어에게 짝지어 준다.
	void SetPlayerCharacterId(int playerId, int characterId)	{ m_PlayerData[playerId].m_CharacterId = characterId;}

	const std::string& GetPlayerName(int playerId)				{ return m_PlayerData[playerId].m_PlayerName; }
	
	const std::string& GetPlayerSettingImage(int playerId)		{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterSettingImage; }
	const std::string& GetPlayerPlayImage(int playerId)			{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterPlayImage; } 
	const std::string& GetPlayerResultImage(int playerId)		{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterResultImage; }
	const cocos2d::ccColor4B& GetPlayerColor(int playerId)		{ return m_Character[m_PlayerData[playerId].m_CharacterId].m_CharacterColor; }

	void SetPlayerTurn(int playerId, int turn)					{ m_PlayerData[playerId].m_PlayerTurn = turn; }
	int GetPlayerTurn(int palyerId)								{ return m_PlayerData[palyerId].m_PlayerTurn; }

	void		SetMapSize(int x, int y);
	MapSize		GetMapSize() {return m_MapSize;}

	void		SetPlayerNumber(int playerNumber)			{m_PlayerNumber = playerNumber;}
	int			GetplayerNumber()							{return m_PlayerNumber; }

	bool IsPossible(IndexedPosition indexedPosition);
	bool IsClosed(IndexedPosition indexedPosition);

	/*	주어진 index의 울타리 주변 타일을 확인 합니다 */
	void CollectClosedTile(IndexedPosition indexedPosition, Direction direction);

	/*	IsClosed함수에서 탐색 중인 타일이 이미 탐색된 곳인지 체크하는 함수입니다 */
	bool IsAlreadyChecked(const IndexedPosition& nextTile);

	void		UpdatePlayerResult(int playerId, MO_ITEM item);
	int			GetPlayerResult(int playerId, MO_ITEM item);

	void		UpdatePlayerScore(int playerId, int score)	{ m_PlayerData[playerId].m_MyTotalScore += score; }
	int			GetPlayerTotalScore(int playerId)			{return m_PlayerData[playerId].m_MyTotalScore; }

	int			GetWinnerIdx();

	bool IsEnd();

	/*	애니메이션 상태를 지정, 반환하는 함수들 */
	bool		GetLineAnimationFlag()									{ return m_LineAnimationFlag; }
	int			GetTileAnimationTurnNumber()							{ return m_TileAnimationTurnNumber; }
	void		SetTileAnimationTurnNumber(int turnNumber)				{ m_TileAnimationTurnNumber = turnNumber; }
	void		SetAnimationState(IndexedPosition indexedPosition, int turn, Direction direction);
	void		InitAnimationState(IndexedPosition indexedPosition);
	void		SetTileAnimationTurn(int turn)							{ m_TileAnimationTurn = turn; }
	int			GetTileAnimationTurn(IndexedPosition indexedPosition);

private:
	static CGameLogic*	m_pInstance; //singleton instance

	MapSize				m_MapSize;
	int						m_PlayerNumber;
	int						m_CurrentTurn;

	std::array<PlayerData, MAX_PLAYER_NUM> m_PlayerData;
	std::array<Character, CHARACTER_NUM> m_Character;

	//플레이 순서에 매칭되는 플레이어의 ID
	std::array<int, MAX_PLAYER_NUM> m_PlayerIdByTurn;

	/*	맵 관련 변수들 */

	//맵에 대한 정보를 저장하기 위한 배열 ( 실제 게임 상황이 실시간으로 업데이트 되어야 하는 배열 ) 
	//조심해!! MapObjMap은 이름이 왜 저모양인지?
	template <typename IType, int ROW, int COL>
	struct array2d_
	{
		typedef std::array< std::array<IType, COL>, ROW> type ;
	} ;

	typedef array2d_<MapObject, MAX_MAP_WIDTH, MAX_MAP_HEIGHT>::type MapObjMap ;
	MapObjMap m_Map;

	/*	주인이 없는 타일의 수를 저장하는 변수 : 종료 조건을 쉽게 확인하기 위해서 생성 */
	int	m_VoidTileCount;
	
	/* 닫힌 도형 검사용 배열 */
	std::array<IndexedPosition, CHECKLIST_LENGTH> m_ClosedTile;

	/* 애니메이션 관련 변수들 */
	bool	m_LineAnimationFlag;
	int		m_TileAnimationTurnNumber;
	int		m_TileAnimationTurn;
	bool	m_TileAnimationTurnOver;

	// implement the "static node()" method manually
    //CREATE_FUNC(CGameLogic);
};

