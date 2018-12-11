#pragma once
#include "../etc/Vector2.h"
#include "../etc/Typedef.h"
class Ground
{
public:
	Ground() { size = { 0,0 }; }
	Ground(Vec2f groundSize) { size = groundSize; pos.y = WINDOW_SIZE_Y - size.y; }
	~Ground(){}
	Vec2f Getsize() { return size; }
	void Setsize(Vec2f size) { this->size = size; }
private:
	//	プレイヤーが移動できる範囲（サイズ）
	Vec2f size;
	//	プレイヤーが移動できる範囲（位置）
	Vec2f pos;

};