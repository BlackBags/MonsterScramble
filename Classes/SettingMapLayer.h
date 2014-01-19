#pragma once
#include "cocos2d.h"

class CSettingMapLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	CREATE_FUNC(CSettingMapLayer);

private:
	void SelectMapCallBack(CCObject* pSender);
};