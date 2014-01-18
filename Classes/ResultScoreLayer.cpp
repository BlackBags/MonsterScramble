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

	//±×¸®±â
    
	return true;
}