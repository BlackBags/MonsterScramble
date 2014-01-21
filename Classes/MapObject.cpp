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
	//각 MO_TYPE에 해당하는 그림이 이 곳에 들어간다.
	static std::string objectNames[MO_TYPE_NUMBER] =
	{
		
	};

	if (type < 0 || type > MO_TYPE_NUMBER - 1)
		return NULL;

	//m_Type과 대응되는 이미지를 가져와서 오브젝트를 생성한다. 여기서의 setMapType는 업데이트를 위해 ...?
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
