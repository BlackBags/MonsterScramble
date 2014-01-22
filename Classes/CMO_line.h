#pragma once
#include "cocos2d.h"
#include "config.h"


class CMO_line : public cocos2d::CCSprite
{
public:
	CMO_line();
	~CMO_line();

protected:
	static CMO_line* create(const char* pszFileName, const cocos2d::CCRect& rect);

public:
	static CMO_line* Create(IndexedPosition indexedPosition);

private:
};


