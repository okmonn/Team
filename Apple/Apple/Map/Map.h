#pragma once
#include "../etc/Vector2.h"
class Map {
public:
	Map();
	~Map();
	Vec2f GetSize()
	{
		return size;
	};
	void SetSize(Vec2f size)
	{
		this->size = size;
	};
public:
	Vec2f size;
};