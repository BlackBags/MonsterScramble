#pragma once
#include "cocos2d.h"

class CPlayerLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	virtual void update(float dt);

	// implement the "static node()" method manually
	CREATE_FUNC(CPlayerLayer);

private:
	cocos2d::CCSize m_VisibleSize;

};

