#include "PlayerLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CPlayerLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//위치 선정부터 한다.
	m_UIposition[0].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[0].y = m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[1].x = m_VisibleSize.width - DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[1].y =m_VisibleSize.height - DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[2].x = DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[2].y = DEFAULT_CHARACTER_MARGIN_V;

	m_UIposition[3].x =m_VisibleSize.width -  DEFAULT_CHARACTER_MARGIN_H;
	m_UIposition[3].y = DEFAULT_CHARACTER_MARGIN_V;

	//그림을 매번 불러올 순 없으니 일단 플레이 순서대로 캐릭터를 배열하고, 그 아이디를 저장해 놓도록 한다.
	for(int i = 0; i<CGameManager::GetInstance()->GetPlayerNumber();i++)
	{
		if (CGameManager::GetInstance()->GetPlayerIdByTurn(i)!=-1)
		{
			m_Character[i] = CGameManager::GetInstance()->GetPlayerIdByTurn(i);
			CCSprite* pTitle = CCSprite::create(CGameManager::GetInstance()->GetCharacterPlayFaceById(m_Character[i]).c_str());
			pTitle->setPosition(m_UIposition[i]);
			this->addChild(pTitle, 0);
		}
	}
	
	return true;

}

void CPlayerLayer::update( float dt )
{

}
