#include "SettingTitleLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CSettingTitleLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// get Windows Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// Create sprite
	CCSprite* pTitle = CCSprite::create("image/SETTING_title.png");

	// Title Position : X Center + Y
	pTitle->setPosition(ccp(visibleSize.width/2, visibleSize.height - pTitle->getContentSize().height) );
	this->addChild(pTitle, 0);

	// 조심해!!!! 시작버튼은 따로 빼야합니다

	CCMenuItemImage *StartButton = CCMenuItemImage::create(
		"image/SETTING_start.png",
		"image/SETTING_start.png",
		this,
		menu_selector(CSettingTitleLayer::StartButtonCallBack)
		);

	CCMenu	*StartButtonMenu = CCMenu::create(StartButton, NULL);
	// 조심해!!
	StartButtonMenu->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);

	this->addChild(StartButtonMenu);

	// test
	return true;
}

void CSettingTitleLayer::StartButtonCallBack( CCObject* pSender )
{
	CGameManager::GetInstance()->StartGame();
}
