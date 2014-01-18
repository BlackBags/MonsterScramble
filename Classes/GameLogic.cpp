#include "GameLogic.h"
#include <queue>

USING_NS_CC;

CGameLogic* CGameLogic::m_pInstance = nullptr;

CGameLogic::CGameLogic(void)
{

}


CGameLogic::~CGameLogic(void)
{
}

CGameLogic* CGameLogic::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGameLogic();
	}

	return m_pInstance;
}

void CGameLogic::ReleaseInstance()
{
}

bool CGameLogic::init()
{
	//캐릭터 관련 자료를 넣어준다.
	for (int i = 0;i<CHARACTER_NUM;++i)
	{
		switch(i)
		{
		case 0:
			m_Character[0].m_CharacterName = "Green";
			m_Character[0].m_CharacterColor = ccc4(_COLOR_CHARACTER_1_) ;
			m_Character[0].m_CharacterSettingImage = "CHARACTER_1_Play.png";
			m_Character[0].m_CharacterPlayImage = "CHARACTER_1_Play.png";
			m_Character[0].m_CharacterResultImage = "PLAYER_face1.png";
			m_Character[0].m_CharacterVoice = "Sound/PLAYER_1_good.mp3";
			break;
		case 1:
			m_Character[1].m_CharacterName = "Blue";
			m_Character[1].m_CharacterColor = ccc4(_COLOR_CHARACTER_2_ );
			m_Character[1].m_CharacterSettingImage = "CHARACTER_2_Play.png";
			m_Character[1].m_CharacterPlayImage = "CHARACTER_2_Play.png";
			m_Character[1].m_CharacterResultImage = "PLAYER_face2.png";
			m_Character[1].m_CharacterVoice = "Sound/PLAYER_2_good.mp3";			
			break;
		case 2:
			m_Character[2].m_CharacterName = "Red";
			m_Character[2].m_CharacterColor = ccc4(_COLOR_CHARACTER_3_ );
			m_Character[2].m_CharacterSettingImage = "CHARACTER_3_Play.png";
			m_Character[2].m_CharacterPlayImage = "CHARACTER_3_Play.png";
			m_Character[2].m_CharacterResultImage = "PLAYER_face3.png";
			m_Character[2].m_CharacterVoice = "Sound/PLAYER_3_good.mp3";
			break;
		case 3:
			m_Character[3].m_CharacterName = "Yellow";
			m_Character[3].m_CharacterColor =ccc4( _COLOR_CHARACTER_4_) ;
			m_Character[3].m_CharacterSettingImage = "CHARACTER_4_Play.png";
			m_Character[3].m_CharacterPlayImage = "CHARACTER_4_Play.png";
			m_Character[3].m_CharacterResultImage = "PLAYER_face4.png";
			m_Character[3].m_CharacterVoice = "Sound/PLAYER_4_good.mp3";	
			break;

		}
	}

	return true;
}

void CGameLogic::SetMapSize( int x, int y )
{
	m_MapSize.m_Height = y;
	m_MapSize.m_Width = x;
}

void CGameLogic::UpdatePlayerResult( int playerId, MO_ITEM item )
{
	++m_PlayerData[playerId].m_MyTile;

	switch (item)
	{
	case MO_GOLD:
		++m_PlayerData[playerId].m_MyGold;
		break;
	case MO_TRASH:
		++m_PlayerData[playerId].m_MyTrash;
		break;
	default:
		break;
	}
}

int CGameLogic::GetPlayerResult(int playerId, MO_ITEM item)
{
	switch (item)
	{
	case MO_NOTHING:
		return m_PlayerData[playerId].m_MyTile;
		break;
	case MO_GOLD:
		return m_PlayerData[playerId].m_MyGold;
		break;
	case MO_TRASH:
		return m_PlayerData[playerId].m_MyTrash;
		break;
	default:
		break;
	}
}

