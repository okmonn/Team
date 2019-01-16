#include "EnemyMane.h"
#include "Player.h"
#include "Enemy1.h"
#include "../Application/Application.h"

// �R���X�g���N�^
EnemyMane::EnemyMane(std::weak_ptr<Application>app, std::weak_ptr<Player> pl) : app(app), pl(pl)
{
	enemy.clear();

	Init();
}

// �f�X�g���N�^
EnemyMane::~EnemyMane()
{
}

// ������
void EnemyMane::Init(void)
{
	func.clear();

	func["1"] = [&](std::list<std::shared_ptr<Enemy>>& list, std::weak_ptr<Application>app, std::weak_ptr<Player>pl, const Vec2f& pos, const Vec2f& size)->void {
		list.push_back(std::make_shared<Enemy1>(app, pl, pos, size));
	};
}

// �G�̐���
void EnemyMane::Create(const std::string & type, const Vec2f & pos, const Vec2f & size)
{
	func[type](enemy, app, pl, pos, size);
}

// �`��
void EnemyMane::Draw(void)
{
	for (auto itr = enemy.begin(); itr != enemy.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

// ����
void EnemyMane::UpData(void)
{
	for (auto itr = enemy.begin(); itr != enemy.end(); ++itr)
	{
		(*itr)->UpData();
	}
}

// �N���A
void EnemyMane::Clear(void)
{
	enemy.clear();
}
