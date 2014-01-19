#include "SettingCharacterLayer.h"
#include "GameManager.h"

USING_NS_CC;

bool CSettingCharacterLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// 멤버변수 초기화
	m_TempPlayerNumber = 0;

	// Get Window Size
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); 

	// CCMenu
	// 조심해! 일단 init에 넣고 모듈화는 좀 있다가..
	CCMenu *CharacterSelectTable = CCMenu::createWithItems(NULL, NULL);

	// make Image Buttons
	CCMenuItemImage *pCharacter1 = CCMenuItemImage::create(
		"image/PLAYER_1_face.png",
		"image/PLAYER_1_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter2 = CCMenuItemImage::create(
		"image/PLAYER_2_face.png",
		"image/PLAYER_2_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter3 = CCMenuItemImage::create(
		"image/PLAYER_3_face.png",
		"image/PLAYER_3_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	CCMenuItemImage *pCharacter4 = CCMenuItemImage::create(
		"image/PLAYER_4_face.png",
		"image/PLAYER_4_selected_face.png",
		this,
		menu_selector(CSettingCharacterLayer::SelectCharacterCallBack)
		);

	// set Tag : 어떤 캐릭터가 선택됐는지 확인해야 하므로
	pCharacter1->setTag(0);
	pCharacter2->setTag(1);
	pCharacter3->setTag(2);
	pCharacter4->setTag(3);

	// add Child
	CharacterSelectTable->addChild(pCharacter1, 2);
	CharacterSelectTable->addChild(pCharacter2, 2);
	CharacterSelectTable->addChild(pCharacter3, 2);
	CharacterSelectTable->addChild(pCharacter4, 2);

	// set Position
	CharacterSelectTable->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	CharacterSelectTable->alignItemsHorizontally();

	// add to class Character Select menu
	this->addChild(CharacterSelectTable);

	return true;
}

void CSettingCharacterLayer::SelectCharacterCallBack(CCObject* pSender)
{
	// 이 매크로들의 의미는 뭘까요? 운영체제랑 관계있는거 같은데.. 이대로면 IOS에서 그냥 꺼지는거 아닌지?
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	// 조심해!! 현재 캐릭터 선택 / 취소가 체크박스 로직이 아니라 클릭 멈추면 취소되는 형태
	// 선택 취소가 안 되고 클릭할때마다 PlayerNumber가 계속 커지는 버그 있음.
	// 중복 선택을 막을 수도 없다.
	// 적당한 API가 있을 것 같은데.. 좀 더 뒤져봐야겠다.

	// 어떤 버튼이 클릭되었는지를 알아본다.
	int selectedCharacterId = static_cast<CCMenuItem*>(pSender)->getTag();

	CGameManager::GetInstance()->SelectCharacter(m_TempPlayerNumber, selectedCharacterId);
	
	// 추가 선택을 대비하여 1 증가시킨다. 실제 데이터에 반영되는 것은 m_TempPlayerNumber 최종 상태보다 항상 1 작다.
	++m_TempPlayerNumber;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}