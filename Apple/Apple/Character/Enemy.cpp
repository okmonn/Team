#include "Enemy.h"
#include "../Map/Map.h"

// �R���X�g���N�^
Enemy::Enemy(std::weak_ptr<Map> map)
{
	Load("rsc/img/player.png", "pl");

	pos = { 0.0f, this->map.lock()->GetGroundPos().y };
	size = { 240.0f, 270.0f };

}

// �f�X�g���N�^
Enemy::~Enemy()
{
}

// �ҋ@���̏���
void Enemy::Wait(void)
{
	if (st != "wait")
	{
		return;
	}
}

// �ړ����̏���
void Enemy::Walk(void)
{
	if (st != "walk")
	{
		return;
	}
}

// �U�����̏���
void Enemy::Attack(void)
{
	if (st != "attack")
	{
		return;
	}
}

// �_���[�W���̏���
void Enemy::Damage(void)
{
	if (st != "damage")
	{
		return;
	}
}
