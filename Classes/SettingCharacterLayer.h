#pragma once
#include "cocos2d.h"

class CSettingCharacterLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	CREATE_FUNC(CSettingCharacterLayer);

private:
	// 캐릭터를 선택했을떄 일어나는 일
	void SelectCharacterCallBack(CCObject* pSender);

	// 싱글 전용 변수
	// 캐릭을 하나 선택할 때마다 1씩 증가한다.
	// 동시에 PlayerID 역할도 한다. (멀티에서는 이 정보가 모두 서버에서 온다)
	int m_TempPlayerNumber;
};

