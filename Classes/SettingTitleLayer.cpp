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

	// ������!!!! ���۹�ư�� ���� �����մϴ�

	CCMenuItemImage *StartButton = CCMenuItemImage::create(
		"image/SETTING_start.png",
		"image/SETTING_start.png",
		this,
		menu_selector(CSettingTitleLayer::StartButtonCallBack)
		);

	CCMenu	*StartButtonMenu = CCMenu::create(StartButton, NULL);
	// ������!!
	StartButtonMenu->setPosition(visibleSize.width/2, visibleSize.height/2 + 200);

	this->addChild(StartButtonMenu);

	// test
	return true;
}

void CSettingTitleLayer::StartButtonCallBack( CCObject* pSender )
{
	CGameManager::GetInstance()->StartGame();
}
