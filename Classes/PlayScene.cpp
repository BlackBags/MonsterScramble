#include "PlayScene.h"
#include "BackgroundLayer.h"
#include "GameBoardLayer.h"
#include "GameEndLayer.h"
#include "HelpButtonLayer.h"
#include "HelpWindowLayer.h"
#include "PlayerLayer.h"
#include "TimerLayer.h"

USING_NS_CC;

bool CPlayScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	/////////////////////////////
    // 2. add layers
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	CCLayer* gameBoard = CGameBoardLayer::create();
	this->addChild(gameBoard, 1);

	CCLayer* endButton = CGameEndLayer::create();
	this->addChild(endButton, 1);

	CCLayer* helpButton = CHelpButtonLayer::create();
	this->addChild(helpButton, 1);

	CCLayer* player = CPlayerLayer::create();
	this->addChild(player, 1);

	CCLayer* timer = CTimerLayer::create();
	this->addChild(timer, 1);

	CCLayer* helpWindow = CHelpWindowLayer::create();
	this->addChild(helpWindow, 2);

	//매프레임마다 update함수 호출하도록 설정
	//this->schedule(schedule_selector(CPlayScene::update) );

	//이렇게 설정하면 update함수가 알아서 프레임마다 호출된다.
	this->scheduleUpdate();

	return true;
}

void CPlayScene::update(float dt)
{
	//dt는 이전 update 이후 지난 시간

	
	//여기에 각 레이어들을 업데이트하는 코드를 넣음
	//각 레이어별로 업데이트 함수 만들어야 함
}