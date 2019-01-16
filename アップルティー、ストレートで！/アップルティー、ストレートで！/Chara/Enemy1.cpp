#include "Enemy1.h"
#include "../Application/Application.h"

// コンストラクタ
Enemy1::Enemy1(std::weak_ptr<Application> app, const Vec2f & pos, const Vec2f & size)
{
	this->app  = app;
	this->pos  = pos;
	this->size = size;
}

// デストラクタ
Enemy1::~Enemy1()
{
}

// 描画
void Enemy1::Draw(void)
{
}

// 処理
void Enemy1::UpData(void)
{
}
