#pragma once
#include "../etc/Vector2.h"
#include "../etc/Typedef.h"
class Ground
{
public:
	Ground() { size = { 0,0 }; }
	Ground(Vec2f groundSize) { size = groundSize; pos = {0, WINDOW_SIZE_Y - size.y }; }
	~Ground(){}
	Vec2f Getsize() { return size; }
	void Setsize(Vec2f size) { this->size = size; }
	Vec2f Getpos() { return pos; }
	void Setpos(Vec2f pos) { this->pos = pos; }
private:
	//	プレイヤーが移動できる範囲（サイズ）
	Vec2f size;
	//	プレイヤーが移動できる範囲（位置）
	Vec2f pos;

};