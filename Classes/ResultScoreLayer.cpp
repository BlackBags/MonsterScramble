#include "ResultScoreLayer.h"
#include "MainScene.h"

USING_NS_CC;

bool CResultScoreLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a background image

	//title 표시


	//메인 메뉴로 가는 버튼 등록
	CCMenu* pMenu = nullptr;

	CCMenuItemImage *pFinish = CCMenuItemImage::create(
										"MAIN_newgame.png",
										"MAIN_newgame_selected.png",
										this,
										menu_selector(CResultScoreLayer::mainSceneCallback));

	pFinish->setPosition(ccp(origin.x + visibleSize.width/2, visibleSize.height/2 - pFinish->getContentSize().height/2) );

	// create menu, it's an autorelease object
	pMenu = CCMenu::create(pFinish, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
	return true;
}

void CResultScoreLayer::mainSceneCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    //CCDirector::sharedDirector()->end(); //credit load
	CCScene* newScene = CMainScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, newScene) );
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}