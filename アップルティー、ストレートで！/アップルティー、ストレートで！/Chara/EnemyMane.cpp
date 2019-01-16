#include "EnemyMane.h"
#include "Enemy1.h"

// �R���X�g���N�^
EnemyMane::EnemyMane()
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
	origin.clear();

	origin["1"] = std::make_shared<Enemy1>();
}

// �G�̐���
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

// �N���A
void EnemyMane::ClearEnemy(void)
{
	enemy.clear();
}

// �I���W���̃N���A
void EnemyMane::ClearOrigin(void)
{
	origin.clear();
}
