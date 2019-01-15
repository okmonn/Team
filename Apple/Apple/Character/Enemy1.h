#pragma once
#include "Enemy.h"

class Map;

class Enemy1 :
	public Enemy
{
public:
	Enemy1();
	Enemy1(std::weak_ptr<Union> un,std::weak_ptr<Map> map);
	~Enemy1();
	void Draw();
	void UpData();
};