#include "EnemyMane.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "../Application/Application.h"

// �R���X�g���N�^
EnemyMane::EnemyMane(std::weak_ptr<Application>app, std::weak_ptr<Camera>cam, std::weak_ptr<Player>pl) : app(app), cam(cam), pl(pl)
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

	func["1"] = [&](std::list<std::shared_ptr<Enemy>>& list, std::weak_ptr<Application>app,std::weak_ptr<Camera>cam, std::weak_ptr<Player>pl, const Vec2f& pos, const Vec2f& size)->void {
		list.push_back(std::make_shared<Enemy1>(app,cam, pl, pos, size));
	};

	func["2"] = [&](std::list<std::shared_ptr<Enemy>>& list, std::weak_ptr<Application>app, std::weak_ptr<Camera>cam, std::weak_ptr<Player>pl, const Vec2f& pos, const Vec2f& size)->void {
		list.push_back(std::make_shared<Enemy2>(app, cam, pl, pos, size));
	};

}

// �G�̐���
void EnemyMane::Create(const std::string & type, const Vec2f & pos, const Vec2f & size)
{
	func[type](enemy, app, cam, pl, pos, size);
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
	for (auto itr = enemy.begin(); itr != enemy.end();)
	{
		(*itr)->UpData();
		if ((*itr)->GetDead())
		{
			itr = enemy.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

// �N���A
void EnemyMane::Clear(void)
{
	enemy.clear();
}
