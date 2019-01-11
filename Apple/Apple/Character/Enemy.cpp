#include "Enemy.h"
#include "../Map/Map.h"

// コンストラクタ
Enemy::Enemy(std::weak_ptr<Map> map)
{
	Load("rsc/img/player.png", "pl");

	pos = { 0.0f, this->map.lock()->GetGroundPos().y };
	size = { 240.0f, 270.0f };

}

// デストラクタ
Enemy::~Enemy()
{
}

// 待機時の処理
void Enemy::Wait(void)
{
	if (st != "wait")
	{
		return;
	}
}

// 移動時の処理
void Enemy::Walk(void)
{
	if (st != "walk")
	{
		return;
	}
}

// 攻撃時の処理
void Enemy::Attack(void)
{
	if (st != "attack")
	{
		return;
	}
}

// ダメージ時の処理
void Enemy::Damage(void)
{
	if (st != "damage")
	{
		return;
	}
}
