#pragma once
#include "cocos2d.h"

class CSettingCharacterLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();

	CREATE_FUNC(CSettingCharacterLayer);

private:
	// ĳ���͸� ���������� �Ͼ�� ��
	void SelectCharacterCallBack(CCObject* pSender);

	// �̱� ���� ����
	// ĳ���� �ϳ� ������ ������ 1�� �����Ѵ�.
	// ���ÿ� PlayerID ���ҵ� �Ѵ�. (��Ƽ������ �� ������ ��� �������� �´�)
	int m_TempPlayerNumber;
};

