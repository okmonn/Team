#include "Enemy1.h"



Enemy1::Enemy1()
{

}


Enemy1::~Enemy1()
{

}

void Enemy1::Draw(void)
{
	DrawImg("pl", lpos.x, lpos.y - size.y, size.x, size.y);	
	//DrawImg("pl", pos.x + Camera::Get().GetPos().x, pos.y + Camera::Get().GetPos().y + GROUND_Y, size.x, size.y);
}
