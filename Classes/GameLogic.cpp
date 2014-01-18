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
	//ĳ���� ���� �ڷḦ �־��ش�.
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

		//�Էµ� ��Ÿ�� �ֺ��� Ȯ���ؼ� �����ְ� ���� Ÿ�ϰ� ��Ƽ���� ���ڸ� ����
		if (m_Map[indexedPosition.m_PosI + 1][indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI - 1][ indexedPosition.m_PosJ].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ + 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		if (m_Map[indexedPosition.m_PosI][indexedPosition.m_PosJ - 1].m_Owner == MO_NOBODY) { ++tileVoidCount; }

		//Ȯ�ε� Ÿ���� ���� 4�� �Ǹ� �Էµ� ��Ÿ���� ���� Ÿ�ϵ� ���̿� �����Ƿ� ���� �� ����
		if (tileVoidCount == 4)
		{
			return true;
		}
	}

	return false;
}

bool CGameLogic::IsClosed( IndexedPosition indexedPosition )
{
	//���õ� ��Ÿ���� ���� Ȯ��
	CollectClosedTile(indexedPosition,DI_UP);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� ������ Ȯ��
	CollectClosedTile(indexedPosition, DI_RIGHT);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� �Ʒ��� Ȯ��
	CollectClosedTile(indexedPosition, DI_DOWN);
	if (m_ClosedTile[0].m_PosI != 0 && m_ClosedTile[0].m_PosJ != 0)
		return true;

	//���õ� ��Ÿ���� ���� Ȯ��
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

	//Ȯ�� �� ������ ����
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

	//Ȯ�� �� ������ ������� ���̸� Ȯ�� �� ��
	if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type != MO_DOT)
	{
		//Ÿ�Ͽ� �ִϸ��̼� �����ϴ� ���� ��Ÿ���� ���� ����
		int animationTurn = 1;
		SetAnimationState(currentTile, animationTurn, direction);

		//�տ��� ������ Ž�� ��� ������ ť�� �迭�� �ִ´�.
		int i = 0;

		searchTiles.push(currentTile);
		m_ClosedTile[i++] = currentTile;
		m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Flag = true;

		while (!searchTiles.empty() )
		{
			currentTile.m_PosI = searchTiles.front().m_PosI;
			currentTile.m_PosJ = searchTiles.front().m_PosJ;
			searchTiles.pop();

			//currentTile�� sentinel�̸� ���ݱ��� Ȯ���� �������δ� ������ ���������Ƿ� Ȯ���� Ÿ���� �����ϴ� �迭�� �ʱ�ȭ�ϰ� Ȯ�� ����
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_SENTINEL)
			{
				for (int tempI = 0 ; tempI < MAX_MAP_WIDTH; ++tempI)
				{
					for (int tempJ = 0 ; tempJ < MAX_MAP_HEIGHT; ++tempJ)
					{
						m_Map[tempI][tempJ].m_Flag = false;

						if (m_Map[currentTile.m_PosI][currentTile.m_PosJ].m_Type == MO_TILE)
						{
							//�ִϸ��̼� ����� ���� �����͵� �ʱ�ȭ
							InitAnimationState(IndexedPosition(tempI, tempJ));
						}

						//����� �ִϸ��̼��� �����Ƿ� 0���� ����
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
			CCLOG("��Ƽ���� ������\n");
#endif
				break;
			}
#ifdef _DEBUG
			CCLOG("idx I : %d / idx J : %d\n", currentTile.m_PosI, currentTile.m_PosJ);
#endif
			//���� Ÿ���� ���� Ȯ��
			if (m_Map[currentTile.m_PosI - 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI - 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosI].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_UP);
				}				
			}

			//���� Ÿ���� ������ Ȯ��
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ + 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ + 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_RIGHT);
				}				
			}

			//���� Ÿ���� �Ʒ��� Ȯ��
			if (m_Map[currentTile.m_PosI + 1][currentTile.m_PosJ].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI + 2;
				nextTile.m_PosJ = currentTile.m_PosJ;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_DOWN);
				}				
			}

			//���� Ÿ���� ���� Ȯ��
			if (m_Map[currentTile.m_PosI][currentTile.m_PosJ - 1].m_Type == MO_LINE_UNCONNECTED)
			{
				nextTile.m_PosI = currentTile.m_PosI;
				nextTile.m_PosJ = currentTile.m_PosJ - 2;
				if (!IsAlreadyChecked(nextTile) )
				{
					searchTiles.push(nextTile);
					m_ClosedTile[i++] = nextTile;
					m_Map[nextTile.m_PosI][nextTile.m_PosJ].m_Flag = true;

					//�ִϸ��̼� ����� ���� ������ ���� ����
					animationTurn = GetTileAnimationTurn(currentTile) + 1;
					SetAnimationState(nextTile, animationTurn, DI_LEFT);
				}				
			}
		}
		//���� Ÿ���� �����Ƿ� �ִϸ��̼� �����϶�� �÷��� ����
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


