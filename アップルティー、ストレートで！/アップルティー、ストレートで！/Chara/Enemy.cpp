#include "Enemy.h"
#include "Player.h"
#include "../Application/Application.h"
#include <random>

// コンストラクタ
Enemy::Enemy() : 
	target(0.0f)
{
}

// デストラクタ
Enemy::~Enemy()
{
}

// ランダムなターゲット座標の生成
Vec2f Enemy::GetRandomPos(const Vec2f & range)
{
	std::random_device dev;
	std::mt19937 mt(dev());

	//ランダム範囲
	std::uniform_real_distribution<float> offsetX(0.0f, range.x);
	std::uniform_real_distribution<float> offsetY(0.0f, range.y);


	return Vec2f(offsetX(mt), offsetY(mt));
}

// あたり判定
bool Enemy::CheckHit(void)
{
	return false;
}
