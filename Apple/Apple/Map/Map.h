#pragma once
#include "../etc/Vector2.h"
#include "Ground.h"

#include <memory>

class Map {
public:
	Map();
	~Map();
	std::unique_ptr<Ground> ground;
	Vec2f GetGroundSize()
	{
		return ground->Getsize();
	};
	void SetSize(Vec2f size)
	{
		this->size = size;
	};
public:
	Vec2f size;
};