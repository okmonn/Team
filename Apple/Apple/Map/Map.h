#pragma once
#include "../etc/Vector2.h"
#include <memory>
#include <map>
#include "Ground.h"

class Map {
public:
	Map();
	~Map();
	Vec2f GetGroundSize()
	{
		return ground->Getsize();
	};
	Vec2f GetGroundPos()
	{
		return ground->Getsize();
	};
	void SetSize(Vec2f size)
	{
		this->size = size;
	};
public:
	Vec2f size;
	std::unique_ptr<Ground> ground;

};