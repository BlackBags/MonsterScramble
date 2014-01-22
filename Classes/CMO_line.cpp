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
	//�����ֿ� ���� �׸� ���� ��
	static std::string objectNames[4] =
	{
		"image/MO_line_vertical.png",
		"image/MO_line_horizontal.png",
		"image/MO_line_vertical_c.png",
		"image/MO_line_horizontal_c.png",
	};

	//i�� Ȧ���� j�� ¦���� ���� �ִ�.
	//i�� ¦���� j�� Ȧ���� �� �ִ�.
	//¦������ ��� �������� �� ����. Ȧ������ ��� �������� �� ����.
	int width = (indexedPosition.m_PosI%2==0)? DEFAULT_LINE_WEIGHT : DEFAULT_TILE_SIZE ;
	int height = (indexedPosition.m_PosI%2==0)? DEFAULT_TILE_SIZE : DEFAULT_LINE_WEIGHT  ;

	int objectIdx = indexedPosition.m_PosI%2;

	//���� ����� ��� �׸��� �ٲ� ��.
	if (CGameManager::GetInstance()->GetMapType(indexedPosition) == MO_LINE_CONNECTED)
		objectIdx += 2;

	CMO_line* pMapObejct = CMO_line::create(objectNames[objectIdx].c_str(), CCRectMake(0.0f, 0.0f, width,  height));

	return pMapObejct;
}

void CMO_line::update( float delta )
{
	CCLog("Line updated");
	//���� Ÿ�� ������ ����� ������Ʈ
}
