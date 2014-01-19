#include "MainScene.h"
#include "BackgroundLayer.h"
#include "GameSettingScene.h"
#include "SettingTitleLayer.h"
#include "SettingCharacterLayer.h"
#include "SettingMapLayer.h"

USING_NS_CC;

bool CGameSettingScene::init(void)
{
	//////////////////////////////
	// 1. super init first
	if ( !CCScene::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add layers
	
	// background layer
	CCLayer* BackgroundLayer = CBackgroundLayer::create();
	this->addChild(BackgroundLayer, 0);

	// title layer
	CCLayer* SettingTitleLayer = CSettingTitleLayer::create();
	this->addChild(SettingTitleLayer, 1);

	// Character Select Table layer
	CSettingCharacterLayer* SettingCharacterLayer = CSettingCharacterLayer::create();
	this->addChild(SettingCharacterLayer, 1);

	// map select table layer
	CSettingMapLayer* SettingMaplayer = CSettingMapLayer::create();
	this->addChild(SettingMaplayer, 1);

	return true;
}