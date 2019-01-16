#include "EnemyMane.h"
#include "Enemy1.h"

// コンストラクタ
EnemyMane::EnemyMane()
{
	enemy.clear();

	Init();
}

// デストラクタ
EnemyMane::~EnemyMane()
{
}

// 初期化
void EnemyMane::Init(void)
{
	origin.clear();

	origin["1"] = std::make_shared<Enemy1>();
}

// 敵の生成
void EnemyMane::Create(const std::string & type, const Vec2f & pos, const Vec2f & size)
{
	if (origin.find(type) == origin.end())
	{
		return;
	}

	enemy.push_back(origin[type]);
	enemy.back()->SetPos(pos);
	enemy.back()->SetSize(size);
}

// クリア
void EnemyMane::ClearEnemy(void)
{
	enemy.clear();
}

// オリジンのクリア
void EnemyMane::ClearOrigin(void)
{
	origin.clear();
}
