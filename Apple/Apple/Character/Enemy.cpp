#include "Enemy.h"
#include "../Map/Map.h"

// �R���X�g���N�^
Enemy::Enemy(Map map)
{
	
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
