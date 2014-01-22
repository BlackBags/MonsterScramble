#include "CMO_line.h"
#include "GameManager.h"

USING_NS_CC;


CMO_line::CMO_line()
{

}

CMO_line::~CMO_line()
{

}

CMO_line* CMO_line::create(const char* pszFileName, const CCRect& rect)
{
	CMO_line* pSprite = new CMO_line();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_line* CMO_line::Create(IndexedPosition indexedPosition)
{
	//소유주에 따른 그림 파일 들
	static std::string objectNames[4] =
	{
		"image/MO_line_vertical.png",
		"image/MO_line_horizontal.png",
		"image/MO_line_vertical_c.png",
		"image/MO_line_horizontal_c.png",
	};

	//i가 홀수고 j가 짝수면 누워 있다.
	//i가 짝수고 j가 홀수면 서 있다.
	//짝수행인 경우 수평으로 긴 라인. 홀수행인 경우 수직으로 긴 라인.
	int width = (indexedPosition.m_PosI%2==0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI%2==0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	int objectIdx = indexedPosition.m_PosI%2;

	//선이 연결된 경우 그림만 바꿔 줌.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
		objectIdx += 2;

	CMO_line* pMapObejct = CMO_line::create(objectNames[objectIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height));

	return pMapObejct;
}

void CMO_line::update( float delta )
{
	CCLog("Line updated");
	//현재 타일 소유를 물어보고 업데이트
}
