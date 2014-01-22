#include "CMO_tile.h"
#include "GameManager.h"

USING_NS_CC;


CMO_tile::CMO_tile()
{
}

CMO_tile::~CMO_tile()
{

}

CMO_tile* CMO_tile::create(const char* pszFileName, const CCRect& rect)
{
	CMO_tile* pSprite = new CMO_tile();
	if (pSprite && pSprite->initWithFile(pszFileName, rect))
	{
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CMO_tile* CMO_tile::Create(IndexedPosition indexedPosition)
{

	//소유주에 따른 그림 파일 들
	static std::string objectNames[5] =
	{
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png",
		"image/MO_tile.png"
	};
	
	//int objectIdx = CGameManager::GetInstance()->GetMapOwner(indexedPosition);
	CMO_tile* pMapObejct = CMO_tile::create(objectNames[0].c_str(), CCRectMake(0.0f, 0.0f, DEFAULT_TILE_SIZE,  DEFAULT_TILE_SIZE));

	return pMapObejct;
}

void CMO_tile::update( float delta )
{

}
