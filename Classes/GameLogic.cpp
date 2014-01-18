#include "GameLogic.h"

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
			m_Character[0].m_CharacterSelectImage = "CHARACTER_1_Play.png";
			m_Character[0].m_CharacterPlayImage = "CHARACTER_1_Play.png";
			m_Character[0].m_CharacterResultImage = "PLAYER_face1.png";
			m_Character[0].m_CharacterVoice = "Sound/PLAYER_1_good.mp3";
			break;
		case 1:
			m_Character[1].m_CharacterName = "Blue";
			m_Character[1].m_CharacterColor = ccc4(_COLOR_CHARACTER_2_ );
			m_Character[1].m_CharacterSelectImage = "CHARACTER_2_Play.png";
			m_Character[1].m_CharacterPlayImage = "CHARACTER_2_Play.png";
			m_Character[1].m_CharacterResultImage = "PLAYER_face2.png";
			m_Character[1].m_CharacterVoice = "Sound/PLAYER_2_good.mp3";			
			break;
		case 2:
			m_Character[2].m_CharacterName = "Red";
			m_Character[2].m_CharacterColor = ccc4(_COLOR_CHARACTER_3_ );
			m_Character[2].m_CharacterSelectImage = "CHARACTER_3_Play.png";
			m_Character[2].m_CharacterPlayImage = "CHARACTER_3_Play.png";
			m_Character[2].m_CharacterResultImage = "PLAYER_face3.png";
			m_Character[2].m_CharacterVoice = "Sound/PLAYER_3_good.mp3";
			break;
		case 3:
			m_Character[3].m_CharacterName = "Yellow";
			m_Character[3].m_CharacterColor =ccc4( _COLOR_CHARACTER_4_) ;
			m_Character[3].m_CharacterSelectImage = "CHARACTER_4_Play.png";
			m_Character[3].m_CharacterPlayImage = "CHARACTER_4_Play.png";
			m_Character[3].m_CharacterResultImage = "PLAYER_face4.png";
			m_Character[3].m_CharacterVoice = "Sound/PLAYER_4_good.mp3";	
			break;

		}
	}

	return true;
}
