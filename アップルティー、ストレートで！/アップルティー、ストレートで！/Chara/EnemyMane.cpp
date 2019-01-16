#include "EnemyMane.h"
#include "Player.h"
#include "Enemy1.h"
#include "../Application/Application.h"

// コンストラクタ
EnemyMane::EnemyMane(std::weak_ptr<Application>app, std::weak_ptr<Player> pl) : app(app), pl(pl)
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
	func.clear();

	func["1"] = [&](std::list<std::shared_ptr<Enemy>>& list, std::weak_ptr<Application>app, std::weak_ptr<Player>pl, const Vec2f& pos, const Vec2f& size)->void {
		list.push_back(std::make_shared<Enemy1>(app, pl, pos, size));
	};
}

// 敵の生成
void EnemyMane::Create(const std::string & type, const Vec2f & pos, const Vec2f & size)
{
	func[type](enemy, app, pl, pos, size);
}

// 描画
void EnemyMane::Draw(void)
{
	for (auto itr = enemy.begin(); itr != enemy.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

// 処理
void EnemyMane::UpData(void)
{
	for (auto itr = enemy.begin(); itr != enemy.end(); ++itr)
	{
		(*itr)->UpData();
	}
}

// クリア
void EnemyMane::Clear(void)
{
	enemy.clear();
}
