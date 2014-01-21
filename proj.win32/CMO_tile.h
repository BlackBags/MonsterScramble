#ifndef MonsterScramble_MapObject
#define MonsterScramble_MapObject

#pragma once
#include "cocos2d.h"
#include "config.h"


class CMO_tile : public cocos2d::CCSprite
{
public:
	CMO_tile();
	~CMO_tile();

protected:
	static CMO_tile* create(const char* pszFileName, const cocos2d::CCRect& rect);

public:
	static CMO_tile* Create(IndexedPosition indexedPosition);
	void update(float delta);


private:
	static IndexedPosition m_indexedPosition;

};

#endif

