#include "GameBoardLayer.h"
#include "config.h"
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
	// 사용하는 모든 자원을 일단 모두 등록하고 가시성 속성을 바꿀까...아무튼


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
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
	board->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(board);


	for (int i = 1; i<rowNum*2+2;++i)
	{
		for(int j = 1; j<columnNum*2+2;++j)
		{
			IndexedPosition pos;
			pos.m_PosI = i;
			pos.m_PosJ = j;

			//행, 열 모두 짝수 일 경우 타일을 그린다.
			if ( i %2 == 0 && j%2 == 0)
			{
				CMO_tile* pTile = CMO_tile::Create(pos);
				pTile->setAnchorPoint(ccp(0,0));
				pTile->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2-1),DEFAULT_TILE_SIZE*(i/2-1)));

				board->addChild(pTile,0);
			}
			// 행, 열 모두 홀수일 경우 닷을 그린다.
			else if ( i %2 == 1 && j%2 == 1)
			{
				CMO_dot* pDot = CMO_dot::Create();
				pDot->setPosition(ccp(DEFAULT_TILE_SIZE*(j/2),DEFAULT_TILE_SIZE*(i/2)));

				board	->addChild(pDot,2);
			}
			//그 외에는 선이다.
			else
			{
				CMO_line* pLine = CMO_line::Create(pos);
				//누워있다.
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
	

}

void CGameBoardLayer::DrawMapObjects()
{
	
}
