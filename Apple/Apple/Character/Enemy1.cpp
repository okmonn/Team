#include "Enemy1.h"
#include "../Map/Map.h"
#include "../Union/Union.h"


Enemy1::Enemy1()
{

}
Enemy1::Enemy1(std::weak_ptr<Union> un,std::weak_ptr<Map> map)
{
	this->un = un;
	this->map = map;
	Load("rsc/img/player.png", "en");
	Load("rsc/img/player.png", "n");
	Load("rsc/img/player.png", "e");
	pos = { 0.0f+240.0f, 120.0f };
	size = { 240.0f, 270.0f };
}

Enemy1::~Enemy1()
{

}

void Enemy1::Draw(void)
{
	//DrawImg("pl", lpos.x, lpos.y - size.y, size.x, size.y);	
	DrawImg("en", lpos.x, lpos.y - size.y, size.x, size.y);	
	//DrawImg("pl", pos.x + Camera::Get().GetPos().x, pos.y + Camera::Get().GetPos().y + GROUND_Y, size.x, size.y);
}

void Enemy1::UpData()
{

}