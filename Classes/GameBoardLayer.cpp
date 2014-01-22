#include "GameBoardLayer.h"
#include "GameManager.h"
#include "CMO_tile.h"
#include "CMO_dot.h"
#include "CMO_line.h"

USING_NS_CC;

bool CGameBoardLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}



	//////////////////////////////
	// 2. add resources
	// ����ϴ� ��� �ڿ��� �ϴ� ��� ����ϰ� ���ü� �Ӽ��� �ٲܱ�...�ƹ�ư


	m_VisibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	
	int rowNum = 0;
	int columnNum = 0;

	if (CGameManager::GetInstance()->GetSelectedMapSize() == MS_6X5 )
	{
		rowNum = 5;
		columnNum = 6;
	}
	else
	{
		rowNum = 7;
		columnNum = 8;
	}

	CCSprite * board = CCSprite::create("image/board.png", CCRect(0,0,columnNum*DEFAULT_TILE_SIZE,rowNum*DEFAULT_TILE_SIZE));
	board->setAnchorPoint(ccp(0.5f,0.5f));
	board->setPosition(ccp(m_VisibleSize.width/2, m_VisibleSize.height/2));
	this->addChild(board);

	m_BoardOrigin.x = (m_VisibleSize.width - (DEFAULT_TILE_SIZE*columnNum))/2;
	m_BoardOrigin.y = (m_VisibleSize.height - (DEFAULT_TILE_SIZE*rowNum))/2;

	for (int i = 1; i<rowNum*2+2;++i)
	{
		for(int j = 1; j<columnNum*2+2;++j)
		{
			IndexedPosition pos;
			pos.m_PosI = i;
			pos.m_PosJ = j;

			//��, �� ��� ¦�� �� ��� Ÿ���� �׸���.
			if ( i %2 == 0 && j%2 == 0)
			{
				CMO_tile* pTile = CMO_tile::Create(pos);
				pTile->setAnchorPoint(ccp(0,0));
				pTile->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2-1),DEFAULT_TILE_SIZE*(i/2-1)));

				board->addChild(pTile,0);
			}
			// ��, �� ��� Ȧ���� ��� ���� �׸���.
			else if ( i %2 == 1 && j%2 == 1)
			{
				CMO_dot* pDot = CMO_dot::Create();
				pDot->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2),DEFAULT_TILE_SIZE*(i/2)));

				board	->addChild(pDot,2);
			}
			//�� �ܿ��� ���̴�.
			else
			{
				CMO_line* pLine = CMO_line::Create(pos);
				//�����ִ�.
				if ( j %2 == 0 )
				{
					pLine->setAnchorPoint(ccp(0,0.5));
					pLine->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2-1),DEFAULT_TILE_SIZE*(i/2)));
				}
				else
				{
					pLine->setAnchorPoint(ccp(0.5,0));
					pLine->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2),DEFAULT_TILE_SIZE*(i/2-1)));
				}


				board->addChild(pLine,1);
			}			
		}
	}

	this->setTouchEnabled(true);
	

}

void CGameBoardLayer::DrawMapObjects()
{
	
}

void CGameBoardLayer::ccTouchesBegan( CCSet* pTouches, CCEvent* pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();

	m_StartPoint = pTouch->getLocationInView();

	CCLog("Start point =  %f, %f", m_StartPoint.x,m_StartPoint.y);
}

void CGameBoardLayer::ccTouchesEnded( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch *pTouch = (CCTouch*)pTouches->anyObject();

	m_EndPoint  = pTouch->getLocationInView();
	CCLog("End point =  %f, %f", m_EndPoint.x,m_EndPoint.y);
	DrawLine();
}

void CGameBoardLayer::DrawLine()
{
	IndexedPosition startIndex = ConvertCoordinate(m_StartPoint);
	IndexedPosition endIndex = ConvertCoordinate(m_EndPoint);
	
	//���� �ΰ��� ���մϴ�.
	//���� ���� ���
	if(startIndex.m_PosI == endIndex.m_PosI)
	{
		if(endIndex.m_PosJ - startIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine(IndexedPosition(startIndex.m_PosI, endIndex.m_PosJ-1));
		}
		else if(startIndex.m_PosJ - endIndex.m_PosJ == 2)
		{
			CGameManager::GetInstance()->DrawLine(IndexedPosition(startIndex.m_PosI, startIndex.m_PosJ-1));
		}
	}
	//���� ���� ���
	else if(startIndex.m_PosJ == endIndex.m_PosJ)
	{
		if(endIndex.m_PosI - startIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine(IndexedPosition(endIndex.m_PosI-1,startIndex.m_PosJ));
		}
		else if(startIndex.m_PosI - endIndex.m_PosI == 2)
		{
			CGameManager::GetInstance()->DrawLine(IndexedPosition(startIndex.m_PosI-1, startIndex.m_PosJ));
		}
	}
}

IndexedPosition CGameBoardLayer::ConvertCoordinate(CCPoint point)
{
	// (0,0)�� ���� ���� �Ʒ��� �Űܿ´�.
	point.y = m_VisibleSize.height - point.y;

	//���� �ε����� �ٲ۴�.
	IndexedPosition indexedPosition;
	
	//����, ������ ������� Ȯ���Ѵ�.
	if ((point.x - m_BoardOrigin.x) < 0 || (point.y - m_BoardOrigin.y) < 0 || (m_VisibleSize.width - point.x) < m_BoardOrigin.x || (m_VisibleSize.height - point.y) < m_BoardOrigin.y)
	{
		indexedPosition.m_PosI = 0;
		indexedPosition.m_PosJ = 0;
		return indexedPosition;
	}

	//������!!
	//���� ������ dot�� Ŭ���� �� �ִ� �������� Ȯ���Ѵ�.
	if (static_cast<int>(point.x-m_BoardOrigin.x)%static_cast<int>(DEFAULT_TILE_SIZE) < 20)
		indexedPosition.m_PosI = static_cast<int>(point.x-m_BoardOrigin.x)/static_cast<int>(DEFAULT_TILE_SIZE);
	else if (static_cast<int>(point.x-m_BoardOrigin.x)%static_cast<int>(DEFAULT_TILE_SIZE) > DEFAULT_TILE_SIZE - 20)
		indexedPosition.m_PosI = static_cast<int>(point.x-m_BoardOrigin.x)/static_cast<int>(DEFAULT_TILE_SIZE) + 1;

	if (static_cast<int>(point.y-m_BoardOrigin.y)%static_cast<int>(DEFAULT_TILE_SIZE) < 20)
		indexedPosition.m_PosJ = static_cast<int>(point.y-m_BoardOrigin.y)/static_cast<int>(DEFAULT_TILE_SIZE);
	else if (static_cast<int>(point.x-m_BoardOrigin.y)%static_cast<int>(DEFAULT_TILE_SIZE) > DEFAULT_TILE_SIZE - 20)
		indexedPosition.m_PosJ = static_cast<int>(point.y-m_BoardOrigin.y)/static_cast<int>(DEFAULT_TILE_SIZE) + 1;

	indexedPosition.m_PosI = indexedPosition.m_PosI * 2+ 1;
	indexedPosition.m_PosJ = indexedPosition.m_PosJ * 2 +1;

	return indexedPosition;
}
