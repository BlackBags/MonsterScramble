#include "MapObject.h"

USING_NS_CC;


CMapObject::CMapObject()
{

}

CMapObject::~CMapObject()
{

}

CMapObject* CMapObject::create(const char* pszFileName, const CCRect& rect)
{
	CMapObject* pSprite = new CMapObject();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMapObject* CMapObject::Create(MO_TYPE type)
{
	//�� MO_TYPE�� �ش��ϴ� �׸��� �� ���� ����.
	static std::string objectNames[MO_TYPE_NUMBER] =
	{
		
	};

	if (type < 0 || type > MO_TYPE_NUMBER - 1)
		return NULL;

	//m_Type�� �����Ǵ� �̹����� �����ͼ� ������Ʈ�� �����Ѵ�. ���⼭�� setMapType�� ������Ʈ�� ���� ...?
	CMapObject* pCMapObject = CMapObject::create(objectNames[type].c_str(), CCRectMake(0.0f, 0.0f, 100.0f, 100.0f));
	pCMapObject->SetMapType(type);

	return pCMapObject;
}

int CMapObject::GetMapType()
{
	return m_type;
}

void CMapObject::SetMapType(MO_TYPE type)
{
	m_type = type;
}
