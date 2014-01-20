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

	return true;
}