bool CGameLogic::IsPossible(IndexedPosition indexedPosition)
{
	if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type == MO_LINE_UNCONNECTED ||m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Type == MO_LINE_HIDDEN)
	{
		int tileVoidCount = 0;

		//입력된 울타리 주변을 확인해서 소유주가 없는 타일과 센티널의 숫자를 센다
		if (m_Map[indexedPosition.m_PosI + 1][indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI - 1][ indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ + 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ - 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		//확인된 타일의 수가 4가 되면 입력된 울타리는 열린 타일들 사이에 있으므로 그을 수 있음
		if (tileVoidCount == 4)
		{
			return true;
		}
	}

	return false;
}

bool CGameLogic::IsClosed( IndexedPosition indexedPosition )
{
	//선택된 울타리의 위쪽 확인
	CollectClosedTile(indexedPosition,DI_UP);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 오른쪽 확인
	CollectClosedTile(indexedPosition, DI_RIGHT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 아래쪽 확인
	CollectClosedTile(indexedPosition, DI_DOWN);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//선택된 울타리의 왼쪽 확인
	CollectClosedTile(indexedPosition, DI_LEFT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	return false;
}

bool CGameLogic::IsEnd()
{
	return (m_VoidTileCount == 0);
}

void CGameLogic::CollectClosedTile( IndexedPosition indexedPosition, Direction direction )
{
	std::queue<IndexedPosition> searchTiles;

	IndexedPosition currentTile;
	IndexedPosition nextTile;

	//확인 할 방향을 지정
	switch (direction)
	{
	case DI_UP:
		currentTile.m_PosI = indexedPosition.m_PosI - 1;
		currentTile.m_PosJ = indexedPosition.m_PosJ;
		break;
	case DI_RIGHT:
		currentTile.m_PosI = indexedPosition.m_PosI;
		currentTile.m_PosJ = indexedPosition.m_PosJ + 1;
		break;
	case DI_DOWN:
		currentTile.m_PosI = indexedPosition.m_PosI + 1;
		currentTile.m_PosJ = indexedPosition.m_PosJ;
		break;
	case DI_LEFT:
		currentTile.m_PosI = indexedPosition.m_PosI;
		currentTile.m_PosJ = indexedPosition.m_PosJ - 1;
		break;
	default:
		break;
	}

	//확인 할 방향의 출발점이 점이면 확인 안 함
	if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type != MO_DOT)
	{
		//타일에 애니메이션 적용하는 순서 나타내기 위한 변수
		int animationTurn = 1;
		SetAnimationState(currentTile, animationTurn, direction);

		//앞에서 갱신한 탐색 출발 지점을 큐와 배열에 넣는다.
		int i = 0;

		searchTiles.push(currentTile);
		m_ClosedTile[i++] = currentTile;
		m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Flag = true;

		while (!searchTiles.empty() )
		{
			currentTile.m_PosI = searchTiles.front().m_PosI;
			currentTile.m_PosJ = searchTiles.front().m_PosJ;
			searchTiles.pop();

			//currentTile이 sentinel이면 지금까지 확인한 방향으로는 도형이 열려있으므로 확인한 타일을 저장하는 배열은 초기화하고 확인 종료
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_SENTINEL)
			{
				for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
				{
					for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
					{
						m_Map[tempI][tempJ].m_Flag = false;

						if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_TILE)
						{
							//애니메이션 재생을 위한 데이터도 초기화
							InitAnimationState(IndexedPosition(tempI, tempJ));
						}

						//재생할 애니메이션이 없으므로 0으로 설정
						animationTurn = 0;
					}
				}
				//memset(m_ClosedTile, 0, sizeof(IndexedPosition) * CHECKLIST_LENGTH);

				for (int i = 0; i < m_ClosedTile.size(); ++i)
				{
					m_ClosedTile[i].m_PosI = 0;
					m_ClosedTile[i].m_PosJ = 0;
				}
#ifdef _DEBUG
			CCLOG("센티넬을 만났다\n");
#endif
				break;
			}
#ifdef _DEBUG
			CCLOG("idx I : %d / idx J : %d\n", currentTile.m_PosI, currentTile.m_PosJ);
#endif
			//현재 타일의 위쪽 확인
			if (m_Map[currentTile.m_PosI - 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI - 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosI].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_UP);
				}				
			}

			//현재 타일의 오른쪽 확인
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ + 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ + 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_RIGHT);
				}				
			}

			//현재 타일의 아래쪽 확인
			if (m_Map[currentTile.m_PosI + 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI + 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_DOWN);
				}				
			}

			//현재 타일의 왼쪽 확인
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ - 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ - 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//애니메이션 재생을 위한 순서와 방향 지정
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_LEFT);
				}				
			}
		}
		//닫힌 타일이 있으므로 애니메이션 실행하라는 플래그 설정
		SetTileAnimationTurnNumber(animationTurn);
	}
}

bool CGameLogic::IsAlreadyChecked( const IndexedPosition& nextTile )
{
	return m_Map[nextTile.m_PosI][nextTile.m_PosI].m_Flag;
}

void CGameLogic::SetAnimationState(IndexedPosition indexedPosition, int turn, Direction direction)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = true;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn = turn;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Direction = direction;
}

void CGameLogic::InitAnimationState(IndexedPosition indexedPosition)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn = 0;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationFlag = false;
	m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_Direction = DI_UP;
}

int	CGameLogic::GetTileAnimationTurn(IndexedPosition indexedPosition)
{
	assert(indexedPosition.m_PosI < MAX_MAP_WIDTH && indexedPosition.m_PosJ<MAX_MAP_HEIGHT) ;

	return m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ].m_AnimationTurn;
}


